//=========================================================
// RBTree.cpp
// Son Nguyen, James Bui
// Nov, 2024
// This is the implementation file for the RBTree class.
//=========================================================

#include "RBTreeNode.hpp"
#include "RBTree.hpp"
// #include "customexceptions.hpp"
#include <iostream>

using namespace std;

//=========================================================
// Constructor for the RBTree class.
// Initializes an empty binary search tree.
// Parameters:
//  None
// Returns:
//  None
//=========================================================
template <class T>
RBTree<T>::RBTree()
{
    root = nullptr;
}

//=========================================================
// Copy constructor for the RBTree class.
// Creates a deep copy of an existing tree.
// Parameters:
//  tree: Reference to the RBTree object to be copied
// Returns:
//  None
//=========================================================
template <class T>
RBTree<T>::RBTree(const RBTree<T> &tree)
{
    if (tree.isEmpty())
    {
        root = nullptr;
    }
    else
    {
        root = new RBTreeNode<T>(*tree.root);
    }
}

//=========================================================
// ~RBTree
// Destructor for the RBTree class.
// Frees the memory associated with the tree nodes.
// Parameters:
//  None
// Returns:
//  None
//=========================================================
template <class T>
RBTree<T>::~RBTree()
{
    if (size() != 0)
    {
        delete root;
    }
}

//=========================================================
// operator=
// Assignment Operator for the RBTree class.
// Parameters:
// - const RBTree<T> &tree: Red-Black tree to be copied
// Returns:
//  A tree copied from the parameter
//=========================================================
template <class T>
RBTree<T> &RBTree<T>::operator=(const RBTree<T> &tree)
{
    // Check for self assignment
    if (this == &tree)
    {
        return *this;
    }

    // Delete the current tree
    delete root;
    root = nullptr;

    // Check if the tree is empty
    if (tree.root == nullptr)
    {
        return *this;
    }

    // Make a deep copy of the tree
    root = new RBTreeNode<T>(*tree.root);

    return *this;
}

//=========================================================
// transplant
// Replaces one subtree as a child of its parent with another subtree.
// Parameters:
//  oldNode: Pointer to the node being replaced
//  newNode: Pointer to the node that replaces oldNode
// Returns:
//  None
//=========================================================
template <class T>
void RBTree<T>::transplant(RBTreeNode<T> *oldNode, RBTreeNode<T> *newNode)
{
    if (oldNode->parent == nullptr)
    {
        root = newNode;
    }
    else if (oldNode == oldNode->parent->left)
    {
        oldNode->parent->left = newNode;
    }
    else
    {
        oldNode->parent->right = newNode;
    }
    if (newNode != nullptr)
    {
        newNode->parent = oldNode->parent;
    }
    oldNode->parent = nullptr;
}

//=========================================================
// isEmpty
// Checks if the RBTree is empty.
// Parameters:
//  None
// Returns:
//  True if the tree is empty, false otherwise
//=========================================================
template <class T>
bool RBTree<T>::isEmpty() const
{
    return size() == 0;
}

//=========================================================
// size
// Returns the number of nodes in the RBTree.
// Parameters:
//  None
// Returns:
//  The number of nodes in the tree
//=========================================================
template <class T>
long RBTree<T>::size() const
{
    return getSize(root);
}

//=========================================================
// insert
// Inserts a new node with the specified value into the RBTree.
// Parameters:
//  value: The value to be inserted into the tree
// Returns:
//  A pointer to the inserted node
//=========================================================
template <class T>
RBTreeNode<T> *RBTree<T>::insert(T value)
{
    RBTreeNode<T> *inserted = new RBTreeNode<T>(value);
    RBTreeNode<T> *current = root;
    RBTreeNode<T> *parent = nullptr;

    while (current != nullptr)
    {
        parent = current;
        if (inserted->val <= current->val)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    inserted->parent = parent;
    if (parent == nullptr)
    {
        root = inserted;
    }
    else if (inserted->val <= parent->val)
    {
        parent->left = inserted;
    }
    else
    {
        parent->right = inserted;
    }
    inserted->left = nullptr;
    inserted->right = nullptr;
    inserted->color = RED;
    insert_fixup(inserted);
    return inserted;
}

//=========================================================
// remove
// Removes a node with the specified value from the RBTree.
// Parameters:
//  value: The value of the node to be removed
// Returns:
//  None, but throws an exception if the value is not found
//=========================================================
template <class T>
void RBTree<T>::remove(T value)
{
    RBTreeNode<T> *deleted = search(value);
    if (deleted == nullptr)
    {
        throw value_not_in_tree("value not found");
    }

    RBTreeNode<T> *y = deleted;
    RBTreeNode<T> *x;
    Color original_color = y->color;
    if (deleted->left == nullptr)
    {
        x = deleted->right;
        transplant(deleted, deleted->right);
    }
    else if (deleted->right == nullptr)
    {
        x = deleted->left;
        transplant(deleted, deleted->left);
    }
    else
    {
        y = deleted->right->treeMin();
        original_color = y->color;
        x = y->right;
        if (y != deleted->right)
        {
            transplant(y, y->right);
            y->right = deleted->right;
            y->right->parent = y;
        }
        else if (x != nullptr)
            x->parent = y;
        transplant(deleted, y);
        y->left = deleted->left;
        y->left->parent = y;
        y->color = deleted->color;
    }
    if (original_color == BLACK && x != nullptr)
    {
        delete_fixup(x);
    }
    // delete node
    deleted->left = deleted->right = deleted->parent = nullptr;
    delete deleted;
}

//=========================================================
// search
// Searches for a node with the specified value in the RBTree.
// Parameters:
//  value: The value to search for
// Returns:
//  A pointer to the node if found, otherwise nullptr
//=========================================================
template <class T>
RBTreeNode<T> *RBTree<T>::search(T value) const
{
    RBTreeNode<T> *current = root;
    while (current != nullptr)
    {
        if (current->val == value)
        {
            return current;
        }
        if (current->val < value)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    return nullptr;
}

//=========================================================
// treeMin
// Finds the minimum value node in the RBTree.
// Parameters:
//  None
// Returns:
//  A pointer to the node with the minimum value
// Throws:
//  An exception if the tree is empty
//=========================================================
template <class T>
RBTreeNode<T> *RBTree<T>::treeMin() const
{
    if (isEmpty())
    {
        throw empty_tree_exception("Tree is empty!");
    }
    else
    {
        return root->treeMin();
    }
}

//=========================================================
// treeMax
// Finds the maximum value node in the RBTree.
// Parameters:
//  None
// Returns:
//  A pointer to the node with the maximum value
// Throws:
//  An exception if the tree is empty
//=========================================================
template <class T>
RBTreeNode<T> *RBTree<T>::treeMax() const
{
    if (isEmpty())
    {
        throw empty_tree_exception("Tree is empty!");
    }
    else
    {
        return root->treeMax();
    }
}

//=========================================================
// printPreOrderTraversal
// Prints the RBTree in pre-order traversal.
// Parameters:
//  None
// Returns:
//  None
//=========================================================
template <class T>
void RBTree<T>::printPreOrderTraversal() const
{
    if (isEmpty())
    {
        return;
    }
    else
    {
        root->printPreOrderTraversal();
    }
}

//=========================================================
// printInOrderTraversal
// Prints the RBTree in in-order traversal.
// Parameters:
//  None
// Returns:
//  None
//=========================================================
template <class T>
void RBTree<T>::printInOrderTraversal() const
{
    if (isEmpty())
    {
        return;
    }
    else
    {
        root->printInOrderTraversal();
    }
}

//=========================================================
// printPostOrderTraversal
// Prints the RBTree in post-order traversal.
// Parameters:
//  None
// Returns:
//  None
//=========================================================
template <class T>
void RBTree<T>::printPostOrderTraversal() const
{
    if (isEmpty())
    {
        return;
    }
    else
    {
        root->printPostOrderTraversal();
    }
}

//=========================================================
// insert_fixup
// Fix the node which violates the property of a Red-Black tree after insertion
// Parameters:
//  RBTreeNode<T> *node: the node where the "double black" problem might exist after insertion. 
// Returns:
//  None
//=========================================================
template <class T>
void RBTree<T>::insert_fixup(RBTreeNode<T> *z)
{
    while (z->parent && z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            RBTreeNode<T> *uncle = z->parent->parent->right;
            if (uncle && uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    left_rotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(z->parent->parent);
            }
        }
        else
        {
            RBTreeNode<T> *uncle = z->parent->parent->left;
            if (uncle && uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    right_rotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

//=========================================================
// delete_fixup
// Fix the node which violates the property of a Red-Black tree after deletion
// Parameters:
//  RBTreeNode<T> *node: the node where the "double black" problem might exist after deletion. 
// Returns:
//  None
//=========================================================
template <class T>
void RBTree<T>::delete_fixup(RBTreeNode<T> *node)
{
    while (node != root && node->color == BLACK)
    {
        if (node == node->parent->left)
        {
            RBTreeNode<T> *sibling = node->parent->right;
            if (sibling && sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                left_rotate(node->parent);
                sibling = node->parent->right;
            }

            if (sibling && (sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling->right == nullptr || sibling->right->color == BLACK))
            {
                sibling->color = RED;
                node = node->parent;
            }
            else
            {
                if (sibling && (sibling->right == nullptr || sibling->right->color == BLACK))
                {
                    if (sibling->left)
                        sibling->left->color = BLACK;
                    sibling->color = RED;
                    right_rotate(sibling);
                    sibling = node->parent->right;
                }
                if (sibling)
                    sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling && sibling->right)
                    sibling->right->color = BLACK;
                left_rotate(node->parent);
                node = root;
            }
        }
        else
        {
            RBTreeNode<T> *sibling = node->parent->left;
            if (sibling && sibling->color == RED)
            {
                sibling->color = BLACK;
                node->parent->color = RED;
                right_rotate(node->parent);
                sibling = node->parent->left;
            }
            if (sibling && (sibling->right == nullptr || sibling->right->color == BLACK) &&
                (sibling->left == nullptr || sibling->left->color == BLACK))
            {
                sibling->color = RED;
                node = node->parent;
            }
            else
            {
                if (sibling && (sibling->left == nullptr || sibling->left->color == BLACK))
                {
                    if (sibling->right)
                        sibling->right->color = BLACK;
                    sibling->color = RED;
                    left_rotate(sibling);
                    sibling = node->parent->left;
                }
                if (sibling)
                    sibling->color = node->parent->color;
                node->parent->color = BLACK;
                if (sibling && sibling->left)
                    sibling->left->color = BLACK;
                right_rotate(node->parent);
                node = root;
            }
        }
    }
    if (node)
    {
        node->color = BLACK;
    }
}

//=========================================================
// left_rotate
// Performs the left-rotate operation on the tree
// Parameters:
//  RBTreeNode<T> *node: the node to be rotated around
// Returns:
//  None
//=========================================================
template <class T>
void RBTree<T>::left_rotate(RBTreeNode<T> *node)
{
    RBTreeNode<T> *right = node->right;
    if (right == nullptr)
        return;
    node->right = right->left;
    if (right->left != nullptr)
    {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == nullptr)
    {
        root = right;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = right;
    }
    else
    {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

//=========================================================
// right_rotate
// Performs the right-rotate operation on the tree
// Parameters:
//  RBTreeNode<T> *node: the node to be rotated around
// Returns:
//  None
//=========================================================
template <class T>
void RBTree<T>::right_rotate(RBTreeNode<T> *node)
{
    RBTreeNode<T> *left = node->left;
    if (left == nullptr)
        return;
    node->left = left->right;
    if (left->right != nullptr)
    {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == nullptr)
    {
        root = left;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = left;
    }
    else
    {
        node->parent->right = left;
    }
    left->right = node;
    node->parent = left;
}

//=========================================================
// getSize
// Get the size of the subtree rooted at this node
// Parameters:
//  pointer to a node
// Returns:
//  The number of nodes in the tree
//=========================================================
template <class T>
long RBTree<T>::getSize(RBTreeNode<T> *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + getSize(node->left) + getSize(node->right);
}

//=========================================================
// is_balanced
// Check if the Red-Black Tree is balanced
// Purpose:
//  - Verifies that the tree meets the Red-Black Tree properties:
//      1) The root is black.
//      2) There are no consecutive red nodes (no red node has a red child).
//      3) All paths from the root to leaves have the same black height.
// Parameters:
//  None
// Returns:
//  true if the tree is balanced according to Red-Black Tree properties, false otherwise
//=========================================================
template <class T>
bool RBTree<T>::is_balanced()
{
    if (root == nullptr)
        return true;

    // Check if the root is black
    if (root->color != BLACK)
    {
        std::cerr << "Root is not black." << std::endl;
        return false;
    }

    // Check all paths for equal black height and no consecutive red nodes
    int blackHeight = -1;
    return is_balanced_helper(root, 0, blackHeight);
}


//=========================================================
// is_balanced_helper
// Recursively check if the subtree rooted at a given node is balanced
// Purpose:
//  - Traverses the tree from a given node to verify that it satisfies
//    Red-Black Tree properties:
//      1) Black height is consistent across paths from the root to each leaf.
//      2) No consecutive red nodes exist.
// Parameters:
//  node - pointer to the current node in the tree
//  currentBlackHeight - the count of black nodes in the current path
//  expectedBlackHeight - reference to an integer tracking the expected black height across all paths
// Returns:
//  true if the subtree rooted at node is balanced, false otherwise
//=========================================================
template <class T>
bool RBTree<T>:: is_balanced_helper(RBTreeNode<T> *node, int currentBlackHeight, int &expectedBlackHeight)
{
    if (node == nullptr)
    {
        // At a leaf (nil node), set the black height if it's the first leaf, else verify it matches
        if (expectedBlackHeight == -1)
        {
            expectedBlackHeight = currentBlackHeight;
        }
        return currentBlackHeight == expectedBlackHeight;
    }

    // Check for consecutive red nodes
    if (node->color == RED)
    { // if the current node is RED
        if ((node->left && node->left->color == RED) || (node->right && node->right->color == RED))
        {
            std::cerr << "Consecutive red nodes found at node with data " << node->val << std::endl;
            return false;
        }
    }

    // Increment black height count for black nodes
    if (node->color == BLACK)
        currentBlackHeight++;

    // Recursively check the left and right subtrees
    return is_balanced_helper(node->left, currentBlackHeight, expectedBlackHeight) &&
           is_balanced_helper(node->right, currentBlackHeight, expectedBlackHeight);
}