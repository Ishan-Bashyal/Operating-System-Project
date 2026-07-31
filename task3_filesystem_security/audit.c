// Task 3 - Section 5: Audit Logging

#include <stdio.h>

FILE *audit_log;

void log_action(const char *user, const char *action, const char *filename, const char *result) {
    printf("User: %s | Action: %s | File: %s | Result: %s\n",
           user, action, filename, result);

    fprintf(audit_log, "User: %s | Action: %s | File: %s | Result: %s\n",
            user, action, filename, result);

    fflush(audit_log);   // Save changes immediately
}

int main(void) {
    audit_log = fopen("audit.log", "a");   // Open the log file

    // Sample actions
    log_action("ram",   "CREATE", "notes.txt", "OK");
    log_action("ram",   "READ",   "notes.txt", "OK");
    log_action("shyam", "READ",   "notes.txt", "OK");
    log_action("shyam", "WRITE",  "notes.txt", "DENIED");
    log_action("hari",  "READ",   "notes.txt", "DENIED");
    log_action("ram",   "DELETE", "notes.txt", "OK");

    fclose(audit_log);

    printf("\nAudit log saved.\n");

    return 0;
}