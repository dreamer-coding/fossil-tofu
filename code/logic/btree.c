/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/tofu/btree.h"
#include <stddef.h>  // For size_t, NULL
#include <stdint.h>  // For int32_t and other integer types
#include <stdlib.h>  // For malloc and free
#include <math.h>

// *****************************************************************************
// Utility functions
// *****************************************************************************

// Function to create a new binary tree with the specified data type.
fossil_btree_t* fossil_btree_create_container(char* type) {
    fossil_btree_t* tree = (fossil_btree_t*)malloc(sizeof(fossil_btree_t));
    if (tree) {
        tree->root = NULL;
        tree->type = fossil_tofu_strdup(type);  // Store the type string
    }
    return tree;
}

// Function to create a new binary tree with default values.
fossil_btree_t* fossil_btree_create_default(void) {
    return fossil_btree_create_container("default");
}

// Recursive helper function to copy nodes
static fossil_btree_node_t* fossil_btree_copy_nodes(const fossil_btree_node_t* node) {
    if (node == NULL) return NULL;

    // Allocate a new node
    fossil_btree_node_t* new_node = (fossil_btree_node_t*)malloc(sizeof(fossil_btree_node_t));
    if (new_node == NULL) return NULL;  // Memory allocation failure

    // Copy data and height
    new_node->data = fossil_tofu_copy(node->data); // Assuming fossil_tofu_copy duplicates tofu data
    new_node->height = node->height;

    // Recursively copy left and right subtrees
    new_node->left = fossil_btree_copy_nodes(node->left);
    new_node->right = fossil_btree_copy_nodes(node->right);

    return new_node;
}

// Function to create a new binary tree by copying an existing tree
fossil_btree_t* fossil_btree_create_copy(const fossil_btree_t* other) {
    if (other == NULL) return NULL;

    fossil_btree_t* tree = (fossil_btree_t*)malloc(sizeof(fossil_btree_t));
    if (tree == NULL) return NULL;  // Memory allocation failure

    // Copy metadata
    tree->type = fossil_tofu_strdup(other->type); // Assuming this duplicates the type string
    tree->root = fossil_btree_copy_nodes(other->root); // Recursively copy the tree

    return tree;
}

// Function to create a new binary tree by moving an existing tree.
fossil_btree_t* fossil_btree_create_move(fossil_btree_t* other) {
    fossil_btree_t* tree = (fossil_btree_t*)malloc(sizeof(fossil_btree_t));
    if (tree) {
        tree->type = other->type;
        tree->root = other->root;
        other->type = NULL;
        other->root = NULL;
    }
    return tree;
}

// Function to destroy a binary tree and free allocated memory.
void fossil_btree_destroy(fossil_btree_t* tree) {
    if (tree) {
        // Free the tree's root and all its nodes
        // Recursive function for node destruction will be needed here
        free(tree->type); // Free the type string
        free(tree);        // Finally free the tree structure
    }
}

// *****************************************************************************
// Tree functions (Insert, Erase, Size, etc.)
// *****************************************************************************

// Utility function to get the height of a node
static int fossil_btree_height(fossil_btree_node_t* node) {
    return (node == NULL) ? 0 : node->height;
}

// Utility function to calculate balance factor of a node
static int fossil_btree_balance_factor(fossil_btree_node_t* node) {
    if (node == NULL) return 0;
    return fossil_btree_height(node->left) - fossil_btree_height(node->right);
}

// Utility function to perform right rotation (LL rotation)
static fossil_btree_node_t* fossil_btree_rotate_right(fossil_btree_node_t* y) {
    fossil_btree_node_t* x = y->left;
    fossil_btree_node_t* T2 = x->right;

    // Rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + fmax(fossil_btree_height(y->left), fossil_btree_height(y->right));
    x->height = 1 + fmax(fossil_btree_height(x->left), fossil_btree_height(x->right));

    return x;  // New root
}

// Utility function to perform left rotation (RR rotation)
static fossil_btree_node_t* fossil_btree_rotate_left(fossil_btree_node_t* x) {
    fossil_btree_node_t* y = x->right;
    fossil_btree_node_t* T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + fmax(fossil_btree_height(x->left), fossil_btree_height(x->right));
    y->height = 1 + fmax(fossil_btree_height(y->left), fossil_btree_height(y->right));

    return y;  // New root
}

// Recursive function to insert a node in the AVL tree and balance it
static fossil_btree_node_t* fossil_btree_insert_node(fossil_btree_node_t* node, fossil_tofu_t data) {
    // Standard BST insertion
    if (node == NULL) {
        fossil_btree_node_t* new_node = malloc(sizeof(fossil_btree_node_t));
        if (new_node == NULL) return NULL;  // Memory allocation failure
        new_node->data = data;
        new_node->left = new_node->right = NULL;
        new_node->height = 1;  // New node has height 1
        return new_node;
    }

    if (data < node->data)
        node->left = fossil_btree_insert_node(node->left, data);
    else if (data > node->data)
        node->right = fossil_btree_insert_node(node->right, data);
    else
        return node;  // Duplicate keys are not allowed

    // Update height
    node->height = 1 + fmax(fossil_btree_height(node->left), fossil_btree_height(node->right));

    // Get balance factor
    int balance = fossil_btree_balance_factor(node);

    // Balance the node
    if (balance > 1 && data < node->left->data)  // Left-Left case
        return fossil_btree_rotate_right(node);
    if (balance < -1 && data > node->right->data)  // Right-Right case
        return fossil_btree_rotate_left(node);
    if (balance > 1 && data > node->left->data) {  // Left-Right case
        node->left = fossil_btree_rotate_left(node->left);
        return fossil_btree_rotate_right(node);
    }
    if (balance < -1 && data < node->right->data) {  // Right-Left case
        node->right = fossil_btree_rotate_right(node->right);
        return fossil_btree_rotate_left(node);
    }

    return node;  // No rotation needed
}

// Public function to insert data into AVL tree
int32_t fossil_btree_insert(fossil_btree_t* tree, fossil_tofu_t data) {
    if (tree == NULL) return -1;
    tree->root = fossil_btree_insert_node(tree->root, data);
    return 0;
}

// Utility function to find the node with the minimum value
static fossil_btree_node_t* fossil_btree_min_node(fossil_btree_node_t* node) {
    fossil_btree_node_t* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Recursive function to delete a node from the AVL tree
static fossil_btree_node_t* fossil_btree_delete_node(fossil_btree_node_t* root, fossil_tofu_t data) {
    if (root == NULL) return root;

    // Standard BST deletion
    if (data < root->data)
        root->left = fossil_btree_delete_node(root->left, data);
    else if (data > root->data)
        root->right = fossil_btree_delete_node(root->right, data);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            fossil_btree_node_t* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                free(root);
                return NULL;
            } else {
                *root = *temp;
                free(temp);
            }
        } else {
            fossil_btree_node_t* temp = fossil_btree_min_node(root->right);
            root->data = temp->data;
            root->right = fossil_btree_delete_node(root->right, temp->data);
        }
    }

    if (root == NULL) return root;

    // Update height
    root->height = 1 + fmax(fossil_btree_height(root->left), fossil_btree_height(root->right));

    // Balance the node
    int balance = fossil_btree_balance_factor(root);

    if (balance > 1 && fossil_btree_balance_factor(root->left) >= 0)  // Left-Left case
        return fossil_btree_rotate_right(root);
    if (balance > 1 && fossil_btree_balance_factor(root->left) < 0) {  // Left-Right case
        root->left = fossil_btree_rotate_left(root->left);
        return fossil_btree_rotate_right(root);
    }
    if (balance < -1 && fossil_btree_balance_factor(root->right) <= 0)  // Right-Right case
        return fossil_btree_rotate_left(root);
    if (balance < -1 && fossil_btree_balance_factor(root->right) > 0) {  // Right-Left case
        root->right = fossil_btree_rotate_right(root->right);
        return fossil_btree_rotate_left(root);
    }

    return root;
}

// Public function to remove a node
int32_t fossil_btree_erase(fossil_btree_t* tree, fossil_tofu_t data) {
    if (tree == NULL) return -1;
    tree->root = fossil_btree_delete_node(tree->root, data);
    return 0;
}

// Recursive helper function to count nodes
static size_t fossil_btree_count_nodes(fossil_btree_node_t* node) {
    if (node == NULL) return 0;
    return 1 + fossil_btree_count_nodes(node->left) + fossil_btree_count_nodes(node->right);
}

// Public function to get the size of the tree
size_t fossil_btree_size(const fossil_btree_t* tree) {
    if (tree == NULL) return 0;
    return fossil_btree_count_nodes(tree->root);
}

// Function to check if the tree is not empty.
bool fossil_btree_not_empty(const fossil_btree_t* tree) {
    return tree && tree->root != NULL;
}

// Function to check if the tree is empty.
bool fossil_btree_is_empty(const fossil_btree_t* tree) {
    return tree == NULL || tree->root == NULL;
}

// Function to check if the tree is not a null pointer.
bool fossil_btree_not_cnullptr(const fossil_btree_t* tree) {
    return tree != NULL;
}

// Function to check if the tree is a null pointer.
bool fossil_btree_is_cnullptr(const fossil_btree_t* tree) {
    return tree == NULL;
}

// *****************************************************************************
// Getter and Setter functions (Traversal, Min, Max, etc.)
// *****************************************************************************

// Function to perform an in-order traversal of the binary tree.
void fossil_btree_traverse_in_order(const fossil_btree_t* tree, void (*action)(fossil_tofu_t)) {
    if (tree != NULL && tree->root != NULL) {
        // Traverse the left subtree
        fossil_btree_traverse_in_order(tree->root->left, action);
        
        // Apply the action to the root node
        action(tree->root->data);
        
        // Traverse the right subtree
        fossil_btree_traverse_in_order(tree->root->right, action);
    }
}

// Function to perform a pre-order traversal of the binary tree.
void fossil_btree_traverse_pre_order(const fossil_btree_t* tree, void (*action)(fossil_tofu_t)) {
    if (tree != NULL && tree->root != NULL) {
        // Apply the action to the root node
        action(tree->root->data);
        
        // Traverse the left subtree
        fossil_btree_traverse_pre_order(tree->root->left, action);
        
        // Traverse the right subtree
        fossil_btree_traverse_pre_order(tree->root->right, action);
    }
}

// Function to perform a post-order traversal of the binary tree.
void fossil_btree_traverse_post_order(const fossil_btree_t* tree, void (*action)(fossil_tofu_t)) {
    if (tree != NULL && tree->root != NULL) {
        // Traverse the left subtree
        fossil_btree_traverse_post_order(tree->root->left, action);
        
        // Traverse the right subtree
        fossil_btree_traverse_post_order(tree->root->right, action);
        
        // Apply the action to the root node
        action(tree->root->data);
    }
}

// Function to get the smallest element in the binary tree.
fossil_tofu_t fossil_btree_get_min(const fossil_btree_t* tree) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;  // Return NULL if the tree is empty
    }

    fossil_btree_node_t* current = tree->root;
    while (current->left != NULL) {
        current = current->left;  // Traverse to the leftmost node
    }

    return current->data;  // Return the smallest element
}

// Function to get the largest element in the binary tree.
fossil_tofu_t fossil_btree_get_max(const fossil_btree_t* tree) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;  // Return NULL if the tree is empty
    }

    fossil_btree_node_t* current = tree->root;
    while (current->right != NULL) {
        current = current->right;  // Traverse to the rightmost node
    }

    return current->data;  // Return the largest element
}

// Function to find an element in the binary tree.
fossil_tofu_t* fossil_btree_find(const fossil_btree_t* tree, fossil_tofu_t data) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;  // Return NULL if the tree is empty
    }

    fossil_btree_node_t* current = tree->root;
    while (current != NULL) {
        if (data == current->data) {
            return &(current->data);  // Return the element if found
        } else if (data < current->data) {
            current = current->left;  // Go to the left subtree
        } else {
            current = current->right;  // Go to the right subtree
        }
    }

    return NULL;  // Return NULL if the element is not found
}
