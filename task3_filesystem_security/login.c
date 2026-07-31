// Task 3 - Section 1: User Authentication

#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define NAME_LEN 32

typedef struct {
    char username[NAME_LEN];
    unsigned long password_hash;
} User;

User users[MAX_USERS];
int user_count = 0;

unsigned long simple_hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

void register_user(const char *username, const char *password) {
    strcpy(users[user_count].username, username);
    users[user_count].password_hash = simple_hash(password);

    printf("User '%s' registered.\n", username);

    user_count++;
}

int login(const char *username, const char *password) {
    unsigned long h = simple_hash(password);

    for (int i = 0; i < user_count; i++)
        if (strcmp(users[i].username, username) == 0)
            return users[i].password_hash == h;

    return 0;   // User not found
}

int main(void) {
    register_user("ram", "ram123");
    register_user("shyam", "shyam123");

    printf("\n");

    printf("Ram login: %s\n",
           login("ram", "ram123") ? "SUCCESS" : "FAILED");

    printf("Ram with wrong password: %s\n",
           login("ram", "wrongpass") ? "SUCCESS" : "FAILED");

    printf("Hari login: %s\n",
           login("hari", "hari123") ? "SUCCESS" : "FAILED");

    return 0;
}