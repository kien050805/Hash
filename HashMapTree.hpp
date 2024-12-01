//==============================================================
// HashMapTree.cpp
// Authors : Kien, Trinity, James
// 11/22/2024
//
// Description:
// This file contains the implementation of the HashMapTree
// class template
//==============================================================
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
    const long DEFAULT_SLOTS = 1024;
    long slots;
    long size;
    RBTree<pair<K, V> > *table;
    Hash<K> h;

public:
    HashMapTree();
    HashMapTree(long m);
    ~HashMapTree();

    void insert(const K &key, const V &value);
    void remove(const K &key);
    V &operator[](const K &key);
    pair<K, V> *search(const K &key);

};

#include "HashMapTree.cpp"

#endif