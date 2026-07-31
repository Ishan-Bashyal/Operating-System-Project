//Task 4 - Section 3: Authentication + Multiple Concurrent Clients (SERVER)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 65433
#define BUF_SIZE 512

typedef struct { const char *username; const char *password; } Cred;
Cred USERS[] = { {"ram", "ram123"}, {"shyam", "shyam123"} };
#define NUM_USERS 2

int read_line(int sock, char *buf, int size) {
    int i = 0;
    char c;
    while (i < size - 1) {
        int n = recv(sock, &c, 1, 0);
        if (n <= 0) return 0;
        if (c == '\n') break;
        buf[i++] = c;
    }
    buf[i] = '\0';
    return 1;
}

void *handle_client(void *arg) {
    int sock = *(int *)arg;
    free(arg);
    char line[BUF_SIZE];
    char logged_in_user[64] = "";

    // Check login details
    if (!read_line(sock, line, sizeof(line))) { close(sock); return NULL; }
    char cmd[16], user[64], pass[64];
    sscanf(line, "%15s %63s %63s", cmd, user, pass);

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

    // Receive messages
    while (read_line(sock, line, sizeof(line))) {
        if (strcmp(line, "BYE") == 0) break;
        if (strncmp(line, "MSG ", 4) == 0) {
            printf("[%s] %s\n", logged_in_user, line + 4);
            char reply[BUF_SIZE];
            snprintf(reply, sizeof(reply), "ACK %s\n", line + 4);
            send(sock, reply, strlen(reply), 0);
        }
    }

    printf("[%s] Disconnected\n", logged_in_user);
    close(sock);
    return NULL;
}

int main(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);   // Create the server socket
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));   // Bind the socket
    listen(server_fd, 5);                                      // Wait for clients
    printf("Server listening on 127.0.0.1:%d\n", PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
        if (client_fd < 0) continue;

        printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        int *arg = malloc(sizeof(int));
        *arg = client_fd;
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, arg);
        pthread_detach(tid);   // Thread closes automatically
    }
    return 0;
}