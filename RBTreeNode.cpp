//=========================================================
// RBTreeNode.cpp
// Son Nguyen, James Bui
// Nov, 2024
// This is the implementation file for the RBTreeNode class with functions: constructors, destructor, operator =,
// treeMin, treeMax, printPreOrderTraversal, printInOrderTraversal, printPostOrderTraversal
//=========================================================

#include "RBTreeNode.hpp"
#include <iostream>

using namespace std;


//=========================================================
// Default constructor for the RBTreeNode class.
// Initializes an empty node with default values and null pointers.
// Parameters:
//  None
// Returns:
//  None
//=========================================================
template<class T>
RBTreeNode<T>::RBTreeNode() {
    val = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = BLACK;
}


//=========================================================
// Constructor for the RBTreeNode class with an initial value.
// Initializes a node with the specified value and null pointers.
// Parameters:
//  value: The value to be assigned to the node
// Returns:
//  None
//=========================================================
template<class T>
RBTreeNode<T>::RBTreeNode(T value) {
    val = value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}


//=========================================================
// Copy constructor for the RBTreeNode class.
// Performs a deep copy of the given node, including its subtrees.
// Parameters:
//  node: Reference to the node to be copied
// Returns:
//  None
//=========================================================
template<class T>
RBTreeNode<T>::RBTreeNode(const RBTreeNode<T> &node) {
    //copy the value of the node
    val = node.val;

    //copy the left subtree
    if (node.left != nullptr) {
        left = new RBTreeNode<T>(*node.left);
        left->parent = this;
    }
    else {
        left = nullptr;
    }

    //copy the right subtree
    if (node.right != nullptr) {
        right = new RBTreeNode<T>(*node.right);
        right->parent = this;
    }
    else {
        right = nullptr;
    }

    color = node.color;
}


//=========================================================
// Destructor for the RBTreeNode class.
// Recursively deletes left and right subtrees to free memory.
// Parameters:
//  None
// Returns:
//  None
//=========================================================
template<class T>
RBTreeNode<T>::~RBTreeNode() {
    if (left) {
        delete left;
    }
    if (right) {
        delete right;
    }
}


//=========================================================
// Assignment operator for the RBTreeNode class.
// Performs a deep copy assignment of a given node.
// Parameters:
//  node: Reference to the node to be assigned
// Returns:
//  Reference to the current node after assignment
//=========================================================
template<class T>
RBTreeNode<T>& RBTreeNode<T>::operator=(const RBTreeNode<T> &node) {

    // check for self assignment
    if (this == &node) {
        return *this;
    }

    // delete the left and right subtree
    delete left;
    delete right;

    // update the value of val
    val = node.val;

    // deepcopy the left and right subtree
    if (node.left != nullptr)  {
        left = new RBTreeNode<T>(*node.left);
        left->parent = this;
    }
    else {
        left = nullptr;
    }
    if (node.right != nullptr) {
        right = new RBTreeNode<T>(*node.right);
        right->parent = this;
    }
    else {
        right = nullptr;
    }
    color = node.color;
    return *this;
}


//=========================================================
// treeMin
// Finds the minimum value node starting from the current node.
// Recursively traverses the left subtree to find the minimum.
// Parameters:
//  None
// Returns:
//  Pointer to the node with the minimum value
//=========================================================
template<class T>
RBTreeNode<T>* RBTreeNode<T>::treeMin() {
    if (this->left != nullptr) {
        return this->left->treeMin();
    }
    else {
        return this;
    }
}


//=========================================================
// treeMax
// Finds the maximum value node starting from the current node.
// Recursively traverses the right subtree to find the maximum.
// Parameters:
//  None
// Returns:
//  Pointer to the node with the maximum value
//=========================================================
template<class T>
RBTreeNode<T>* RBTreeNode<T>::treeMax() {
    if (this->right != nullptr) {
        return this->right->treeMax();
    }
    else {
        return this;
    }
}


//=========================================================
// printPreOrderTraversal
// Prints the tree in pre-order traversal starting from the current node.
// Visits the current node, then the left subtree, and then the right subtree.
// Parameters:
//  None
// Returns:
//  None
//=========================================================
template<class T>
void RBTreeNode<T>::printPreOrderTraversal() const {
    cout << this->val << " ";
    if (this->left != nullptr)  {
    this->left->printPreOrderTraversal();
    }
    if (this->right != nullptr) {
    this->right->printPreOrderTraversal();
    }
}


//=========================================================
// printInOrderTraversal
// Prints the tree in in-order traversal starting from the current node.
// Visits the left subtree, then the current node, and then the right subtree.
// Parameters:
//  None
// Returns:
//  None
//=========================================================
template<class T>
void RBTreeNode<T>::printInOrderTraversal() const {
    if (this->left != nullptr)  {
    this->left->printInOrderTraversal();
    }
    cout << this->val << " ";
    if (this->right != nullptr) {
    this->right->printInOrderTraversal();
    }
}


//=========================================================
// printPostOrderTraversal
// Prints the tree in post-order traversal starting from the current node.
// Visits the left subtree, then the right subtree, and then the current node.
// Parameters:
//  None
// Returns:
//  None
//=========================================================
template<class T>
void RBTreeNode<T>::printPostOrderTraversal() const {
    if (this->left != nullptr)  {
    this->left->printPostOrderTraversal();
    }
    if (this->right != nullptr) {
    this->right->printPostOrderTraversal();
    }
    cout << this->val << " ";
}
