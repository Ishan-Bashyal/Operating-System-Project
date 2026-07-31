// Task 4 - Section 1: Basic Client-Server Socket Connection (CLIENT)

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65431

int main(void) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    printf("Connected to the server.\n");

    const char *msg = "Hello from the client!";
    send(sock, msg, strlen(msg), 0);
    printf("Message sent: %s\n", msg);

    char buffer[256] = {0};
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Reply: %s\n", buffer);

    close(sock);
    return 0;
}