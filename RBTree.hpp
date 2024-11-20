//=========================================================
// RBTree.hpp
// Son Nguyen, James Bui
// Nov, 2024
// This is the header file with definitions of functions for the RBTree class:
//=========================================================

#include "RBTreeNode.hpp"
#ifndef RBTREE_HPP
#define RBTREE_HPP

template<class T>
class RBTree {
    private:
        RBTreeNode<T>* root;
        bool is_balanced_helper(RBTreeNode<T> *node, int currentBlackHeight, int &expectedBlackHeight);
        
    public: 
    // Constructors and Destructor
    RBTree();
    RBTree(const RBTree<T> &tree);
    ~RBTree();
    RBTree<T>& operator=(const RBTree<T> &tree);
    void transplant(RBTreeNode<T>* oldNode, RBTreeNode<T>* newNode);
    bool isEmpty() const;
    long size() const;
    RBTreeNode<T>* insert(T value);
    void remove(T value);
    RBTreeNode<T>* search(T value) const;
    RBTreeNode<T>* treeMin() const;
    RBTreeNode<T>* treeMax() const;
    void printPreOrderTraversal() const;
    void printInOrderTraversal() const;
    void printPostOrderTraversal() const;
    void insert_fixup(RBTreeNode<T>* z);
    void delete_fixup(RBTreeNode<T>* node);
    void left_rotate(RBTreeNode<T>* node);
    void right_rotate(RBTreeNode<T>* node);
    long getSize(RBTreeNode<T>* node) const;
    bool is_balanced();

};

#include "RBTree.cpp"

#endif