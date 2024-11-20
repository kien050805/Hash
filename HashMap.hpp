//==============================================================
// HashMap.hpp
// Authors : Kien, Trinity, James
// 11/22/2024
//
// Description:
// This header file defines the HashMap class template
//==============================================================
#include <iostream>
#include <vector>

using namespace std;

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "Hash.hpp"

template <class K, class V>
class HashMap
{
private:
    const long DEFAULT_SLOTS = 1024;
    long slots;
    long size;
    vector<pair<K, V>> *table;
    Hash<K> h;

public:
    HashMap();
    HashMap(long m);
    ~HashMap();

    void insert(const K &key, const V &value);
    void remove(const K &);
    V &operator[](const K &key);
    pair<K, V> *search(const K &key);
};

#endif