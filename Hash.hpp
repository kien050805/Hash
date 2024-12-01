//========================================================
// James Bui & Kien Le & Trinity Meckel
// November 2024
// Hash.hpp
// This file contains the HashFunction class declaration.  
//========================================================

#include <iostream>

using namespace std;

#ifndef HASH_HPP
#define HASH_HPP

template <class T>
class Hash
{
private:
    size_t p = 37;
    size_t m = 101;
    size_t a, b;

public:
    Hash ();
    Hash (size_t slots, size_t prime);
    size_t getHash(const T &key);
    size_t operator()(const T k);
};

#include "Hash.cpp"

#endif