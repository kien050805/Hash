//========================================================
// James Bui & Kien Le & Trinity Meckel
// November 2024
// RBTree.hpp
// This header files defines the RBTree class template
//========================================================

#include <iostream>

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <utility>
#include "RBTreeNode.hpp"
#include "customexceptions.hpp"

namespace custom
{
    template <class K, class V>
    bool operator==(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first == p2.first;
    }
    template <class K, class V>
    bool operator!=(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first != p2.first;
    }
    template <class K, class V>
    bool operator<(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first < p2.first;
    }
    template <class K, class V>
    bool operator>(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first > p2.first;
    }
    template <class K, class V>
    bool operator<=(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first <= p2.first;
    }
    template <class K, class V>
    bool operator>=(const std::pair<K, V> &p1, const std::pair<K, V> &p2)
    {
        return p1.first >= p2.first;
    }
};

template <class T>
class RBTree
{
private:
    RBTreeNode<T> *root;
    RBTreeNode<T> *NIL = new RBTreeNode<T>();
    long rbt_size;

    bool is_balanced_helper(RBTreeNode<T> *node, int currentBlackHeight, int &expectedBlackHeight) const;

    void transplant(RBTreeNode<T> *oldNode, RBTreeNode<T> *newNode);
    void insert_fixup(RBTreeNode<T> *z);
    void delete_fixup(RBTreeNode<T> *node);
    void left_rotate(RBTreeNode<T> *node);
    void right_rotate(RBTreeNode<T> *node);
    void NIL_fixup();

    RBTreeNode<T> *copy(const RBTreeNode<T> *node, const RBTree<T> &tree);
    void deallocate(RBTreeNode<T> *node);

public:
    RBTree();
    RBTree(const RBTree<T> &tree);
    ~RBTree();
    RBTree<T> &operator=(const RBTree<T> &tree);

    bool isEmpty() const;
    long size() const;
    RBTreeNode<T> *search(const T &value);
    RBTreeNode<T> *treeMin() const;
    RBTreeNode<T> *treeMax() const;

    bool is_balanced() const;

    void printPreOrderTraversal() const;
    void printInOrderTraversal() const;
    void printPostOrderTraversal() const;

    RBTreeNode<T> *insert(T value);
    void remove(T value);
};

#include "RBTree.cpp"

#endif
