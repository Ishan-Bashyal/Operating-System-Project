//Task 4 - Section 2: A Simple Protocol for Data Exchange (SERVER)

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65432
#define BUF_SIZE 512

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

int main(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);   //Create the server socket
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));   //Bind the socket
    listen(server_fd, 1);                                      //Wait for a client
    printf("Server listening on 127.0.0.1:%d\n", PORT);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);
    printf("Client connected.\n");

    char line[BUF_SIZE];
    while (read_line(client_fd, line, sizeof(line))) {
        if (strcmp(line, "BYE") == 0) {
            printf("Connection closed.\n");
            break;
        }

        if (strncmp(line, "MSG ", 4) == 0) {
            printf("Message: %s\n", line + 4);
            char reply[BUF_SIZE];
            snprintf(reply, sizeof(reply), "ACK %s\n", line + 4);
            send(client_fd, reply, strlen(reply), 0);
        }
    }

    close(client_fd);
    close(server_fd);
    return 0;
}