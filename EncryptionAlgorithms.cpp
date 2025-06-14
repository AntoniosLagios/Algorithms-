// DES (Conceptual)
#include <iostream>
#include <bitset>

uint64_t simpleDES(uint64_t block, uint64_t key) {
    return block ^ key; // Simplified XOR for illustration
}

int main() {
    uint64_t block = 0b1100110011001100;
    uint64_t key =   0b1010101010101010;

    uint64_t encrypted = simpleDES(block, key);
    uint64_t decrypted = simpleDES(encrypted, key);

    std::cout << "Encrypted: " << std::bitset<16>(encrypted) << "\n";
    std::cout << "Decrypted: " << std::bitset<16>(decrypted) << "\n";
    return 0;
}
//RSA (Simplified version)
#include <iostream>
#include <cmath>

int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}


int main() {
    int p = 3, q = 11;
    int n = p * q;            // 33
    int phi = (p - 1) * (q - 1); // 20
    int e = 3; // public key
    int d = 7; // private key (modular inverse of e mod phi)

    int msg = 4;
    int encrypted = modExp(msg, e, n);
    int decrypted = modExp(encrypted, d, n);

    std::cout << "Encrypted: " << encrypted << "\n";
    std::cout << "Decrypted: " << decrypted << "\n";
    return 0;
}
//ECC (Elliptic Curve Cryptography)
#include <iostream>

struct Point {
    int x, y;
};

int mod = 17; // A small prime field
int a = 2, b = 2; // y^2 = x^3 + ax + b

Point add(Point P, Point Q) {
    int lambda = ((Q.y - P.y) * (int)std::pow(Q.x - P.x, -1)) % mod;
    int x_r = (lambda * lambda - P.x - Q.x) % mod;
    int y_r = (lambda * (P.x - x_r) - P.y) % mod;
    return { (x_r + mod) % mod, (y_r + mod) % mod };
}

int main() {
    Point P = {5, 1}, Q = {6, 3};
    Point R = add(P, Q);
    std::cout << "R = (" << R.x << ", " << R.y << ")\n";
    return 0;
}

//SHA-256 (Use library like OpenSSL or Crypto++)
#include <iostream>
#include <openssl/sha.h>
#include <iomanip>

void hashSHA256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)input.c_str(), input.size(), hash);
    
    std::cout << "SHA-256: ";
    for (unsigned char c : hash)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    std::cout << "\n";
}

int main() {
    hashSHA256("hello world");
    return 0;
}
//SHA-1
#include <iostream>
#include <openssl/sha.h>
#include <iomanip>
void hashSHA1(const std::string& input) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((const unsigned char*)input.c_str(), input.size(), hash);

    std::cout << "SHA-1: ";
    for (unsigned char c : hash)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    std::cout << "\n";
}

int main() {
    hashSHA1("hello world");
    return 0;
}
//RSA Digital Signature
#include <iostream>
#include <cmath>

int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
int main() {
    int p = 3, q = 11;
    int n = p * q;            // 33
    int phi = (p - 1) * (q - 1); // 20
    int e = 3; // Public key
    int d = 7; // Private key

    int message = 5;
    int hash = message; // In practice, you'd use SHA256 or similar

    // Signing (using private key)
    int signature = modExp(hash, d, n);

    // Verifying (using public key)
    int verifiedHash = modExp(signature, e, n);

    std::cout << "Signature: " << signature << "\n";
    std::cout << "Verified Hash: " << verifiedHash << "\n";
    std::cout << (verifiedHash == hash ? "Valid Signature" : "Invalid Signature") << "\n";

    return 0;
}
//ECDSA (Conceptual simulation)
#include <iostream>
#include <string>

struct ECDSAPublicKey {
    int x; // pretend it's a point on a curve
};

struct ECDSAPrivateKey {
    int d; // private key scalar
};

// Fake hash for demo
int hash(const std::string& msg) {
    int h = 0;
    for (char c : msg) h += c;
    return h % 101;
}

int sign(const std::string& msg, const ECDSAPrivateKey& priv) {
    int h = hash(msg);
    return (h * priv.d) % 101; // Simplified
}

bool verify(const std::string& msg, int signature, const ECDSAPublicKey& pub) {
    int h = hash(msg);
    return ((signature * pub.x) % 101) == h;
}

int main() {
    std::string message = "hello";
    ECDSAPrivateKey priv{5};
    ECDSAPublicKey pub{61}; // pretend public key is derived

    int signature = sign(message, priv);
    bool valid = verify(message, signature, pub);

    std::cout << "Signature: " << signature << "\n";
    std::cout << (valid ? "Valid Signature" : "Invalid Signature") << "\n";

    return 0;
}
