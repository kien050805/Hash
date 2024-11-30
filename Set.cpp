//==============================================================
// Set.cpp
// Authors : Kien, Trinity, James
// 11/22/2024
//
// Description:
// This file contains the implementations of the Set class
//==============================================================

#include "Set.hpp"
#include "HashMap.hpp"
#include "Hash.hpp"

template <typename T>
Set<T>::Set()
{
}

template <typename T>
Set<T>::Set(const Set<T> &s)
{
    table = s.table;
    hasher = s.hasher;
}

template <typename T>
Set<T> Set<T>::operator=(const Set<T> &set)
{
    table = set.table;
    hasher = set.hasher;
    return *this;
}

template <typename T>
Set<T>::~Set()
{
}

template <typename T>
void Set<T>::insert(const T &value)
{
    if (!search(value))
    {
        size_t key = hasher(value);
        table.insert(key, value);
    }
}

template <typename T>
void Set<T>::remove(const T &value)
{
    size_t key = hasher(value);
    table.del(key);
}

template <typename T>
bool Set<T>::search(const T &value)
{
    size_t key = hasher(value);
    return (table.search(key) != nullptr);
}
