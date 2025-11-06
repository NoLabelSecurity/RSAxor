/* ===============================================================
 *                          RSAxor
 * ===============================================================
 *  Developer:        Brian Lorick
 *  Organization:     No/Label Security Services & Solutions
 *  Created On:       02/05/2025
 *  Last Modified:    10/20/2025
 *  Version:          1.0.0
 *
 *  Description:
 *      Educational simulation demonstrating hybrid encryption
 *      using RSA (asymmetric) for key exchange and XOR-based
 *      AES-like symmetric encryption for data. This version runs
 *      in any standard C compiler without requiring OpenSSL or
 *      external libraries.
 *
 *  Features:
 *      - RSA key generation, encryption, and decryption (simulated)
 *      - XOR-based symmetric encryption (AES-like)
 *      - Modular exponentiation implementation
 *      - Step-by-step console interaction with clear output
 *
 *  Usage:
 *      1. Compile using `make run` or manually with:
 *         `gcc -Wall -o build/RSAxor src/main.c`
 *      2. Enter plaintext when prompted.
 *      3. Observe RSA parameter generation, key exchange,
 *         encryption, and decryption steps.
 *
 *  Notes:
 *      - For EDUCATIONAL USE ONLY — not secure for real cryptographic use.
 *      - Simple arithmetic and bitwise operations replace actual crypto algorithms.
 *
 *  License:
 *      MIT License
 * =============================================================== */

#include <stdio.h>              // Standard input/output library
#include <stdlib.h>             // Standard library for memory management
#include <string.h>             // String manipulation functions
#include <math.h>               // Math library for power functions

// ---------------------------------------------------------------------------
// VARIABLE AND CONSTANT DECLARATIONS
// ---------------------------------------------------------------------------

const int RSA_P = 61;                        // First prime number for RSA
const int RSA_Q = 53;                        // Second prime number for RSA
const int RSA_E = 17;                        // Public exponent (commonly used)
int rsaN;                                    // RSA modulus (n = p * q)
int rsaPhi;                                  // Euler's totient (phi = (p-1)*(q-1))
int rsaD;                                    // RSA private exponent

char plaintext[128];                         // User input plaintext
char ciphertext[128];                        // Encrypted ciphertext
char decryptedText[128];                     // Decrypted text
char aesKey = 'K';                           // Simple XOR key for "AES" simulation

// ---------------------------------------------------------------------------
// FUNCTION DECLARATIONS
// ---------------------------------------------------------------------------

// Function to compute GCD (Greatest Common Divisor)
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;                        // Store b temporarily
        b = a % b;                           // Set b to remainder
        a = temp;                            // Set a to old b
    }
    return a;                                // Return greatest common divisor
}

// Function to compute modular exponentiation (base^exp % mod)
int modExp(int base, int exp, int mod)
{
    long long result = 1;                    // Initialize result
    base = base % mod;                       // Reduce base modulo n
    while (exp > 0)
    {
        if (exp % 2 == 1)                    // If exponent is odd
        {
            result = (result * base) % mod;  // Multiply by base
        }
        exp = exp / 2;                       // Divide exponent by 2
        base = (base * base) % mod;          // Square the base
    }
    return (int)result;                      // Return result modulo mod
}

// Function to perform XOR-based "AES" encryption/decryption
void xorEncryptDecrypt(char *input, char *output, char key)
{
    for (int i = 0; i < strlen(input); i++)  // Loop through input string
    {
        output[i] = input[i] ^ key;          // XOR each byte with key
    }
    output[strlen(input)] = '\0';            // Null-terminate output
}

// Function to find modular multiplicative inverse of e mod phi
int modInverse(int e, int phi)
{
    int t1 = 0, t2 = 1, r1 = phi, r2 = e;    // Extended Euclidean algorithm variables
    while (r2 > 0)
    {
        int q = r1 / r2;                     // Quotient
        int t = t1 - q * t2;                 // Update t
        t1 = t2;                             // Shift t values
        t2 = t;                              // Shift t values
        int r = r1 - q * r2;                 // Update remainder
        r1 = r2;                             // Shift r values
        r2 = r;                              // Shift r values
    }
	
    if (t1 < 0)
    {
        t1 += phi;                           // Ensure positive result
    }
    return t1;                               // Return modular inverse
}

// ---------------------------------------------------------------------------
// MAIN FUNCTION
// ---------------------------------------------------------------------------
int main()
{
    // Step 1: Compute RSA parameters
    rsaN = RSA_P * RSA_Q;                    // Compute modulus n = p * q
    rsaPhi = (RSA_P - 1) * (RSA_Q - 1);      // Compute Euler's totient phi
    rsaD = modInverse(RSA_E, rsaPhi);        // Compute private exponent d

    // Display RSA parameters
    printf("RSA Parameters:\n");
    printf("  p = %d, q = %d\n", RSA_P, RSA_Q);
    printf("  n = %d, phi = %d\n", rsaN, rsaPhi);
    printf("  e = %d, d = %d\n\n", RSA_E, rsaD);

    // Step 2: Get plaintext input
    printf("Enter plaintext message: ");
    fgets(plaintext, sizeof(plaintext), stdin);              // Get user input
    plaintext[strcspn(plaintext, "\n")] = 0;                 // Remove newline

    // Step 3: "AES" (XOR) encryption
    xorEncryptDecrypt(plaintext, ciphertext, aesKey);        // Encrypt plaintext
    printf("\nAES Encrypted (XOR) Ciphertext: ");
    for (int i = 0; i < strlen(ciphertext); i++)             // Print in hex
    {
        printf("%02X ", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    // Step 4: RSA encryption of AES key
    int rsaEncryptedKey = modExp((int)aesKey, RSA_E, rsaN);  // Encrypt AES key
    printf("RSA Encrypted AES Key: %d\n", rsaEncryptedKey);

    // Step 5: RSA decryption of AES key
    int rsaDecryptedKey = modExp(rsaEncryptedKey, rsaD, rsaN); // Decrypt AES key
    printf("RSA Decrypted AES Key: %c\n\n", (char)rsaDecryptedKey);

    // Step 6: AES decryption using decrypted AES key
    xorEncryptDecrypt(ciphertext, decryptedText, (char)rsaDecryptedKey); // Decrypt ciphertext
    printf("Decrypted Text: %s\n", decryptedText);

    // Step 7: Program complete
    return 0;                                               // Exit successfully
}
