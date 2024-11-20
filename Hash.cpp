//========================================================
// James Bui & Kien Le & Trinity Meckel
// November 2024
// Hash.cpp
// This file contains the HashFunction class definitions.  
//========================================================

#include "Hash.hpp"
#include <cstdlib>
#include <functional>

template <class T>
Hash<T>::Hash ()
{
    a = rand() % p + 1;
    b = rand() % p;
};

template <class T>
Hash<T>::Hash (size_t slots, size_t prime)
{
    m = slots;
    p = prime;
    a = rand() % p + 1;
    b = rand() % p;
};

template <class T>
size_t Hash<T>::getHash (const T &key)
{
    std::hash<T> hasher;
    size_t hash = hasher(key);
    // Add b and reduce modulo p
    hash = (a*hash + b) % p;

    // Final modulo m
    return hash % m;
};