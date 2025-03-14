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
#ifndef FOSSIL_TOFU_ARRAYLIST_H
#define FOSSIL_TOFU_ARRAYLIST_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "tofu.h"

#ifdef __cplusplus
extern "C"
{
#endif

// *****************************************************************************
// Type definitions
// *****************************************************************************

// Node structure for the doubly linked list-based array list
typedef struct fossil_arraylist_node_t {
    fossil_tofu_t data;
    struct fossil_arraylist_node_t* prev;
    struct fossil_arraylist_node_t* next;
} fossil_arraylist_node_t;

// Doubly linked list-based array list structure
typedef struct fossil_arraylist_t {
    fossil_arraylist_node_t* head;
    fossil_arraylist_node_t* tail;
    size_t size;
    char* type;
} fossil_arraylist_t;

// *****************************************************************************
// Function prototypes
// *****************************************************************************

/**
 * Create a new array list with the specified data type.
 *
 * @param type The type of data the array list will store.
 * @return     A pointer to the created array list.
 * @note       Time complexity: O(1)
 */
fossil_arraylist_t* fossil_arraylist_create_container(char* type);

/**
 * Create a new array list with default values.
 *
 * @return A pointer to the created array list.
 * @note   Time complexity: O(1)
 */
fossil_arraylist_t* fossil_arraylist_create_default(void);

/**
 * Create a new array list by copying an existing list.
 *
 * @param other The array list to copy.
 * @return      A pointer to the copied array list.
 * @note        Time complexity: O(n)
 */
fossil_arraylist_t* fossil_arraylist_create_copy(const fossil_arraylist_t* other);

/**
 * Move an existing array list to a new container.
 *
 * @param other The array list to move.
 * @return      A pointer to the moved array list.
 * @note        Time complexity: O(1)
 */
fossil_arraylist_t* fossil_arraylist_create_move(fossil_arraylist_t* other);

/**
 * Destroy the array list, freeing all allocated memory.
 *
 * @param alist The array list to destroy.
 * @note        Time complexity: O(n)
 */
void fossil_arraylist_destroy(fossil_arraylist_t* alist);

// *****************************************************************************
// Utility functions
// *****************************************************************************

/**
 * Insert an element at a specific index.
 *
 * @param alist The array list.
 * @param index The index at which to insert.
 * @param data  The data to insert.
 * @return      Error code indicating success or failure.
 * @note        Time complexity: O(n)
 */
int32_t fossil_arraylist_insert_at(fossil_arraylist_t* alist, size_t index, fossil_tofu_t data);

/**
 * Append an element to the end of the array list.
 *
 * @param alist The array list.
 * @param data  The data to append.
 * @return      Error code indicating success or failure.
 * @note        Time complexity: O(1)
 */
int32_t fossil_arraylist_append(fossil_arraylist_t* alist, fossil_tofu_t data);

/**
 * Prepend an element to the beginning of the array list.
 *
 * @param alist The array list.
 * @param data  The data to prepend.
 * @return      Error code indicating success or failure.
 * @note        Time complexity: O(1)
 */
int32_t fossil_arraylist_prepend(fossil_arraylist_t* alist, fossil_tofu_t data);

/**
 * Remove an element at a specific index.
 *
 * @param alist The array list.
 * @param index The index of the element to remove.
 * @return      Error code indicating success or failure.
 * @note        Time complexity: O(n)
 */
int32_t fossil_arraylist_remove_at(fossil_arraylist_t* alist, size_t index);

/**
 * Remove the first element in the array list.
 *
 * @param alist The array list.
 * @return      Error code indicating success or failure.
 * @note        Time complexity: O(1)
 */
int32_t fossil_arraylist_remove_front(fossil_arraylist_t* alist);

/**
 * Remove the last element in the array list.
 *
 * @param alist The array list.
 * @return      Error code indicating success or failure.
 * @note        Time complexity: O(1)
 */
int32_t fossil_arraylist_remove_back(fossil_arraylist_t* alist);

/**
 * Get the size of the array list.
 *
 * @param alist The array list.
 * @return      The number of elements in the array list.
 * @note        Time complexity: O(1)
 */
size_t fossil_arraylist_size(const fossil_arraylist_t* alist);

/**
 * Check if the array list is not empty.
 *
 * @param alist The array list.
 * @return      True if the array list is not empty, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_arraylist_not_empty(const fossil_arraylist_t* alist);

/**
 * Check if the array list is empty.
 *
 * @param alist The array list.
 * @return      True if the array list is empty, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_arraylist_is_empty(const fossil_arraylist_t* alist);

// *****************************************************************************
// Getter and Setter functions
// *****************************************************************************

/**
 * Get the element at a specified index.
 *
 * @param alist The array list.
 * @param index The index of the element.
 * @return      The element at the specified index.
 * @note        Time complexity: O(n)
 */
fossil_tofu_t fossil_arraylist_get(const fossil_arraylist_t* alist, size_t index);

/**
 * Get the first element in the array list.
 *
 * @param alist The array list.
 * @return      The first element.
 * @note        Time complexity: O(1)
 */
fossil_tofu_t fossil_arraylist_get_front(const fossil_arraylist_t* alist);

/**
 * Get the last element in the array list.
 *
 * @param alist The array list.
 * @return      The last element.
 * @note        Time complexity: O(1)
 */
fossil_tofu_t fossil_arraylist_get_back(const fossil_arraylist_t* alist);

/**
 * Set the element at a specified index.
 *
 * @param alist   The array list.
 * @param index   The index to update.
 * @param element The new element.
 * @note         Time complexity: O(n)
 */
void fossil_arraylist_set(fossil_arraylist_t* alist, size_t index, fossil_tofu_t element);

/**
 * Set the first element in the array list.
 *
 * @param alist   The array list.
 * @param element The new element.
 * @note         Time complexity: O(1)
 */
void fossil_arraylist_set_front(fossil_arraylist_t* alist, fossil_tofu_t element);

/**
 * Set the last element in the array list.
 *
 * @param alist   The array list.
 * @param element The new element.
 * @note         Time complexity: O(1)
 */
void fossil_arraylist_set_back(fossil_arraylist_t* alist, fossil_tofu_t element);

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_TOFU_FRAMEWORK_H */