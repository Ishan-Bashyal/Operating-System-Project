//Task 4 - Section 4: Data Validation + Error Handling (CLIENT, final version)

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65432
#define BUF_SIZE 512

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
        if (n <= 0) return 0;
        if (c == '\n') break;
        buf[i++] = c;
    }
    buf[i] = '\0';
    return 1;
}

int main(int argc, char *argv[]) {
    const char *mode = (argc > 1) ? argv[1] : "normal";

    int sock = socket(AF_INET, SOCK_STREAM, 0);   //Create the client socket
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(PORT);

    connect(sock, (struct sockaddr *)&addr, sizeof(addr));   //Connect to the server

    const char *password = (strcmp(mode, "badpass") == 0) ? "wrongpassword" : "ram123";
    char msg[BUF_SIZE];
    snprintf(msg, sizeof(msg), "LOGIN ram %s\n", password);
    send(sock, msg, strlen(msg), 0);

    char buf[BUF_SIZE];
    read_line(sock, buf, sizeof(buf));
    printf("Login: %s\n", buf);
    if (strcmp(buf, "AUTH_OK") != 0) { close(sock); return 0; }

    const char *messages[2] = {"hello server", "second message"};
    for (int i = 0; i < 2; i++) {
        int cs = checksum(messages[i]);
        if (strcmp(mode, "corrupt") == 0 && i == 1)
            cs += 1;   //Change the checksum for testing

        snprintf(msg, sizeof(msg), "DATA %d %s\n", cs, messages[i]);
        send(sock, msg, strlen(msg), 0);
        read_line(sock, buf, sizeof(buf));
        printf("Sent: %s | Reply: %s\n", messages[i], buf);
    }

    send(sock, "BYE\n", 4, 0);
    close(sock);
    return 0;
}