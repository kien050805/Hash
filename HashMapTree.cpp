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

//==============================================================
// HashMapTree
// Default constructor for the HashMapTree class. Initializes the 
// hash table with the default number of slots and a hash function.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
template <class K, class V>
HashMapTree<K, V>::HashMapTree()
{
    size = 0;
    slots = DEFAULT_SLOTS;
    h = Hash<K>(slots, DEFAULT_PRIME);
    table = new RBTree<pair<K, V>>[slots];
};

//==============================================================
// HashMapTree
// Parameterized constructor for the HashMapTree class. Initializes 
// the hash table with a given number of slots and a hash function.
// PARAMETERS:
// - m: number of slots for the hash table
// RETURN VALUE:
// - none
//==============================================================
template <class K, class V>
HashMapTree<K, V>::HashMapTree(size_t m)
{
    size = 0;
    slots = m;
    h = Hash<K>(slots, DEFAULT_PRIME);
    table = new RBTree<pair<K, V>>[slots];
};

//==============================================================
// ~HashMapTree
// Destructor for the HashMapTree class. Frees the memory allocated
// for the hash table.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
template <class K, class V>
HashMapTree<K, V>::~HashMapTree()
{
    delete[] table;
};

//==============================================================
// HashMapTree
// Copy constructor for the HashMapTree class. Creates a new object
// as a copy of an existing HashMapTree.
// PARAMETERS:
// - copy: the HashMapTree to copy from
// RETURN VALUE:
// - none
//==============================================================
template<class K, class V>
HashMapTree<K, V>::HashMapTree(const HashMapTree& copy) {
    if (this != &copy) {
        size = copy.size;
        h = copy.h;
        table = copy.table;
    }
}

//==============================================================
// operator=
// Assignment operator for the HashMapTree class. Assigns the values
// of another HashMapTree to this one.
// PARAMETERS:
// - copy: the HashMapTree to assign from
// RETURN VALUE:
// - reference to the current object
//==============================================================
template<class K, class V>
HashMapTree<K, V>& HashMapTree<K, V>::operator=(const HashMapTree<K, V>& copy) {
    if (this != &copy) {
        size = copy.size;
        h = copy.h;
        table = copy.table;
    }
    return *this;
}

//==============================================================
// insert
// Inserts a key-value pair into the hash map tree. If the key 
// already exists, the value is updated.
// PARAMETERS:
// - key: key of the item to insert
// - value: value of the item to insert
// RETURN VALUE:
// - none
//==============================================================
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

//==============================================================
// remove
// Removes the key-value pair associated with the provided key 
// from the hash map tree.
// PARAMETERS:
// - key: key of the item to remove
// RETURN VALUE:
// - none
// EXCEPTIONS:
// - throws key_exception if the key is not found
//==============================================================
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

//==============================================================
// operator[]
// Accesses the value associated with the given key. If the key 
// is found, returns the corresponding value. Throws an exception 
// if the key is not found.
// PARAMETERS:
// - key: key of the item to access
// RETURN VALUE:
// - reference to the value associated with the key
// EXCEPTIONS:
// - throws key_exception if the key is not found
//==============================================================
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

//==============================================================
// search
// Searches for the key-value pair associated with the given key 
// in the hash map tree and returns a pointer to the pair.
// PARAMETERS:
// - key: key of the item to search for
// RETURN VALUE:
// - pointer to the key-value pair if found, nullptr if not found
//==============================================================
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


