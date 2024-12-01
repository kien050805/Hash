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

//==============================================================
// HashMap
// Default constructor for the HashMap class. Initializes the 
// hash table with the default number of slots and a hash function.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
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

//==============================================================
// HashMap
// Parameterized constructor for the HashMap class. Initializes 
// the hash table with a custom number of slots and a hash function.
// PARAMETERS:
// - m: Number of hash table slots.
// RETURN VALUE:
// - none
//==============================================================
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

//==============================================================
// ~HashMap
// Destructor for the HashMap class. Deletes all nodes in the hash 
// table and frees the allocated memory for the table.
// PARAMETERS:
// - none
// RETURN VALUE:
// - none
//==============================================================
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

//==============================================================
// insert
// Inserts a new item (key, value) into the hash table. If the 
// key already exists, updates the value.
// PARAMETERS:
// - key: The key of the item to insert.
// - value: The value of the item to insert.
// RETURN VALUE:
// - none
//==============================================================
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

//==============================================================
// remove
// Removes a specific node (D) from the hash table.
// PARAMETERS:
// - D: Pointer to the node to remove from the hash table.
// RETURN VALUE:
// - none
//==============================================================
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

//==============================================================
// del
// Deletes the item with the specified key from the hash table.
// PARAMETERS:
// - key: The key of the item to delete.
// RETURN VALUE:
// - none
//==============================================================
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

//==============================================================
// operator[]
// Accesses the value associated with the specified key. If the 
// key does not exist, throws an exception.
// PARAMETERS:
// - key: The key of the item to access.
// RETURN VALUE:
// - V&: The value associated with the given key.
//==============================================================
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

//==============================================================
// search
// Searches for the item with the given key in the hash table. 
// Returns a pointer to the key-value pair if found, otherwise 
// returns nullptr.
// PARAMETERS:
// - key: The key of the item to search for.
// RETURN VALUE:
// - pair<K, V>*: Pointer to the item (key-value pair), or nullptr if not found.
//==============================================================
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

