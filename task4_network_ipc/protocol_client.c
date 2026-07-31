//Task 4 - Section 2: A Simple Protocol for Data Exchange (CLIENT)

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
        if (n <= 0) return 0;
        if (c == '\n') break;
        buf[i++] = c;
    }
    buf[i] = '\0';
    return 1;
}

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);   //Create the client socket
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));   //Connect to the server
    printf("Connected to the server.\n");

    const char *messages[2] = {"hello there", "second message"};
    char line[BUF_SIZE];

    for (int i = 0; i < 2; i++) {
        char cmd[BUF_SIZE];
        snprintf(cmd, sizeof(cmd), "MSG %s\n", messages[i]);
        send(sock, cmd, strlen(cmd), 0);
        read_line(sock, line, sizeof(line));
        printf("Sent: %s | Reply: %s\n", messages[i], line);
    }

    send(sock, "BYE\n", 4, 0);
    close(sock);
    return 0;
}