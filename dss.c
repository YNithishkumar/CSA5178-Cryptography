#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

#define MESSAGE "Hello, Digital Signature!"

// Function to generate a digital signature
int generateSignature() {
    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();

    // Load private key
    EVP_PKEY* private_key = NULL;
    FILE* private_key_file = fopen("private_key.pem", "r");
    if (!private_key_file) {
        perror("Error opening private key file");
        return 1;
    }
    private_key = PEM_read_PrivateKey(private_key_file, NULL, NULL, NULL);
    fclose(private_key_file);
    if (!private_key) {
        perror("Error loading private key");
        return 1;
    }

    // Create a message digest
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        perror("Error creating message digest context");
        return 1;
    }

    if (EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, private_key) != 1) {
        perror("Error initializing message digest");
        return 1;
    }

    // Add data to the message digest
    if (EVP_DigestSignUpdate(mdctx, MESSAGE, strlen(MESSAGE)) != 1) {
        perror("Error adding data to message digest");
        return 1;
    }

    // Get the digital signature
    unsigned char signature[4096];
    size_t signature_len = sizeof(signature);
    if (EVP_DigestSignFinal(mdctx, signature, &signature_len) != 1) {
        perror("Error getting digital signature");
        return 1;
    }

    // Print the digital signature
    printf("Digital Signature:\n");
    for (size_t i = 0; i < signature_len; i++) {
        printf("%02x", signature[i]);
    }
    printf("\n");

    // Clean up
    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(private_key);

    return 0;
}

int main() {
    if (generateSignature() != 0) {
        fprintf(stderr, "Error generating digital signature\n");
        return 1;
    }

    return 0;
}

