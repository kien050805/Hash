//========================================================
// James Bui & Kien Le & Trinity Meckel
// November 2024
// HashMapTree.cpp
// This file contains the implementation of the HashMapTree
// class template
//========================================================
#include <iostream>

using namespace std;

#ifndef HASHMAPTREE_HPP
#define HASHMAPTREE_HPP

#include <utility>
#include "RBTree.hpp"
#include "Hash.hpp"
#include "customexceptions.hpp"

template <class K, class V>
class HashMapTree
{
private:
    const size_t DEFAULT_SLOTS = 10000019;
    const size_t DEFAULT_PRIME = 1000003;
    long slots;
    long size;
    RBTree<pair<K, V> > *table;
    Hash<K> h;

public:
    HashMapTree();
    HashMapTree(size_t m);
    HashMapTree(const HashMapTree& copy);
    ~HashMapTree();
    HashMapTree<K, V>& operator=(const HashMapTree<K, V>& copy);

    void insert(const K &key, const V &value);
    void remove(const K &key);
    V &operator[](const K &key);
    pair<K, V> *search(const K &key);

};

#include "HashMapTree.cpp"

#endif
