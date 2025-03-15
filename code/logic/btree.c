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
        tree->type = strdup(type);  // Store the type string
    }
    return tree;
}

// Function to create a new binary tree with default values.
fossil_btree_t* fossil_btree_create_default(void) {
    return fossil_btree_create_container("default");
}

// Function to create a new binary tree by copying an existing tree.
fossil_btree_t* fossil_btree_create_copy(const fossil_btree_t* other) {
    fossil_btree_t* tree = (fossil_btree_t*)malloc(sizeof(fossil_btree_t));
    if (tree) {
        tree->type = strdup(other->type);
        tree->root = NULL; // Copy root logic will be handled separately
        // To copy the tree, you need a recursive function that traverses the original tree
        // and inserts each node into the new tree.
    }
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

// Function to perform a right rotation (used in AVL insertion and deletion).
fossil_btree_node_t* fossil_btree_rotate_right(fossil_btree_node_t* y) {
    fossil_btree_node_t* x = y->left;
    fossil_btree_node_t* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(fossil_btree_get_height(y->left), fossil_btree_get_height(y->right)) + 1;
    x->height = max(fossil_btree_get_height(x->left), fossil_btree_get_height(x->right)) + 1;

    return x;  // New root
}

// Function to perform a left rotation (used in AVL insertion and deletion).
fossil_btree_node_t* fossil_btree_rotate_left(fossil_btree_node_t* x) {
    fossil_btree_node_t* y = x->right;
    fossil_btree_node_t* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(fossil_btree_get_height(x->left), fossil_btree_get_height(x->right)) + 1;
    y->height = max(fossil_btree_get_height(y->left), fossil_btree_get_height(y->right)) + 1;

    return y;  // New root
}

// Function to get the height of a node.
int32_t fossil_btree_get_height(fossil_btree_node_t* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Function to get the balance factor of a node.
int32_t fossil_btree_get_balance(fossil_btree_node_t* node) {
    if (node == NULL) {
        return 0;
    }
    return fossil_btree_get_height(node->left) - fossil_btree_get_height(node->right);
}

// Function to insert data into the binary tree (AVL insertion).
int32_t fossil_btree_insert(fossil_btree_t* tree, fossil_tofu_t data) {
    // Helper function for recursive insertion
    fossil_btree_node_t* insert_node(fossil_btree_node_t* node, fossil_tofu_t data) {
        // Perform normal BST insertion
        if (node == NULL) {
            // Allocate memory for new node and initialize it
            fossil_btree_node_t* new_node = malloc(sizeof(fossil_btree_node_t));
            new_node->data = data;
            new_node->left = new_node->right = NULL;
            new_node->height = 1;  // New node is initially at height 1
            return new_node;
        }

        // Insert data recursively
        if (data < node->data) {
            node->left = insert_node(node->left, data);
        } else if (data > node->data) {
            node->right = insert_node(node->right, data);
        } else {
            // Duplicate data is not allowed in this tree
            return node;
        }

        // Update the height of this node
        node->height = max(fossil_btree_get_height(node->left), fossil_btree_get_height(node->right)) + 1;

        // Get the balance factor
        int balance = fossil_btree_get_balance(node);

        // If the node becomes unbalanced, perform rotations

        // Left Left Case
        if (balance > 1 && data < node->left->data) {
            return fossil_btree_rotate_right(node);
        }

        // Right Right Case
        if (balance < -1 && data > node->right->data) {
            return fossil_btree_rotate_left(node);
        }

        // Left Right Case
        if (balance > 1 && data > node->left->data) {
            node->left = fossil_btree_rotate_left(node->left);
            return fossil_btree_rotate_right(node);
        }

        // Right Left Case
        if (balance < -1 && data < node->right->data) {
            node->right = fossil_btree_rotate_right(node->right);
            return fossil_btree_rotate_left(node);
        }

        // Return the (unchanged) node pointer
        return node;
    }

    // Call the recursive insert function
    tree->root = insert_node(tree->root, data);

    return 0;  // Return success
}

// Function to perform AVL deletion.
int32_t fossil_btree_erase(fossil_btree_t* tree, fossil_tofu_t data) {
    // Helper function for recursive deletion
    fossil_btree_node_t* delete_node(fossil_btree_node_t* node, fossil_tofu_t data) {
        if (node == NULL) {
            return node;
        }

        // Perform standard BST delete
        if (data < node->data) {
            node->left = delete_node(node->left, data);
        } else if (data > node->data) {
            node->right = delete_node(node->right, data);
        } else {
            // Node to be deleted found

            // Node has one child or no child
            if (node->left == NULL) {
                fossil_btree_node_t* temp = node->right;
                free(node);
                return temp;
            } else if (node->right == NULL) {
                fossil_btree_node_t* temp = node->left;
                free(node);
                return temp;
            }

            // Node has two children: Get the inorder successor (smallest in the right subtree)
            fossil_btree_node_t* temp = fossil_btree_get_min_node(node->right);

            // Copy the inorder successor's content to this node
            node->data = temp->data;

            // Delete the inorder successor
            node->right = delete_node(node->right, temp->data);
        }

        // If the tree has only one node, return
        if (node == NULL) {
            return node;
        }

        // Update the height of this node
        node->height = max(fossil_btree_get_height(node->left), fossil_btree_get_height(node->right)) + 1;

        // Get the balance factor
        int balance = fossil_btree_get_balance(node);

        // If the node becomes unbalanced, perform rotations

        // Left Left Case
        if (balance > 1 && fossil_btree_get_balance(node->left) >= 0) {
            return fossil_btree_rotate_right(node);
        }

        // Right Right Case
        if (balance < -1 && fossil_btree_get_balance(node->right) <= 0) {
            return fossil_btree_rotate_left(node);
        }

        // Left Right Case
        if (balance > 1 && fossil_btree_get_balance(node->left) < 0) {
            node->left = fossil_btree_rotate_left(node->left);
            return fossil_btree_rotate_right(node);
        }

        // Right Left Case
        if (balance < -1 && fossil_btree_get_balance(node->right) > 0) {
            node->right = fossil_btree_rotate_right(node->right);
            return fossil_btree_rotate_left(node);
        }

        return node;
    }

    // Call the recursive delete function
    tree->root = delete_node(tree->root, data);

    return 0;  // Return success
}

// Function to get the size (number of nodes) of the binary tree.
size_t fossil_btree_size(const fossil_btree_t* tree) {
    size_t size = 0;

    // Helper function for recursive size calculation
    void count_nodes(fossil_btree_node_t* node) {
        if (node != NULL) {
            size++;  // Increment size
            count_nodes(node->left);  // Count left subtree
            count_nodes(node->right); // Count right subtree
        }
    }

    count_nodes(tree->root);

    return size;
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
