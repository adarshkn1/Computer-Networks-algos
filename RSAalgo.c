#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to find GCD
long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Modular exponentiation: (base^exp) % mod
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Step 1: Choose two prime numbers
    long long p = 61;
    long long q = 53;

    // Step 2: Compute n = p * q
    long long n = p * q;

    // Step 3: Compute Euler's Totient phi(n)
    long long phi = (p - 1) * (q - 1);

    // Step 4: Choose e (public key exponent)
    long long e = 17;

    // Step 5: Compute d (private key exponent)
    long long d;
    for (d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            break;
    }

    printf("Public Key: (e = %lld, n = %lld)\n", e, n);
    printf("Private Key: (d = %lld, n = %lld)\n\n", d, n);

    // Step 6: Open input file
    FILE *fin = fopen("input.txt", "r");
    if (!fin) {
        perror("Error opening input.txt");
        exit(EXIT_FAILURE);
    }

    FILE *fenc = fopen("encrypted.txt", "w");
    FILE *fdec = fopen("decrypted.txt", "w");
    if (!fenc || !fdec) {
        perror("Error opening output files");
        exit(EXIT_FAILURE);
    }

    // Step 7: Read from input.txt and encrypt each character
    printf("Encrypting file...\n");
    char ch;
    while ((ch = fgetc(fin)) != EOF) {
        long long encrypted_val = mod_exp(ch, e, n);
        fprintf(fenc, "%lld ", encrypted_val);
    }
    fclose(fin);
    fclose(fenc);
    printf("Encryption complete! Encrypted data saved in encrypted.txt\n");

    // Step 8: Decrypt from encrypted.txt
    printf("Decrypting file...\n");
    fenc = fopen("encrypted.txt", "r");
    if (!fenc) {
        perror("Error opening encrypted.txt");
        exit(EXIT_FAILURE);
    }

    long long val;
    while (fscanf(fenc, "%lld", &val) != EOF) {
        char decrypted_char = mod_exp(val, d, n);
        fputc(decrypted_char, fdec);
    }

    fclose(fenc);
    fclose(fdec);

    printf("Decryption complete! Decrypted data saved in decrypted.txt\n");

    return 0;
}