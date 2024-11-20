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
    Hash(long slots);
    size_t getHash(const T &key);
};

#endif