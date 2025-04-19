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
#ifndef FOSSIL_TOFU_CROSSLIST_H
#define FOSSIL_TOFU_CROSSLIST_H

#include "tofu.h"

#ifdef __cplusplus
extern "C"
{
#endif

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
fossil_xlist_t* fossil_xlist_create_container(char* type);

/**
 * Create a new xlist with default values.
 * 
 * Time complexity: O(1)
 *
 * @return The created xlist.
 */
fossil_xlist_t* fossil_xlist_create_default(void);

/**
 * Create a new xlist by copying an existing list.
 * 
 * Time complexity: O(n)
 *
 * @param other The xlist to copy.
 * @return      The created xlist.
 */
fossil_xlist_t* fossil_xlist_create_copy(const fossil_xlist_t* other);

/**
 * Create a new xlist by moving an existing list.
 * 
 * Time complexity: O(1)
 *
 * @param other The xlist to move.
 * @return      The created xlist.
 */
fossil_xlist_t* fossil_xlist_create_move(fossil_xlist_t* other);

/**
 * Erase the contents of the xlist and free allocated memory.
 *
 * @param xlist The xlist to erase.
 * @note        Time complexity: O(n)
 */
void fossil_xlist_destroy(fossil_xlist_t* xlist);

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
int32_t fossil_xlist_insert(fossil_xlist_t* xlist, fossil_tofu_t data);

/**
 * Remove data from the xlist.
 *
 * @param xlist The xlist to remove data from.
 * @return      The error code indicating the success or failure of the operation.
 * @note        Time complexity: O(1)
 */
int32_t fossil_xlist_remove(fossil_xlist_t* xlist);

/**
 * Reverse the xlist in the forward direction.
 *
 * @param xlist The xlist to reverse.
 * @note        Time complexity: O(n)
 */
void fossil_xlist_reverse_forward(fossil_xlist_t* xlist);

/**
 * Reverse the xlist in the backward direction.
 *
 * @param xlist The xlist to reverse.
 * @note        Time complexity: O(n)
 */
void fossil_xlist_reverse_backward(fossil_xlist_t* xlist);

/**
 * Get the size of the xlist.
 *
 * @param xlist The xlist for which to get the size.
 * @return      The size of the xlist.
 * @note        Time complexity: O(n)
 */
size_t fossil_xlist_size(const fossil_xlist_t* xlist);

/**
 * Check if the xlist is not empty.
 *
 * @param xlist The xlist to check.
 * @return      True if the xlist is not empty, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_xlist_not_empty(const fossil_xlist_t* xlist);

/**
 * Check if the xlist is not a null pointer.
 *
 * @param xlist The xlist to check.
 * @return      True if the xlist is not a null pointer, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_xlist_not_cnullptr(const fossil_xlist_t* xlist);

/**
 * Check if the xlist is empty.
 *
 * @param xlist The xlist to check.
 * @return      True if the xlist is empty, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_xlist_is_empty(const fossil_xlist_t* xlist);

/**
 * Check if the xlist is a null pointer.
 *
 * @param xlist The xlist to check.
 * @return      True if the xlist is a null pointer, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_xlist_is_cnullptr(const fossil_xlist_t* xlist);

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
fossil_tofu_t fossil_xlist_get(const fossil_xlist_t* xlist, size_t index);

/**
 * Get the first element in the cross list.
 * 
 * Time complexity: O(1)
 *
 * @param xlist The cross list from which to get the first element.
 * @return      The first element in the cross list.
 */
fossil_tofu_t fossil_xlist_get_front(const fossil_xlist_t* xlist);

/**
 * Get the last element in the cross list.
 * 
 * Time complexity: O(1)
 *
 * @param xlist The cross list from which to get the last element.
 * @return      The last element in the cross list.
 */
fossil_tofu_t fossil_xlist_get_back(const fossil_xlist_t* xlist);

/**
 * Set the element at the specified index in the cross list.
 * 
 * Time complexity: O(n)
 *
 * @param xlist   The cross list in which to set the element.
 * @param index   The index at which to set the element.
 * @param element The element to set.
 */
void fossil_xlist_set(fossil_xlist_t* xlist, size_t index, fossil_tofu_t element);

/**
 * Set the first element in the cross list.
 * 
 * Time complexity: O(1)
 *
 * @param xlist   The cross list in which to set the first element.
 * @param element The element to set.
 */
void fossil_xlist_set_front(fossil_xlist_t* xlist, fossil_tofu_t element);

/**
 * Set the last element in the cross list.
 * 
 * Time complexity: O(1)
 *
 * @param xlist   The cross list in which to set the last element.
 * @param element The element to set.
 */
void fossil_xlist_set_back(fossil_xlist_t* xlist, fossil_tofu_t element);

#ifdef __cplusplus
}
#include <stdexcept>

namespace fossil {

namespace tofu {

    class XList {
    public:
        /**
         * Constructor to create a cross list with a specified type.
         *
         * @param type The type of data the cross list will store.
         * @throws std::runtime_error If the list creation fails.
         */
        XList(char* type) : xlist(fossil_xlist_create_container(type)) {
            if (xlist == nullptr) {
                throw std::runtime_error("Failed to create cross list.");
            }
        }

        /**
         * Default constructor to create a cross list with default values.
         *
         * @throws std::runtime_error If the list creation fails.
         */
        XList() : xlist(fossil_xlist_create_default()) {
            if (xlist == nullptr) {
                throw std::runtime_error("Failed to create cross list.");
            }
        }

        /**
         * Copy constructor to create a new cross list by copying another list.
         *
         * @param other The cross list to copy.
         * @throws std::runtime_error If the list creation fails.
         */
        XList(const XList& other) : xlist(fossil_xlist_create_copy(other.xlist)) {
            if (xlist == nullptr) {
                throw std::runtime_error("Failed to create cross list.");
            }
        }

        /**
         * Move constructor to create a new cross list by moving another list.
         *
         * @param other The cross list to move.
         * @throws std::runtime_error If the list creation fails.
         */
        XList(XList&& other) : xlist(fossil_xlist_create_move(other.xlist)) {
            if (xlist == nullptr) {
                throw std::runtime_error("Failed to create cross list.");
            }
        }

        /**
         * Destructor to destroy the cross list and free allocated memory.
         */
        ~XList() {
            fossil_xlist_destroy(xlist);
        }

        /**
         * Insert data into the cross list.
         *
         * @param data The data to insert.
         * @return     The error code indicating the success or failure of the operation.
         */
        int32_t insert(fossil_tofu_t data) {
            return fossil_xlist_insert(xlist, data);
        }

        /**
         * Remove data from the cross list.
         *
         * @return The error code indicating the success or failure of the operation.
         */
        int32_t remove() {
            return fossil_xlist_remove(xlist);
        }

        /**
         * Reverse the cross list in the forward direction.
         */
        void reverse_forward() {
            fossil_xlist_reverse_forward(xlist);
        }

        /**
         * Reverse the cross list in the backward direction.
         */
        void reverse_backward() {
            fossil_xlist_reverse_backward(xlist);
        }

        /**
         * Get the size of the cross list.
         *
         * @return The size of the cross list.
         */
        size_t size() const {
            return fossil_xlist_size(xlist);
        }

        /**
         * Check if the cross list is not empty.
         *
         * @return True if the cross list is not empty, false otherwise.
         */
        bool not_empty() const {
            return fossil_xlist_not_empty(xlist);
        }

        /**
         * Check if the cross list is not a null pointer.
         *
         * @return True if the cross list is not a null pointer, false otherwise.
         */
        bool not_cnullptr() const {
            return fossil_xlist_not_cnullptr(xlist);
        }

        /**
         * Check if the cross list is empty.
         *
         * @return True if the cross list is empty, false otherwise.
         */
        bool is_empty() const {
            return fossil_xlist_is_empty(xlist);
        }

        /**
         * Check if the cross list is a null pointer.
         *
         * @return True if the cross list is a null pointer, false otherwise.
         */
        bool is_cnullptr() const {
            return fossil_xlist_is_cnullptr(xlist);
        }

        /**
         * Get the element at the specified index in the cross list.
         *
         * @param index The index of the element to get.
         * @return      The element at the specified index.
         */
        fossil_tofu_t get(size_t index) const {
            return fossil_xlist_get(xlist, index);
        }

        /**
         * Get the first element in the cross list.
         *
         * @return The first element in the cross list.
         */
        fossil_tofu_t get_front() const {
            return fossil_xlist_get_front(xlist);
        }

        /**
         * Get the last element in the cross list.
         *
         * @return The last element in the cross list.
         */
        fossil_tofu_t get_back() const {
            return fossil_xlist_get_back(xlist);
        }

        /**
         * Set the element at the specified index in the cross list.
         *
         * @param index   The index at which to set the element.
         * @param element The element to set.
         */
        void set(size_t index, fossil_tofu_t element) {
            fossil_xlist_set(xlist, index, element);
        }

        /**
         * Set the first element in the cross list.
         *
         * @param element The element to set.
         */
        void set_front(fossil_tofu_t element) {
            fossil_xlist_set_front(xlist, element);
        }

        /**
         * Set the last element in the cross list.
         *
         * @param element The element to set.
         */
        void set_back(fossil_tofu_t element) {
            fossil_xlist_set_back(xlist, element);
        }

    private:
        fossil_xlist_t* xlist;
    };

} // namespace tofu

} // namespace fossil

#endif

#endif /* FOSSIL_TOFU_FRAMEWORK_H */
