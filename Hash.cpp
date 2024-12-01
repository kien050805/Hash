//========================================================
// James Bui & Kien Le & Trinity Meckel
// November 2024
// Hash.cpp
// This file contains the HashFunction class definitions.  
//========================================================

#include "Hash.hpp"
#include <cstdlib>
#include <functional>
#include <iostream>

using namespace std;

template <typename T>
Hash<T>::Hash ()
{
    a = rand() % p + 1;
    b = rand() % p;
};

template <typename T>
Hash<T>::Hash (size_t slots, size_t prime)
{
    m = slots;
    p = prime;
    a = rand() % p + 1;
    b = rand() % p;
};

template <typename T>
size_t Hash<T>::getHash (const T &key)
{
    hash<T> hasher;
    size_t hash;
    if (sizeof(key) <= 8)
        hash = key;
    else
        hash = hasher(key);

    // Add b and reduce modulo p
    hash = (a*hash + b) % p;

    // Final modulo m
    return hash % m;
};

template <typename T>
size_t Hash<T>::operator() (const T k)
{
    return getHash(k);
};