//Task 4 - Section 1: Basic Client-Server Socket Connection (SERVER)

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65431

int main(void) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);   //Create the server socket

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));   //Bind the socket
    listen(server_fd, 1);                                       //Listen for a client
    printf("Server listening on 127.0.0.1:%d\n", PORT);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);  //Accept the connection
    printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    char buffer[256] = {0};
    recv(client_fd, buffer, sizeof(buffer), 0);
    printf("Received: %s\n", buffer);

    const char *reply = "Hello from the server!";
    send(client_fd, reply, strlen(reply), 0);
    printf("Reply sent.\n");

    close(client_fd);
    close(server_fd);
    return 0;
}