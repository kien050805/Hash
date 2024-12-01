//========================================================
// James Bui & Kien Le & Trinity Meckel
// November 2024
// Set.cpp
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
Set<T>::Set(size_t table_size)
{
    table(table_size);
}

template <typename T>
Set<T>::Set(const Set<T> &s)
{
    table = s.table;
}

template <typename T>
Set<T> Set<T>::operator=(const Set<T> &set)
{
    table = set.table;
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
        table.insert(value, value);
    }
}

template <typename T>
void Set<T>::remove(const T &value)
{
    table.del(value);
}

template <typename T>
bool Set<T>::search(const T &value)
{
    return (table.search(value) != nullptr);
}
