#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

int main() {
    const char* input_string = "Hello, SHA-512!";
    unsigned char hash[SHA512_DIGEST_LENGTH];

    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, input_string, strlen(input_string));
    SHA512_Final(hash, &sha512);

    printf("Input String: %s\n", input_string);
    printf("SHA-512 Hash: ");
    for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}

