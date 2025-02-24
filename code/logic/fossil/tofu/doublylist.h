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
#ifndef FOSSIL_TOFU_DOUBLYLIST_H
#define FOSSIL_TOFU_DOUBLYLIST_H

#include "tofu.h"

#ifdef __cplusplus
extern "C"
{
#endif

// *****************************************************************************
// Type definitions
// *****************************************************************************

// Node structure for the doubly linked list
typedef struct fossil_dlist_node_t {
    fossil_tofu_t data;
    struct fossil_dlist_node_t* prev;
    struct fossil_dlist_node_t* next;
} fossil_dlist_node_t;

// Doubly linked list structure
typedef struct fossil_dlist_t {
    fossil_dlist_node_t* head;
    fossil_dlist_node_t* tail;
    char* type;
} fossil_dlist_t;

// *****************************************************************************
// Function prototypes
// *****************************************************************************

/**
 * Create a new doubly linked list with the specified data type.
 *
 * @param list_type The type of data the doubly linked list will store.
 * @return          The created doubly linked list.
 * @note            Time complexity: O(1)
 */
fossil_dlist_t* fossil_dlist_create_container(char* type);

/**
 * Create a new doubly linked list with default values.
 * 
 * Time complexity: O(1)
 *
 * @return The created doubly linked list.
 */
fossil_dlist_t* fossil_dlist_create_default(void);

/**
 * Create a new doubly linked list by copying an existing list.
 * 
 * Time complexity: O(n)
 *
 * @param other The doubly linked list to copy.
 * @return      The created doubly linked list.
 */
fossil_dlist_t* fossil_dlist_create_copy(const fossil_dlist_t* other);

/**
 * Create a new doubly linked list by moving an existing list.
 * 
 * Time complexity: O(1)
 *
 * @param other The doubly linked list to move.
 * @return      The created doubly linked list.
 */
fossil_dlist_t* fossil_dlist_create_move(fossil_dlist_t* other);

/**
 * Erase the contents of the doubly linked list and fossil_tofu_free allocated memory.
 *
 * @param dlist The doubly linked list to erase.
 * @note        Time complexity: O(n)
 */
void fossil_dlist_destroy(fossil_dlist_t* dlist);

// *****************************************************************************
// Utility functions
// *****************************************************************************

/**
 * Insert data into the doubly linked list.
 *
 * @param dlist The doubly linked list to insert data into.
 * @param data  The data to insert.
 * @return      The error code indicating the success or failure of the operation.
 * @note        Time complexity: O(1)
 */
int32_t fossil_dlist_insert(fossil_dlist_t* dlist, char *data);

/**
 * Remove data from the doubly linked list.
 *
 * @param dlist The doubly linked list to remove data from.
 * @return      The error code indicating the success or failure of the operation.
 * @note        Time complexity: O(1)
 */
int32_t fossil_dlist_remove(fossil_dlist_t* dlist);

/**
 * Reverse the doubly linked list in the forward direction.
 *
 * @param dlist The doubly linked list to reverse.
 * @note        Time complexity: O(n)
 */
void fossil_dlist_reverse_forward(fossil_dlist_t* dlist);

/**
 * Reverse the doubly linked list in the backward direction.
 *
 * @param dlist The doubly linked list to reverse.
 * @note        Time complexity: O(n)
 */
void fossil_dlist_reverse_backward(fossil_dlist_t* dlist);

/**
 * Get the size of the doubly linked list.
 *
 * @param dlist The doubly linked list for which to get the size.
 * @return      The size of the doubly linked list.
 * @note        Time complexity: O(n)
 */
size_t fossil_dlist_size(const fossil_dlist_t* dlist);

/**
 * Check if the doubly linked list is not empty.
 *
 * @param dlist The doubly linked list to check.
 * @return      True if the doubly linked list is not empty, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_dlist_not_empty(const fossil_dlist_t* dlist);

/**
 * Check if the doubly linked list is not a null pointer.
 *
 * @param dlist The doubly linked list to check.
 * @return      True if the doubly linked list is not a null pointer, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_dlist_not_cnullptr(const fossil_dlist_t* dlist);

/**
 * Check if the doubly linked list is empty.
 *
 * @param dlist The doubly linked list to check.
 * @return      True if the doubly linked list is empty, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_dlist_is_empty(const fossil_dlist_t* dlist);

/**
 * Check if the doubly linked list is a null pointer.
 *
 * @param dlist The doubly linked list to check.
 * @return      True if the doubly linked list is a null pointer, false otherwise.
 * @note        Time complexity: O(1)
 */
bool fossil_dlist_is_cnullptr(const fossil_dlist_t* dlist);

// *****************************************************************************
// Getter and setter functions
// *****************************************************************************

/**
 * Get the element at the specified index in the doubly linked list.
 * 
 * Time complexity: O(n)
 *
 * @param dlist The doubly linked list from which to get the element.
 * @param index The index of the element to get.
 * @return      The element at the specified index.
 */
char *fossil_dlist_get(const fossil_dlist_t* dlist, size_t index);

/**
 * Get the first element in the doubly linked list.
 * 
 * Time complexity: O(1)
 *
 * @param dlist The doubly linked list from which to get the first element.
 * @return      The first element in the doubly linked list.
 */
char *fossil_dlist_get_front(const fossil_dlist_t* dlist);

/**
 * Get the last element in the doubly linked list.
 * 
 * Time complexity: O(1)
 *
 * @param dlist The doubly linked list from which to get the last element.
 * @return      The last element in the doubly linked list.
 */
char *fossil_dlist_get_back(const fossil_dlist_t* dlist);

/**
 * Set the element at the specified index in the doubly linked list.
 * 
 * Time complexity: O(n)
 *
 * @param dlist   The doubly linked list in which to set the element.
 * @param index   The index at which to set the element.
 * @param element The element to set.
 */
void fossil_dlist_set(fossil_dlist_t* dlist, size_t index, char *element);

/**
 * Set the first element in the doubly linked list.
 * 
 * Time complexity: O(1)
 *
 * @param dlist   The doubly linked list in which to set the first element.
 * @param element The element to set.
 */
void fossil_dlist_set_front(fossil_dlist_t* dlist, char *element);

/**
 * Set the last element in the doubly linked list.
 * 
 * Time complexity: O(1)
 *
 * @param dlist   The doubly linked list in which to set the last element.
 * @param element The element to set.
 */
void fossil_dlist_set_back(fossil_dlist_t* dlist, char *element);

#ifdef __cplusplus
}
#include <stdexcept>
#include <string>

/**
 * Fossil Logic namespace
 */
namespace fossil {

    /**
     * Tofu namespace
     */
    namespace tofu {

        /**
         * Doubly linked list class
         */
        class DList {
        public:
            /**
             * Create a new doubly linked list with the specified data type.
             *
             * @param type The type of data the doubly linked list will store.
             */ 
            DList(char* type) : dlist(fossil_dlist_create_container(type)) {
                if (dlist == nullptr) {
                throw std::runtime_error("Failed to create doubly linked list");
                }
            }

            /**
             * Create a new doubly linked list with specified data type.
             * 
             * @param type The type of data the doubly linked list will store.
             */
            DList(std::string type) : dlist(fossil_dlist_create_container(const_cast<char*>(type.c_str()))) {
                if (dlist == nullptr) {
                    throw std::runtime_error("Failed to create doubly linked list");
                }
            }

            /**
             * Create a new doubly linked list with default values.
             */
            DList() : dlist(fossil_dlist_create_default()) {
                if (dlist == nullptr) {
                    throw std::runtime_error("Failed to create doubly linked list");
                }
            }

            /**
             * Create a new doubly linked list by copying an existing list.
             * 
             * @param other The doubly linked list to copy.
             */
            DList(const DList& other) : dlist(fossil_dlist_create_copy(other.dlist)) {
                if (dlist == nullptr) {
                    throw std::runtime_error("Failed to create doubly linked list");
                }
            }

            /**
             * Create a new doubly linked list by moving an existing list.
             * 
             * @param other The doubly linked list to move.
             */
            DList(DList&& other) noexcept : dlist(fossil_dlist_create_move(other.dlist)) {
                other.dlist = nullptr;
            }

            /**
             * Destroy the doubly linked list and fossil_tofu_free allocated memory.
             */
            ~DList() {
                fossil_dlist_destroy(dlist);
            }

            /**
             * Copy assignment operator.
             * 
             * @param other The doubly linked list to copy.
             * @return      The copied doubly linked list.
             */
            DList& operator=(const DList& other) {
                if (this != &other) {
                    fossil_dlist_destroy(dlist);
                    dlist = fossil_dlist_create_copy(other.dlist);
                    if (dlist == nullptr) {
                        throw std::runtime_error("Failed to create doubly linked list");
                    }
                }
                return *this;
            }

            /**
             * Move assignment operator.
             * 
             * @param other The doubly linked list to move.
             * @return      The moved doubly linked list.
             */
            DList& operator=(DList&& other) noexcept {
                if (this != &other) {
                    fossil_dlist_destroy(dlist);
                    dlist = fossil_dlist_create_move(other.dlist);
                    other.dlist = nullptr;
                }
                return *this;
            }

            /**
             * Insert data into the doubly linked list.
             *
             * @param data The data to insert.
             */
            void insert(char *data) {
                if (fossil_dlist_insert(dlist, data) != 0) {
                    throw std::runtime_error("Failed to insert data into doubly linked list");
                }
            }

            /**
             * Insert data into the doubly linked list.
             *
             * @param data The data to insert.
             */
            void insert(const std::string& data) {
                if (fossil_dlist_insert(dlist, const_cast<char*>(data.c_str())) != 0) {
                    throw std::runtime_error("Failed to insert data into doubly linked list");
                }
            }

            /**
             * Remove data from the doubly linked list.
             */
            void remove() {
                if (fossil_dlist_remove(dlist) != 0) {
                    throw std::runtime_error("Failed to remove data from doubly linked list");
                }
            }

            /**
             * Reverse the doubly linked list in the forward direction.
             */
            void reverse_forward() {
                fossil_dlist_reverse_forward(dlist);
            }

            /**
             * Reverse the doubly linked list in the backward direction.
             */
            void reverse_backward() {
                fossil_dlist_reverse_backward(dlist);
            }

            /**
             * Get the size of the doubly linked list.
             *
             * @return The size of the doubly linked list.
             */
            size_t size() const {
                return fossil_dlist_size(dlist);
            }

            /**
             * Check if the doubly linked list is not empty.
             *
             * @return True if the doubly linked list is not empty, false otherwise.
             */
            bool not_empty() const {
                return fossil_dlist_not_empty(dlist);
            }

            /**
             * Check if the doubly linked list is not a null pointer.
             *
             * @return True if the doubly linked list is not a null pointer, false otherwise.
             */
            bool not_cnullptr() const {
                return fossil_dlist_not_cnullptr(dlist);
            }

            /**
             * Check if the doubly linked list is empty.
             *
             * @return True if the doubly linked list is empty, false otherwise.
             */
            bool is_empty() const {
                return fossil_dlist_is_empty(dlist);
            }

            /**
             * Check if the doubly linked list is a null pointer.
             *
             * @return True if the doubly linked list is a null pointer, false otherwise.
             */
            bool is_cnullptr() const {
                return fossil_dlist_is_cnullptr(dlist);
            }

            /**
             * Get the element at the specified index in the doubly linked list.
             * 
             * @param index The index of the element to get.
             * @return      The element at the specified index.
             */
            char *get(size_t index) const {
                return fossil_dlist_get(dlist, index);
            }

            /**
             * Get the first element in the doubly linked list.
             * 
             * @return The first element in the doubly linked list.
             */
            char *get_front() const {
                return fossil_dlist_get_front(dlist);
            }

            /**
             * Get the last element in the doubly linked list.
             * 
             * @return The last element in the doubly linked list.
             */
            char *get_back() const {
                return fossil_dlist_get_back(dlist);
            }

            /**
             * Set the element at the specified index in the doubly linked list.
             * 
             * @param index   The index at which to set the element.
             * @param element The element to set.
             */
            void set(size_t index, char *element) {
                fossil_dlist_set(dlist, index, element);
            }

            /**
             * Set the element at the specified index in the doubly linked list.
             * 
             * @param index   The index at which to set the element.
             * @param element The element to set.
             */
            void set_front(char *element) {
                fossil_dlist_set_front(dlist, element);
            }

            /**
             * Set the element at the specified index in the doubly linked list.
             * 
             * @param index   The index at which to set the element.
             * @param element The element to set.
             */
            void set_front(const std::string& element) {
                fossil_dlist_set_front(dlist, const_cast<char*>(element.c_str()));
            }

            /**
             * Set the element at the specified index in the doubly linked list.
             * 
             * @param index   The index at which to set the element.
             * @param element The element to set.
             */
            void set_back(char *element) {
                fossil_dlist_set_back(dlist, element);
            }

            /**
             * Set the element at the specified index in the doubly linked list.
             * 
             * @param index   The index at which to set the element.
             * @param element The element to set.
             */
            void set_back(const std::string& element) {
                fossil_dlist_set_back(dlist, const_cast<char*>(element.c_str()));
            }

        private:
            fossil_dlist_t* dlist;
        };

    }

} // namespace fossil

#endif

#endif /* FOSSIL_TOFU_FRAMEWORK_H */
