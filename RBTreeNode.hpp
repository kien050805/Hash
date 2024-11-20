//=========================================================
// RBTreeNode.hpp
// Son Nguyen, James Bui
// Nov, 2024
// This is the header file with definitions of functions for the RBTreeNode class:
// treeMin, treeMax, printPreOrderTraversal, printInOrderTraversal, printPostOrderTraversal
//=========================================================
#include <iostream>
using namespace std;

#ifndef RBTREENODE_HPP
#define RBTREENODE_HPP

enum Color { RED, BLACK };

template<class T>
class RBTreeNode {
    public: 

    // Values
    T val;
    RBTreeNode *parent;
    RBTreeNode *left;
    RBTreeNode *right;
    Color color;

    // Constructors to initialize the node with a value
    RBTreeNode();
    RBTreeNode(T value);
    RBTreeNode(const RBTreeNode<T> &node);
    ~RBTreeNode();

    // Function prototypes
    RBTreeNode<T>& operator=(const RBTreeNode<T> &node);
    RBTreeNode<T>* treeMin();
    RBTreeNode<T>* treeMax();
    void printPreOrderTraversal() const;
    void printInOrderTraversal() const;
    void printPostOrderTraversal() const;
};

#include "RBTreeNode.cpp"

#endif
