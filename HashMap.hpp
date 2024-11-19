//==============================================================
// HashMap.hpp
// Authors : Kien, Trinity, James
// 11/22/2024
//
// Description:
// This header file defines the HashMap class template
//==============================================================

#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <vector>
#include <list>
#include <utility>
#include <stdexcept>
#include <iostream>
using namespace std;

template <typename K , typename V>
class HashMap {
private: 
  size_t tableSize; // Number of buckets in each hash table
  size_t numElements; // Number of key-value pairs in map 
  vector<list<pair<K , V>>> table; // Hash table implemented with chaining

  // Custom hash function
  size_t hash(const K &key) const {
    return hash<K>()(key); 
  }
public:
  HashMap(size_t size = 101)
    : tableSize(size), numElements(0), table(size) {}

  void insert(const K &key const V &value);
  void remove(const K &key);
  V& operator[] (const K &key);
  pair<K , V>* search(const K &key)

  size_t size() const { return numElements; }
  size_t capacity() const { return tableSize; }

};

#endif // HASHMAP_HPP






