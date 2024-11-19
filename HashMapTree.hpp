//==============================================================
// HashMapTree.hpp
// Authors : Kien, Trinity, James
// 11/22/2024
//
// Description:
// This header file defines the HashMapTree class template 
//==============================================================
#ifndef HASHMAPTREE_HPP
#define HASHMAPTREE_HPP

#include <vector>
#include <utility> 
#include <stdexcept>
#include <iostream>
#include <functional>

using namespace std;

template <typename K, typename V>
class HashMapTree {
private:
    struct TreeNode {
        K key;
        V value;
        TreeNode* left;
        TreeNode* right;

        TreeNode(const K& key, const V& value)
            : key(key), value(value), left(nullptr), right(nullptr) {}
    };

    vector<TreeNode*> table; // Hash table with BSTs in each bucket
    size_t tableSize;        // Number of buckets
    size_t numElements;      // Number of key-value pairs

    size_t hash(const K& key) const {
        return hash<K>()(key) % tableSize; // Hashing function
    }

    TreeNode* insertNode(TreeNode* root, const K& key, const V& value);
    TreeNode* removeNode(TreeNode* root, const K& key);
    TreeNode* findMin(TreeNode* root) const;
    TreeNode* searchNode(TreeNode* root, const K& key) const;
    void deleteTree(TreeNode* root);

public:
    HashMapTree(size_t size = 101);
    ~HashMapTree();

    void insert(const K& key, const V& value);
    void remove(const K& key);
    V& operator[](const K& key);
    pair<K, V>* search(const K& key);

    size_t size() const { return numElements; }
    size_t capacity() const { return tableSize; }
};

#endif 
