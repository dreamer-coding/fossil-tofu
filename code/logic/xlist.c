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
#include "fossil/tofu/xlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// *****************************************************************************
// Type definitions
// *****************************************************************************

// Node structure for the xlist
typedef struct fossil_xlist_node_t {
    fossil_tofu_t data;
    struct fossil_xlist_node_t* prev;
    struct fossil_xlist_node_t* next;
    struct fossil_xlist_node_t* up;
    struct fossil_xlist_node_t* down;
} fossil_xlist_node_t;

// Xlist structure
typedef struct fossil_xlist_t {
    fossil_xlist_node_t* head;
    fossil_xlist_node_t* tail;
    char* type;
} fossil_xlist_t;

// *****************************************************************************
// Function prototypes
// *****************************************************************************

/**
 * Create a new xlist with the specified data type.
 *
 * @param list_type The type of data the xlist will store.
 * @return          The created xlist.
 * @note            Time complexity: O(1)
 */
fossil_xlist_t* fossil_xlist_create_container(char* type) {
    fossil_xlist_t* xlist = (fossil_xlist_t*)malloc(sizeof(fossil_xlist_t));
    if (xlist == NULL) {
        return NULL;  // Memory allocation failed
    }
    xlist->head = NULL;
    xlist->tail = NULL;
    xlist->type = fossil_tofu_strdup(type);
    return xlist;
}

/**
 * Create a new xlist with default values.
 * 
 * Time complexity: O(1)
 *
 * @return The created xlist.
 */
fossil_xlist_t* fossil_xlist_create_default(void) {
    return fossil_xlist_create_container("any");
}

/**
 * Create a new xlist by copying an existing list.
 * 
 * Time complexity: O(n)
 *
 * @param other The xlist to copy.
 * @return      The created xlist.
 */
fossil_xlist_t* fossil_xlist_create_copy(const fossil_xlist_t* other) {
    if (other == NULL) {
        return NULL;  // Null pointer check
    }
    fossil_xlist_t* xlist = (fossil_xlist_t*)malloc(sizeof(fossil_xlist_t));
    if (xlist == NULL) {
        return NULL;  // Memory allocation failed
    }
    xlist->type = fossil_tofu_strdup(other->type);
    xlist->head = NULL;
    xlist->tail = NULL;

    // Copy the elements from the other list
    fossil_xlist_node_t* current = other->head;
    while (current != NULL) {
        fossil_xlist_insert(xlist, current->data);
        current = current->next;
    }
    return xlist;
}

/**
 * Create a new xlist by moving an existing list.
 * 
 * Time complexity: O(1)
 *
 * @param other The xlist to move.
 * @return      The created xlist.
 */
fossil_xlist_t* fossil_xlist_create_move(fossil_xlist_t* other) {
    if (other == NULL) {
        return NULL;  // Null pointer check
    }
    fossil_xlist_t* xlist = (fossil_xlist_t*)malloc(sizeof(fossil_xlist_t));
    if (xlist == NULL) {
        return NULL;  // Memory allocation failed
    }
    xlist->type = other->type;
    xlist->head = other->head;
    xlist->tail = other->tail;
    other->head = NULL;
    other->tail = NULL;
    return xlist;
}

/**
 * Erase the contents of the xlist and free allocated memory.
 *
 * @param xlist The xlist to erase.
 * @note        Time complexity: O(n)
 */
void fossil_xlist_destroy(fossil_xlist_t* xlist) {
    if (xlist == NULL) {
        return;  // Null pointer check
    }
    fossil_xlist_node_t* current = xlist->head;
    while (current != NULL) {
        fossil_xlist_node_t* next = current->next;
        fossil_tofu_destroy(&current->data);
        free(current);
        current = next;
    }
    free(xlist->type);
    free(xlist);
}

// *****************************************************************************
// Utility functions
// *****************************************************************************

/**
 * Insert data into the xlist.
 *
 * @param xlist The xlist to insert data into.
 * @param data  The data to insert.
 * @return      The error code indicating the success or failure of the operation.
 * @note        Time complexity: O(1)
 */
int32_t fossil_xlist_insert(fossil_xlist_t* xlist, fossil_tofu_t data) {
    if (xlist == NULL) {
        return FOSSIL_TOFU_FAILURE;  // Null pointer check
    }
    fossil_xlist_node_t* node = (fossil_xlist_node_t*)malloc(sizeof(fossil_xlist_node_t));
    if (node == NULL) {
        return FOSSIL_TOFU_FAILURE;  // Memory allocation failed
    }
    node->data = data;
    node->next = NULL;
    node->prev = xlist->tail;
    node->up = NULL;
    node->down = NULL;

    if (xlist->tail != NULL) {
        xlist->tail->next = node;
    } else {
        xlist->head = node;  // First element in the list
    }
    xlist->tail = node;
    return FOSSIL_TOFU_SUCCESS;
}

/**
 * Remove data from the xlist.
 *
 * @param xlist The xlist to remove data from.
 * @return      The error code indicating the success or failure of the operation.
 * @note        Time complexity: O(1)
 */
int32_t fossil_xlist_remove(fossil_xlist_t* xlist) {
    if (xlist == NULL || xlist->head == NULL) {
        return FOSSIL_TOFU_FAILURE;  // Null pointer check or empty list
    }
    fossil_xlist_node_t* node = xlist->head;
    if (xlist->head == xlist->tail) {  // Only one element in the list
        xlist->head = NULL;
        xlist->tail = NULL;
    } else {
        xlist->head = xlist->head->next;
        xlist->head->prev = NULL;
    }
    fossil_tofu_destroy(&node->data);
    free(node);
    return FOSSIL_TOFU_SUCCESS;
}

/**
 * Reverse the xlist in the forward direction.
 *
 * @param xlist The xlist to reverse.
 * @note        Time complexity: O(n)
 */
void fossil_xlist_reverse_forward(fossil_xlist_t* xlist) {
    if (xlist == NULL) {
        return;  // Null pointer check
    }
    fossil_xlist_node_t* current = xlist->head;
    fossil_xlist_node_t* prev = NULL;
    while (current != NULL) {
        fossil_xlist_node_t* next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }
    xlist->head = prev;
}

/**
 * Reverse the xlist in the backward direction.
 *
 * @param xlist The xlist to reverse.
 * @note        Time complexity: O(n)
 */
void fossil_xlist_reverse_backward(fossil_xlist_t* xlist) {
    if (xlist == NULL) {
        return;  // Null pointer check
    }
    fossil_xlist_node_t* current = xlist->tail;
    fossil_xlist_node_t* prev = NULL;
    while (current != NULL) {
        fossil_xlist_node_t* next = current->prev;
        current->prev = prev;
        current->next = next;
        prev = current;
        current = next;
    }
    xlist->tail = prev;
}

/**
 * Get the size of the xlist.
 *
 * @param xlist The xlist for which to get the size.
 * @return      The size of the xlist.
 * @note        Time complexity: O(n)
 */
size_t fossil_xlist_size(const fossil_xlist_t* xlist) {
    size_t size = 0;
    if (xlist == NULL) {
        return size;  // Null pointer check
    }
    fossil_xlist_node_t* current = xlist->head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

/**
 * Check if the xlist is not empty.
 *
 * @param xlist The xlist to check.
 * @return      True if the xlist is not empty, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_xlist_not_empty(const fossil_xlist_t* xlist) {
    return xlist != NULL && xlist->head != NULL;
}

/**
 * Check if the xlist is not a null pointer.
 *
 * @param xlist The xlist to check.
 * @return      True if the xlist is not a null pointer, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_xlist_not_cnullptr(const fossil_xlist_t* xlist) {
    return xlist != NULL;
}

/**
 * Check if the xlist is empty.
 *
 * @param xlist The xlist to check.
 * @return      True if the xlist is empty, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_xlist_is_empty(const fossil_xlist_t* xlist) {
    return xlist == NULL || xlist->head == NULL;
}

/**
 * Check if the xlist is a null pointer.
 *
 * @param xlist The xlist to check.
 * @return      True if the xlist is a null pointer, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_xlist_is_cnullptr(const fossil_xlist_t* xlist) {
    return xlist == NULL;
}

// *****************************************************************************
// Getter and setter functions
// *****************************************************************************

/**
 * Get the element at the specified index in the cross list.
 * 
 * Time complexity: O(n)
 *
 * @param xlist The cross list from which to get the element.
 * @param index The index of the element to get.
 * @return      The element at the specified index.
 */
fossil_tofu_t fossil_xlist_get(const fossil_xlist_t* xlist, size_t index) {
    if (xlist == NULL || index >= fossil_xlist_size(xlist)) {
        return (fossil_tofu_t){0};  // Null pointer check or index out of bounds
    }
    fossil_xlist_node_t* current = xlist->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

/**
 * Get the first element in the cross list.
 * 
 * Time complexity: O(1)
 *
 * @param xlist The cross list from which to get the first element.
 * @return      The first element in the cross list.
 */
fossil_tofu_t fossil_xlist_get_front(const fossil_xlist_t* xlist) {
    if (xlist == NULL || xlist->head == NULL) {
        return (fossil_tofu_t){0};  // Null pointer check or empty list
    }
    return xlist->head->data;
}

/**
 * Get the last element in the cross list.
 * 
 * Time complexity: O(1)
 *
 * @param xlist The cross list from which to get the last element.
 * @return      The last element in the cross list.
 */
fossil_tofu_t fossil_xlist_get_back(const fossil_xlist_t* xlist) {
    if (xlist == NULL || xlist->tail == NULL) {
        return (fossil_tofu_t){0};  // Null pointer check or empty list
    }
    return xlist->tail->data;
}

/**
 * Set the element at the specified index in the cross list.
 * 
 * Time complexity: O(n)
 *
 * @param xlist   The cross list in which to set the element.
 * @param index   The index at which to set the element.
 * @param element The element to set.
 */
void fossil_xlist_set(fossil_xlist_t* xlist, size_t index, fossil_tofu_t element) {
    if (xlist == NULL || index >= fossil_xlist_size(xlist)) {
        return;  // Null pointer check or index out of bounds
    }
    fossil_xlist_node_t* current = xlist->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = element;
}

/**
 * Set the first element in the cross list.
 * 
 * Time complexity: O(1)
 *
 * @param xlist   The cross list in which to set the first element.
 * @param element The element to set.
 */
void fossil_xlist_set_front(fossil_xlist_t* xlist, fossil_tofu_t element) {
    if (xlist == NULL || xlist->head == NULL) {
        return;  // Null pointer check or empty list
    }
    xlist->head->data = element;
}

/**
 * Set the last element in the cross list.
 * 
 * Time complexity: O(1)
 *
 * @param xlist   The cross list in which to set the last element.
 * @param element The element to set.
 */
void fossil_xlist_set_back(fossil_xlist_t* xlist, fossil_tofu_t element) {
    if (xlist == NULL || xlist->tail == NULL) {
        return;  // Null pointer check or empty list
    }
    xlist->tail->data = element;
}
