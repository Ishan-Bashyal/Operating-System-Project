//Task 4 - Section 4: Data Validation + Error Handling (SERVER, final version)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 65432
#define BUF_SIZE 512

typedef struct { const char *username; const char *password; } Cred;
Cred USERS[] = { {"ram", "ram123"}, {"shyam", "shyam123"} };
#define NUM_USERS 2

int checksum(const char *text) {
    int sum = 0;
    for (int i = 0; text[i] != '\0'; i++) sum += (unsigned char)text[i];
    return sum;
}

int read_line(int sock, char *buf, int size) {
    int i = 0;
    char c;
    while (i < size - 1) {
        int n = recv(sock, &c, 1, 0);
        if (n <= 0) return 0;      //Client disconnected
        if (c == '\n') break;
        buf[i++] = c;
    }
    buf[i] = '\0';
    return 1;
}

void *handle_client(void *arg) {
    int sock = *(int *)arg;
    free(arg);
    char buf[BUF_SIZE];
    char logged_in_user[64] = "";

    // Check login details
    if (!read_line(sock, buf, sizeof(buf))) { close(sock); return NULL; }
    char cmd[16], user[64], pass[64];
    sscanf(buf, "%15s %63s %63s", cmd, user, pass);

    int ok = 0;
    if (strcmp(cmd, "LOGIN") == 0) {
        for (int i = 0; i < NUM_USERS; i++) {
            if (strcmp(USERS[i].username, user) == 0 && strcmp(USERS[i].password, pass) == 0) {
                ok = 1;
                strcpy(logged_in_user, user);
                break;
            }
        }
    }

    if (ok) {
        send(sock, "AUTH_OK\n", 8, 0);
        printf("[%s] Login successful\n", logged_in_user);
    } else {
        send(sock, "AUTH_FAIL\n", 10, 0);
        printf("Login failed for %s\n", user);
        close(sock);
        return NULL;
    }

    // Check the received data
    while (read_line(sock, buf, sizeof(buf))) {
        if (strcmp(buf, "BYE") == 0) break;

        if (strncmp(buf, "DATA ", 5) == 0) {
            int sent_checksum;
            char message[BUF_SIZE];
            sscanf(buf + 5, "%d %[^\n]", &sent_checksum, message);

            if (checksum(message) == sent_checksum) {
                send(sock, "ACK\n", 4, 0);
                printf("[%s] Data: %s\n", logged_in_user, message);
            } else {
                send(sock, "REJECT\n", 7, 0);
                printf("[%s] Invalid data: %s\n", logged_in_user, message);
            }
        }
    }

    printf("[%s] Disconnected\n", logged_in_user);
    close(sock);
    return NULL;
}

int main(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);   //Create the server socket
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));   //Bind the socket
    listen(server_fd, 5);                                      //Wait for clients
    printf("Server listening on 127.0.0.1:%d\n", PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) continue;   //Skip if accept fails

        printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        int *arg = malloc(sizeof(int));
        *arg = client_fd;
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, arg);
        pthread_detach(tid);   //Thread closes automatically
    }
    return 0;
}