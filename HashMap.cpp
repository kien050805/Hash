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
    table = new vector<pair<K, V>>[slots];
    h = Hash<K>(slots);
};

template <class K, class V>
HashMap<K, V>::HashMap(long m)
{
    size = 0;
    slots = m;
    table = new vector<pair<K, V>>[slots];
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
    for (int i = 0; i < table[slot].size(); i++)
    {
        if (table[slot][i].first == key)
        {
            table[slot][i].second = value;
            return;
        }
    }

    table[slot].push_back(make_pair(key, value));
    size++;
};

template <class K, class V>
void HashMap<K, V>::remove(const K &key)
{
    long slot = h(key);
    for (int i = 0; i < table[slot].size(); i++)
    {
        if (table[slot][i].first == key)
        {
            table[slot].erase(table[slot].begin() + i);
        };
    };
    size--;
};

template <class K, class V>
V &HashMap<K, V>::operator[](const K &key)
{
    long slot = h(key);
    for (int i = 0; i < table[slot].size(); i++)
    {
        if (table[slot][i].first == key)
        {
            return table[slot][i].second;
        };
    };

    throw key_exception();
};

template <class K, class V>
pair<K, V> *HashMap<K, V>::search(const K &key)
{
    long slot = h(key);
    for (int i = 0; i < size; i++)
    {
        if (table[slot][i].first == key)
        {
            return table[slot][i];
        };
    };
};