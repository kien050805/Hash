#include "Hash.hpp"
#include <cstdlib>

template <class T>
Hash<T>::Hash ()
{
    a = rand() % p + 1;
    b = rand() % p;
};

template <class T>
Hash<T>::Hash (long slots)
{
    m = slots;
};

template <class T>
size_t Hash<T>::getHash (const T &key)
{
    const char* keyBytes = reinterpret_cast<const char*>(&key);
    size_t hash = 0;
    size_t keySize = sizeof(T);

    // Combine bytes into the hash using modular arithmetic
    for (size_t i = 0; i < keySize; ++i) {
        hash = (hash * a + static_cast<unsigned char>(keyBytes[i])) % p;
    }

    // Add b and reduce modulo p
    hash = (hash + b) % p;

    // Final modulo m
    return hash % m;
};