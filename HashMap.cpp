//==============================================================
// HashMap.cpp
// Authors : Kien, Trinity, James
// 11/22/2024
//
// Description:
// This file contains the implementation of the HashMap class
// template
//==============================================================
#include <vector>
#include "HashMap.hpp"
#include "customexceptions.hpp"

template <class K, class V>
HashMap<K, V>::HashMap()
{
    size = 0;
    slots = DEFAULT_SLOTS;
    table = new Node *[slots];
    for (int i = 0; i < slots; i++)
    {
        table[i] = nullptr;
    };
    h = Hash<K>(slots);
};

template <class K, class V>
HashMap<K, V>::HashMap(long m)
{
    size = 0;
    slots = m;
    table = new Node *[slots];
    for (int i = 0; i < slots; i++)
    {
        table[i] = nullptr;
    };
    h = Hash<K>(slots);
};

template <class K, class V>
HashMap<K, V>::~HashMap()
{
    delete[] table;
};

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
    }

    table[slot] = temp;

    size++;
}

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
            break;
        };
        temp = temp->next;
    };
    size--;
};

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