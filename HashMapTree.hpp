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
#include <iostream>

using namespace std;

template <typename K, typename V>
class HashMapTree {
private:
    struct TreeNode {
        K key;
        V value;
        TreeNode* left;
        TreeNode* right;
        int height;

        TreeNode(const K& k, const V& v)
            : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    TreeNode** table; 
    long slots;
    long size;
    const long DEFAULT_SLOTS = 1024;
    Hash<K> h;

    // Private helper functions for Complete binary tree operations
    TreeNode* insertTree(TreeNode* node, const K& key, const V& value);
    TreeNode* removeTree(TreeNode* node, const K& key);
    TreeNode* searchTree(TreeNode* node, const K& key);
    TreeNode* minValueNode(TreeNode* node);
    int getHeight(TreeNode* node);
    int getBalance(TreeNode* node);
    TreeNode* rotateRight(TreeNode* y);
    TreeNode* rotateLeft(TreeNode* x);
    void destroyTree(TreeNode* node);

public:
    HashMapTree();
    HashMapTree(long m);
    ~HashMapTree();

    void insert(const K& key, const V& value);
    void remove(const K& key);
    V& operator[](const K& key);
    V* search(const K& key);

};

#endif 
