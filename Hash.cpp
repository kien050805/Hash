#include "Hash.hpp"


template <class T>
Hash<T>::Hash ()
{
    m = 1;
};

template <class T>
Hash<T>::Hash (long slots)
{
    m = slots;
};

template <class T>
long Hash<T>::operator() (const T k)
{
    return k % m;
};