#include <iostream>

using namespace std;

#ifndef HASH_HPP
#define HASH_HPP

template <class T>
class Hash
{
private:
    long m;

public:
    Hash ();
    Hash(long slots);
    long operator()(const T k);
};

#endif