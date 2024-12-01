#include <iostream>
#include "HashMapTree.hpp"

using namespace std;

template <class K, class V>
HashMapTree<K, V>::HashMapTree()
{
    size = 0;
    slots = DEFAULT_SLOTS;
    h = Hash<K>(slots, slots);
    table = new RBTree<pair<K, V>>[slots];
};

template <class K, class V>
HashMapTree<K, V>::HashMapTree(long m)
{
    size = 0;
    slots = m;
    h = Hash<K>(slots, slots);
    table = new RBTree<pair<K, V>>[slots];
};

template <class K, class V>
HashMapTree<K, V>::~HashMapTree()
{
    delete[] table;
};

template <class K, class V>
void HashMapTree<K, V>::insert(const K &key, const V &value)
{

    long slot = h(key);
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
    long slot = h(key);
    pair<K, V> temp(key, V());
    if (table[slot].search(temp) != nullptr)
    {
        table[slot].remove(temp);
        size--;
    }
    else
    {
        throw key_exception();
    }
};

template <class K, class V>
V &HashMapTree<K, V>::operator[](const K &key)
{
    long slot = h(key);
    pair<K, V> temp(key, V());
    RBTreeNode<pair<K, V>> *item = table[slot].search(temp);
    if (item != nullptr)
    {
        V ans = item->value().second();
        return ans;
    }
    throw key_exception();
};

template <class K, class V>
pair<K, V> *HashMapTree<K, V>::search(const K &key)
{
    long slot = h(key);
    pair<K, V> temp(key, V());
    RBTreeNode<pair<K, V>> *item = table[slot].search(temp);
    if (item == nullptr)
    {
        return nullptr;
    };
    
    return item->value();
};
