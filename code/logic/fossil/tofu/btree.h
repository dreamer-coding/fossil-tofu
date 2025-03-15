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

#include <iostream>

namespace fossil {
namespace tofu {

/**
 * @class BTree
 * @brief A C++ wrapper for the Fossil AVL binary tree implementation.
 *
 * This class provides a modern C++ interface to the `fossil_btree_` API,
 * supporting object-oriented usage, resource management, and convenient
 * operator overloads.
 */
class BTree {
private:
    fossil_btree_t* tree; ///< Pointer to the underlying AVL tree.

public:
    /**
     * @brief Default constructor. Creates an empty AVL tree.
     */
    BTree() : tree(fossil_btree_create_default()) {}

    /**
     * @brief Parameterized constructor. Creates an AVL tree with a specific data type.
     */
    explicit BTree(const std::string& type) 
        : tree(fossil_btree_create_container(const_cast<char*>(type.c_str()))) {}

    /**
     * @brief Copy constructor.
     */
    BTree(const BTree& other) : tree(fossil_btree_create_copy(other.tree)) {}

    /**
     * @brief Move constructor.
     */
    BTree(BTree&& other) noexcept : tree(other.tree) {
        other.tree = nullptr;
    }

    /**
     * @brief Destructor. Frees tree memory.
     */
    ~BTree() {
        fossil_btree_destroy(tree);
    }

    /**
     * @brief Copy assignment operator.
     */
    BTree& operator=(const BTree& other) {
        if (this != &other) {
            fossil_btree_destroy(tree);
            tree = fossil_btree_create_copy(other.tree);
        }
        return *this;
    }

    /**
     * @brief Move assignment operator.
     */
    BTree& operator=(BTree&& other) noexcept {
        if (this != &other) {
            fossil_btree_destroy(tree);
            tree = other.tree;
            other.tree = nullptr;
        }
        return *this;
    }

    /**
     * @brief Inserts an element into the tree.
     */
    int32_t insert(const fossil_tofu_t& data) {
        return fossil_btree_insert(tree, data);
    }

    /**
     * @brief Removes an element from the tree.
     */
    int32_t erase(const fossil_tofu_t& data) {
        return fossil_btree_erase(tree, data);
    }

    /**
     * @brief Gets the number of elements in the tree.
     */
    size_t get_size() const {
        return fossil_btree_size(tree);
    }

    // *************************************************************************
    // * Operator Overloads
    // *************************************************************************

    /** @brief Overload `+=` for inserting elements */
    BTree& operator+=(const fossil_tofu_t& data) {
        insert(data);
        return *this;
    }

    /** @brief Overload `-=` for removing elements */
    BTree& operator-=(const fossil_tofu_t& data) {
        erase(data);
        return *this;
    }

    /** @brief Overload `==` for equality comparison */
    bool operator==(const BTree& other) const {
        return fossil_btree_equals(tree, other.tree);
    }

    /** @brief Overload `!=` for inequality comparison */
    bool operator!=(const BTree& other) const {
        return !(*this == other);
    }

    /** @brief Overload `<` (compares sizes of trees) */
    bool operator<(const BTree& other) const {
        return get_size() < other.get_size();
    }

    /** @brief Overload `>` (compares sizes of trees) */
    bool operator>(const BTree& other) const {
        return get_size() > other.get_size();
    }

    /** @brief Overload `<=` */
    bool operator<=(const BTree& other) const {
        return get_size() <= other.get_size();
    }

    /** @brief Overload `>=` */
    bool operator>=(const BTree& other) const {
        return get_size() >= other.get_size();
    }

    // *************************************************************************
    // * Additional Utility Methods
    // *************************************************************************

    /**
     * @brief Checks if the tree is empty.
     */
    bool is_empty() const {
        return fossil_btree_is_empty(tree);
    }

    /**
     * @brief Finds an element in the tree.
     */
    fossil_tofu_t* find(const fossil_tofu_t& data) const {
        return fossil_btree_find(tree, data);
    }

    /**
     * @brief Traverses the tree in-order and applies a function.
     */
    void traverse_in_order(void (*action)(fossil_tofu_t)) const {
        fossil_btree_traverse_in_order(tree, action);
    }

    /**
     * @brief Overloads `<<` operator to print tree size.
     */
    friend std::ostream& operator<<(std::ostream& os, const BTree& tree) {
        os << "BTree(Size: " << tree.get_size() << ")";
        return os;
    }

    /**
     * @brief Retrieves the raw pointer to the underlying tree structure.
     */
    fossil_btree_t* get_raw_tree() const {
        return tree;
    }
};

} // namespace tofu
} // namespace fossil

#endif

#endif /* FOSSIL_TOFU_FRAMEWORK_H */