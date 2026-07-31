// Task 3 - Section 4: Encryption / Decryption

#include <stdio.h>
#include <string.h>

void xor_crypt(char *text, const char *key) {
    int key_len = strlen(key);

    for (int i = 0; text[i] != '\0'; i++)
        text[i] = text[i] ^ key[i % key_len];
}

int main(void) {
    char original[256] = "This is a confidential file.";
    char working[256];
    strcpy(working, original);

    const char *key = "mykey";

    printf("Original: %s\n", original);

    // Encrypt the text
    xor_crypt(working, key);

    printf("Encrypted: ");
    for (int i = 0; working[i] != '\0'; i++)
        printf("%02x ", (unsigned char)working[i]);
    printf("\n");

    // Decrypt the text
    xor_crypt(working, key);

    printf("Decrypted: %s\n", working);
    printf("Match: %s\n", strcmp(working, original) == 0 ? "Yes" : "No");

    return 0;
}