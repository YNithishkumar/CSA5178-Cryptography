#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/blowfish.h>

// Define a key for Blowfish encryption
static const char* key = "MySecretKey";

void encryptBlowfish(const char* plaintext, char* ciphertext) {
    BF_KEY bfKey;
    BF_set_key(&bfKey, strlen(key), (const unsigned char*)key);

    BF_ecb_encrypt((const unsigned char*)plaintext, (unsigned char*)ciphertext, &bfKey, BF_ENCRYPT);
}

void decryptBlowfish(const char* ciphertext, char* decryptedtext) {
    BF_KEY bfKey;
    BF_set_key(&bfKey, strlen(key), (const unsigned char*)key);

    BF_ecb_encrypt((const unsigned char*)ciphertext, (unsigned char*)decryptedtext, &bfKey, BF_DECRYPT);
}

int main() {
    const char* plaintext = "Hello, Blowfish!";
    char ciphertext[64];
    char decryptedtext[64];

    encryptBlowfish(plaintext, ciphertext);
    decryptBlowfish(ciphertext, decryptedtext);

    printf("Original: %s\n", plaintext);
    printf("Encrypted: %s\n", ciphertext);
    printf("Decrypted: %s\n", decryptedtext);

    return 0;
}

