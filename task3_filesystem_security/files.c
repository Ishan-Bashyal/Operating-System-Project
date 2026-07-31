// Task 3 - Section 2: File Operations (Create, Read, Write, Delete)

#include <stdio.h>
#include <string.h>

int main(void) {
    const char *filename = "demo.txt";
    char buffer[256];

    // Create the file
    FILE *f = fopen(filename, "w");
    fprintf(f, "Hello, this is the original content.");
    fclose(f);
    printf("File '%s' created.\n", filename);

    // Read the file
    f = fopen(filename, "r");
    fgets(buffer, sizeof(buffer), f);
    fclose(f);
    printf("Content: %s\n", buffer);

    // Update the file
    f = fopen(filename, "w");
    fprintf(f, "Content has been updated.");
    fclose(f);
    printf("File updated.\n");

    // Read again
    f = fopen(filename, "r");
    fgets(buffer, sizeof(buffer), f);
    fclose(f);
    printf("Updated content: %s\n", buffer);

    // Delete the file
    if (remove(filename) == 0)
        printf("File deleted.\n");
    else
        printf("Delete failed.\n");

    // Check if the file exists
    f = fopen(filename, "r");
    printf("File exists: %s\n", (f != NULL) ? "Yes" : "No");
    if (f) fclose(f);

    return 0;
}