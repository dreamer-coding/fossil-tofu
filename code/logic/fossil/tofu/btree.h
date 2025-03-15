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
#ifndef FOSSIL_TOFU_BTREE_H
#define FOSSIL_TOFU_BTREE_H

#include "tofu.h"

#ifdef __cplusplus
extern "C"
{
#endif

// *****************************************************************************
// Type definitions
// *****************************************************************************

typedef struct fossil_btree_node_t {
    fossil_tofu_t data;
    struct fossil_btree_node_t* left;
    struct fossil_btree_node_t* right;
    int32_t height;
} fossil_btree_node_t;

typedef struct fossil_btree_t {
    fossil_btree_node_t* root;
    char* type;
} fossil_btree_t;

// *****************************************************************************
// Function prototypes
// *****************************************************************************

/**
 * Create a new binary tree with the specified data type.
 *
 * @param type The type of data the tree will store.
 * @return     The created tree.
 * @note       O(1) - Constant time complexity.
 */
fossil_btree_t* fossil_btree_create_container(char* type);

/**
 * Create a new binary tree with default values.
 * 
 * @return The created tree.
 * @note   O(1) - Constant time complexity.
 */
fossil_btree_t* fossil_btree_create_default(void);

/**
 * Create a new binary tree by copying an existing tree.
 * 
 * @param other The tree to copy.
 * @return      The created tree.
 * @note        O(n) - Linear time complexity.
 */
fossil_btree_t* fossil_btree_create_copy(const fossil_btree_t* other);

/**
 * Create a new binary tree by moving an existing tree.
 * 
 * @param other The tree to move.
 * @return      The created tree.
 * @note        O(1) - Constant time complexity.
 */
fossil_btree_t* fossil_btree_create_move(fossil_btree_t* other);

/**
 * Destroy a binary tree and free allocated memory.
 *
 * @param tree The tree to destroy.
 * @note       O(n) - Linear time complexity.
 */
void fossil_btree_destroy(fossil_btree_t* tree);

// *****************************************************************************
// Utility functions
// *****************************************************************************

/**
 * Insert data into the binary tree (AVL insertion).
 *
 * @param tree The tree to insert data into.
 * @param data The data to insert.
 * @return     The error code indicating success or failure.
 * @note       O(log n) - Logarithmic time complexity.
 */
int32_t fossil_btree_insert(fossil_btree_t* tree, fossil_tofu_t data);

/**
 * Remove data from the binary tree (AVL deletion).
 *
 * @param tree The tree to remove data from.
 * @param data The data to remove.
 * @return     The error code indicating success or failure.
 * @note       O(log n) - Logarithmic time complexity.
 */
int32_t fossil_btree_erase(fossil_btree_t* tree, fossil_tofu_t data);

/**
 * Get the size (number of nodes) of the binary tree.
 *
 * @param tree The tree for which to get the size.
 * @return     The size of the tree.
 * @note       O(n) - Linear time complexity.
 */
size_t fossil_btree_size(const fossil_btree_t* tree);

/**
 * Check if the tree is not empty.
 *
 * @param tree The tree to check.
 * @return     True if the tree is not empty, false otherwise.
 * @note       O(1) - Constant time complexity.
 */
bool fossil_btree_not_empty(const fossil_btree_t* tree);

/**
 * Check if the tree is empty.
 *
 * @param tree The tree to check.
 * @return     True if the tree is empty, false otherwise.
 * @note       O(1) - Constant time complexity.
 */
bool fossil_btree_is_empty(const fossil_btree_t* tree);

/**
 * Check if the tree is not a null pointer.
 *
 * @param tree The tree to check.
 * @return     True if the tree is not a null pointer, false otherwise.
 * @note       O(1) - Constant time complexity.
 */
bool fossil_btree_not_cnullptr(const fossil_btree_t* tree);

/**
 * Check if the tree is a null pointer.
 *
 * @param tree The tree to check.
 * @return     True if the tree is a null pointer, false otherwise.
 * @note       O(1) - Constant time complexity.
 */
bool fossil_btree_is_cnullptr(const fossil_btree_t* tree);

// *****************************************************************************
// Getter and setter functions
// *****************************************************************************

/**
 * Perform an in-order traversal of the binary tree.
 *
 * @param tree   The tree to traverse.
 * @param action The function to apply to each node.
 * @note        O(n) - Linear time complexity.
 */
void fossil_btree_traverse_in_order(const fossil_btree_t* tree, void (*action)(fossil_tofu_t));

/**
 * Perform a pre-order traversal of the binary tree.
 *
 * @param tree   The tree to traverse.
 * @param action The function to apply to each node.
 * @note        O(n) - Linear time complexity.
 */
void fossil_btree_traverse_pre_order(const fossil_btree_t* tree, void (*action)(fossil_tofu_t));

/**
 * Perform a post-order traversal of the binary tree.
 *
 * @param tree   The tree to traverse.
 * @param action The function to apply to each node.
 * @note        O(n) - Linear time complexity.
 */
void fossil_btree_traverse_post_order(const fossil_btree_t* tree, void (*action)(fossil_tofu_t));

/**
 * Get the smallest element in the binary tree.
 *
 * @param tree The tree from which to get the smallest element.
 * @return     The smallest element in the tree.
 * @note       O(log n) - Logarithmic time complexity.
 */
fossil_tofu_t fossil_btree_get_min(const fossil_btree_t* tree);

/**
 * Get the largest element in the binary tree.
 *
 * @param tree The tree from which to get the largest element.
 * @return     The largest element in the tree.
 * @note       O(log n) - Logarithmic time complexity.
 */
fossil_tofu_t fossil_btree_get_max(const fossil_btree_t* tree);

/**
 * Find an element in the binary tree.
 *
 * @param tree The tree to search.
 * @param data The data to find.
 * @return     The found element or NULL if not found.
 * @note       O(log n) - Logarithmic time complexity.
 */
fossil_tofu_t* fossil_btree_find(const fossil_btree_t* tree, fossil_tofu_t data);

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_TOFU_FRAMEWORK_H */