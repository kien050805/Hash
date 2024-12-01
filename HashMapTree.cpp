//========================================================
// James Bui & Kien Le & Trinity Meckel
// November 2024
// HashMapTree.cpp
// This file includes the implementation of the HashMapTree
// class template
//========================================================
#include <iostream>
#include "HashMapTree.hpp"

using namespace std;

template <class K, class V>
HashMapTree<K, V>::HashMapTree()
{
    size = 0;
    slots = DEFAULT_SLOTS;
    h = Hash<K>(slots, DEFAULT_PRIME);
    table = new RBTree<pair<K, V>>[slots];
};

template <class K, class V>
HashMapTree<K, V>::HashMapTree(size_t m)
{
    size = 0;
    slots = m;
    h = Hash<K>(slots, DEFAULT_PRIME);
    table = new RBTree<pair<K, V>>[slots];
};

template <class K, class V>
HashMapTree<K, V>::~HashMapTree()
{
    delete[] table;
};

template<class K, class V>
HashMapTree<K, V>::HashMapTree(const HashMapTree& copy) {
    if (this != &copy) {
        size = copy.size;
        h = copy.h;
        table = copy.table;
    }
}

template<class K, class V>
HashMapTree<K, V>& HashMapTree<K, V>::operator=(const HashMapTree<K, V>& copy) {
    if (this != &copy) {
        size = copy.size;
        h = copy.h;
        table = copy.table;
    }
    return *this;
}

template <class K, class V>
void HashMapTree<K, V>::insert(const K &key, const V &value)
{

    size_t slot = h(key);
    pair<K, V> temp(key, value);
    RBTreeNode<pair<K, V>> *check_temp = table[slot].search(temp);
    if (check_temp == nullptr)
    {
        table[slot].insert(temp);
        size++;
    }
    else
    {
        table[slot].remove(*check_temp->value());
        table[slot].insert(temp);
    };
}
template <class K, class V>
void HashMapTree<K, V>::remove(const K &key)
{
    size_t slot = h(key);
    pair<K, V> temp(key, V());
    if (table[slot].search(temp) != nullptr)
    {
        table[slot].remove(temp);
        size--;
    }
    else
    {
        throw key_exception("Key Not Found");
    }
};

template <class K, class V>
V &HashMapTree<K, V>::operator[](const K &key)
{
    size_t slot = h(key);
    pair<K, V> temp(key, V());
    RBTreeNode<pair<K, V>> *item = table[slot].search(temp);
    if (item != nullptr)
    {
        V ans = item->value().second();
        return ans;
    }
    throw key_exception("Key Not Found");
};

template <class K, class V>
pair<K, V> *HashMapTree<K, V>::search(const K &key)
{
    size_t slot = h(key);
    pair<K, V> temp(key, V());
    RBTreeNode<pair<K, V>> *item = table[slot].search(temp);
    if (item == nullptr)
    {
        return nullptr;
    };
    
    return item->value();
};
