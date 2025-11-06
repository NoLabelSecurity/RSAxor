# 🔐 RSAxor — Hybrid Data Encryption/Decryption Tool

**Developer:** Brian Lorick  
**Organization:** No/Label Security Services & Solutions  
**Version:** 1.0.0  
**License:** MIT License  

---

## 📘 Overview

**RSAxor** is an **educational C program** that demonstrates the basic concept of hybrid encryption — combining **RSA asymmetric encryption** for key exchange and a simple **XOR-based symmetric encryption** (AES-like) for data protection.

This simulation works in any standard C compiler, including [OnlineGDB](https://www.onlinegdb.com/), and **does not require OpenSSL** or any external libraries.

> ⚠️ **Disclaimer:** This tool is for *educational purposes only* and is **not suitable for real cryptographic use**.

---

## 🧠 Concept

Hybrid encryption systems use both:
1. **Asymmetric encryption (RSA)** — for securely exchanging a key.
2. **Symmetric encryption (AES/XOR)** — for encrypting actual data efficiently.

RSAxor simulates this process:
- RSA is used to encrypt a symmetric "AES" key.
- The "AES" encryption is performed using XOR operations.

---

## 🧩 Features

- 🔢 **RSA key generation** (p, q, e, d) using modular arithmetic  
- 🔐 **XOR-based symmetric cipher** (AES-like simulation)  
- 🧮 **Modular exponentiation** implementation for RSA math  
- 💬 **Interactive input/output** for plaintext entry and encryption results  
- 📜 **Fully commented C source code** for educational study  

---

## ⚙️ Usage

### 🏗️ Build and Run

#### Using Makefile
```bash
make run
```

#### Manual Compilation
```bash
gcc -Wall -Iinclude src/main.c -o build/RSAxor
./build/RSAxor
```

---

## 💻 Sample Run (Example Output)

```text
RSA Parameters:
  p = 61, q = 53
  n = 3233, phi = 3120
  e = 17, d = 2753

Enter plaintext message: hello

AES Encrypted (XOR) Ciphertext: 03 0E 07 07 04 
RSA Encrypted AES Key: 2496
RSA Decrypted AES Key: K

Decrypted Text: hello
```

---

## 🧩 File Structure

```
RSAxor/
├── src/        → source files (main.c)
├── include/    → header files (optional)
├── build/      → compiled output
├── tests/      → test files
├── Makefile    → build system
├── README.md   → documentation
├── LICENSE     → MIT license
└── .gitignore  → ignore build artifacts
```

---

## 🧾 Notes

- This project is designed to **illustrate encryption concepts** in a readable, portable C implementation.  
- All cryptographic steps are simplified for **educational clarity**, not for security.  
- Easily extendable for experimenting with other algorithms.

---

## 📄 License

This project is licensed under the **MIT License**.  
© 2025 Brian Lorick — No/Label Security Services & Solutions
