//==============================================================
// Set.hpp
// Authors : Kien, Trinity, James
// 11/22/2024
//
// Description:
// This header file defines the Set class template 
//==============================================================
#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include "HashMap.hpp"

using namespace std;

template <typename T>
class Set {
private:
    HashMap<size_t, T> table;
    Hash<T> hasher;

public:
    Set();
    Set(const Set<T> &s);
    ~Set();
    Set<T> operator=(const Set<T> &tree);

    void insert(const T &value);
    void remove(const T &value);
    bool search(const T &value);
};

#endif 


