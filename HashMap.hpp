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
#include <utility>

using namespace std;

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "Hash.hpp"

template <class K, class V>
class HashMap
{
private:
    struct Node
    {
        pair<K, V> item;
        Node *next;
        Node *prev;
    };

    const size_t DEFAULT_SLOTS = 1024;
    size_t slots;
    long size;
    Node **table;
    Hash<K> h;

public:
    HashMap();
    HashMap(long m);
    ~HashMap();

    void insert(const K &key, const V &value);
    void remove(Node *D);
    void del(const K &key);
    V &operator[](const K &key);
    pair<K, V> *search(const K &key);
};

#include "HashMap.cpp"

#endif