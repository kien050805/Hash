//========================================================
// James Bui & Kien Le & Trinity Meckel
// November 2024
// HashMap.cpp
// This file contains the implementation of the HashMap class
// template
//==============================================================
#include <vector>
#include "HashMap.hpp"
#include "customexceptions.hpp"

/**
 * @brief Construct a new Hash Map<K,V>:: Hash Map object
 *
 * @tparam K: templated key data type
 * @tparam V: templated value data type
 */
template <class K, class V>
HashMap<K, V>::HashMap()
{
    size = 0;
    slots = DEFAULT_SLOTS;
    h = Hash<K>(slots, slots);

    table = new Node *[slots];
    for (int i = 0; i < slots; i++)
    {
        table[i] = nullptr;
    };
};

/**
 * @brief Construct a new Hash Map<K,V>:: Hash Map object
 *
 * @tparam K: templated key data type
 * @tparam V: templated value data type
 * @param m: number of hash table slots
 */
template <class K, class V>
HashMap<K, V>::HashMap(long m)
{
    if (m < 0)
    {
        throw size_exception();
    };

    size = 0;
    slots = m;
    h = Hash<K>(slots, slots);

    table = new Node *[slots];
    for (int i = 0; i < slots; i++)
    {
        table[i] = nullptr;
    };
};

/**
 * @brief Destroy the Hash Map<K,V>:: Hash Map object
 *
 * @tparam K: templated key data type
 * @tparam V: templated value data type
 */
template <class K, class V>
HashMap<K, V>::~HashMap()
{
    for (int i = 0; i < slots; i++)
    {
        Node *ptr = table[i];
        while (ptr != nullptr)
        {
            Node *temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
    }
    delete[] table;
}

/**
 * @brief Insert the item <K, V> into the hash table
 * 
 * @tparam K: templated key data type
 * @tparam V: templated value data type
 * @param key: item key
 * @param value: item value
 */
template <class K, class V>
void HashMap<K, V>::insert(const K &key, const V &value)
{
    long slot = h(key);

    Node *temp = table[slot];
    while (temp != nullptr)
    {
        if (temp->item.first == key)
        {
            temp->item.second = value;
            return;
        }
        temp = temp->next;
    }

    temp = new Node;
    temp->item = make_pair(key, value);
    temp->next = table[slot];
    temp->prev = nullptr;
    if (table[slot] != nullptr)
    {
        table[slot]->prev = temp;
    };
    table[slot] = temp;

    size++;
}

/**
 * @brief Remove the node D from the hash table
 * 
 * @tparam K: templated key data type
 * @tparam V: templated value data type
 * @param D: Pointer to the node to be deleted
 */
template <class K, class V>
void HashMap<K, V>::remove(Node *D)
{
    long slot = h(D->item.first);

    if (D->prev == nullptr && D->next == nullptr)
    {
        table[slot] = nullptr;
    }
    else if (D->prev == nullptr)
    {
        table[slot] = D->next;
        D->next->prev = nullptr;
    }

    else if (D->next == nullptr)
    {
        D->prev->next = nullptr;
    }

    else
    {
        D->prev->next = D->next;
        D->next->prev = D->prev;
    }

    delete D;
}

/**
 * @brief Delete the item with key from the hash table
 * 
 * @tparam K: templated key data type
 * @tparam V: templated value data type
 * @param key: key of the item to be deleted
 */
template <class K, class V>
void HashMap<K, V>::del(const K &key)
{
    long slot = h(key);
    Node *temp = table[slot];
    while (temp != nullptr)
    {
        if (temp->item.first == key)
        {
            remove(temp);
            size--;
            return;
        };
        temp = temp->next;
    };

    throw key_exception();
};

/**
 * @brief Access the item with key in the hash table
 * 
 * @tparam K: templated key data type
 * @tparam V: templated value data type
 * @param key: key of the item to access
 * @return V&: Value of the item with the given key
 */
template <class K, class V>
V &HashMap<K, V>::operator[](const K &key)
{
    long slot = h(key);
    Node *temp = table[slot];
    while (temp != nullptr)
    {
        if (temp->item.first == key)
        {
            return temp->item.second;
        };
        temp = temp->next;
    };

    throw key_exception();
};

/**
 * @brief Search the item with key in the hash table
 * 
 * @tparam K: templated key data type
 * @tparam V: templated value data type
 * @param key: key of the item to search for
 * @return pair<K, V>*: pointer to the item pair
 */
template <class K, class V>
pair<K, V> *HashMap<K, V>::search(const K &key)
{
    long slot = h(key);
    Node *temp = table[slot];
    while (temp != nullptr)
    {
        if (temp->item.first == key)
        {
            return &temp->item;
        };
        temp = temp->next;
    };

    return nullptr;
};
