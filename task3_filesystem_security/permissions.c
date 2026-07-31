// Task 3 - Section 3: File Permission System

#include <stdio.h>
#include <string.h>

#define NAME_LEN 32

typedef struct {
    char filename[NAME_LEN];
    char owner[NAME_LEN];
    char owner_perm[4];
    char group_perm[4];
    char others_perm[4];
} FileMeta;

FileMeta file;      // Sample file
char known_users[3][NAME_LEN] = {"ram", "shyam", "hari"};  // Registered users

int is_known_user(const char *user) {
    for (int i = 0; i < 3; i++)
        if (strcmp(known_users[i], user) == 0) return 1;
    return 0;
}

const char *relation(const char *user) {
    if (strcmp(file.owner, user) == 0) return "owner";
    return is_known_user(user) ? "group" : "others";
}

const char *perm_for(const char *rel) {
    if (strcmp(rel, "owner") == 0) return file.owner_perm;
    if (strcmp(rel, "group") == 0) return file.group_perm;
    return file.others_perm;
}

void try_read(const char *user) {
    const char *rel = relation(user);
    int allowed = strchr(perm_for(rel), 'r') != NULL;

    printf("%-8s (%-6s) Read: %s\n",
           user, rel, allowed ? "Allowed" : "Denied");
}

void try_write(const char *user) {
    const char *rel = relation(user);
    int allowed = strchr(perm_for(rel), 'w') != NULL;

    printf("%-8s (%-6s) Write: %s\n",
           user, rel, allowed ? "Allowed" : "Denied");
}

int main(void) {
    strcpy(file.filename, "notes.txt");
    strcpy(file.owner, "ram");
    strcpy(file.owner_perm, "rw");    // Owner can read and write
    strcpy(file.group_perm, "r");     // Group can only read
    strcpy(file.others_perm, "");     // No permission

    printf("File: %s\n", file.filename);
    printf("Owner: %s\n\n", file.owner);

    try_read("ram");
    try_write("ram");

    try_read("shyam");
    try_write("shyam");

    try_read("gita");
    try_write("gita");

    return 0;
}