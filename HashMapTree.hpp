//==============================================================
// HashMapTree.hpp
// Authors : Kien, Trinity, James
// 11/22/2024
//
// Description:
// This header file defines the HashMapTree class template 
//==============================================================
#ifndef HASHMAPTREE_HPP
#define HASHMAPTREE_HPP

#include <vector>
#include <iostream>
#include "RBTree.hpp"

using namespace std;

template <typename K, typename V>
class HashMapTree {
private:
   
    const long DEFAULT_SLOTS = 1024;
    long slots;
    long size;
    Hash<K> h;
    vector<RBTree<pair<K, V>>> table;

public:
    HashMapTree();
    HashMapTree(long m);
    ~HashMapTree();

    void insert(const K& key, const V& value);
    void remove(const K& key);
    V& operator[](const K& key);
    V* search(const K& key);

};

#endif 
