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
#include "fossil/tofu/arraylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// *****************************************************************************
// Function prototypes
// *****************************************************************************

fossil_arraylist_t* fossil_arraylist_create_container(char* type) {
    fossil_arraylist_t* arraylist = (fossil_arraylist_t*)fossil_tofu_alloc(sizeof(fossil_arraylist_t));
    if (arraylist == NULL) {
        return NULL;
    }
    arraylist->head = NULL;
    arraylist->tail = NULL;
    arraylist->size = 0;
    arraylist->type = fossil_tofu_strdup(type);
    return arraylist;
}

// Create a default array list
fossil_arraylist_t* fossil_arraylist_create_default(void) {
    return fossil_arraylist_create_container("any");
}

// Create a copy of an array list
fossil_arraylist_t* fossil_arraylist_create_copy(const fossil_arraylist_t* other) {
    fossil_arraylist_t* arraylist = (fossil_arraylist_t*)fossil_tofu_alloc(sizeof(fossil_arraylist_t));
    if (arraylist == NULL) {
        return NULL;
    }
    arraylist->type = fossil_tofu_strdup(other->type);
    arraylist->size = other->size;
    arraylist->head = NULL;
    arraylist->tail = NULL;

    // Copy the elements from the other list
    fossil_arraylist_node_t* node = other->head;
    while (node) {
        fossil_arraylist_insert(arraylist, fossil_tofu_get_value(&node->data));
        node = node->next;
    }

    return arraylist;
}

// Move an array list
fossil_arraylist_t* fossil_arraylist_create_move(fossil_arraylist_t* other) {
    fossil_arraylist_t* arraylist = (fossil_arraylist_t*)fossil_tofu_alloc(sizeof(fossil_arraylist_t));
    if (arraylist == NULL) {
        return NULL;
    }
    arraylist->type = other->type;
    arraylist->size = other->size;
    arraylist->head = other->head;
    arraylist->tail = other->tail;

    // Reset the other list
    other->head = NULL;
    other->tail = NULL;
    other->size = 0;
    return arraylist;
}

// Destroy an array list
void fossil_arraylist_destroy(fossil_arraylist_t* arraylist) {
    fossil_arraylist_node_t* node = arraylist->head;
    while (node) {
        fossil_tofu_destroy(&node->data);
        fossil_arraylist_node_t* next = node->next;
        fossil_tofu_free(node);
        node = next;
    }
    fossil_tofu_free(arraylist->type);
    fossil_tofu_free(arraylist);
}

// *****************************************************************************
// Utility functions
// *****************************************************************************

int32_t fossil_arraylist_insert(fossil_arraylist_t* arraylist, char* data) {
    fossil_arraylist_node_t* new_node = (fossil_arraylist_node_t*)fossil_tofu_alloc(sizeof(fossil_arraylist_node_t));
    if (new_node == NULL) {
        return FOSSIL_TOFU_FAILURE;
    }
    new_node->data = fossil_tofu_create(arraylist->type, data);
    new_node->prev = arraylist->tail;
    new_node->next = NULL;

    if (arraylist->tail) {
        arraylist->tail->next = new_node;
    }
    arraylist->tail = new_node;

    if (arraylist->head == NULL) {
        arraylist->head = new_node;
    }

    arraylist->size++;
    return FOSSIL_TOFU_SUCCESS;
}

// Remove the last element from the array list
int32_t fossil_arraylist_remove(fossil_arraylist_t* arraylist) {
    if (arraylist->size == 0) {
        return FOSSIL_TOFU_FAILURE;
    }

    fossil_arraylist_node_t* last_node = arraylist->tail;
    if (last_node->prev) {
        last_node->prev->next = NULL;
    }
    arraylist->tail = last_node->prev;

    fossil_tofu_destroy(&last_node->data);
    fossil_tofu_free(last_node);

    arraylist->size--;
    return FOSSIL_TOFU_SUCCESS;
}

// Reverse the array list (in-place)
void fossil_arraylist_reverse(fossil_arraylist_t* arraylist) {
    fossil_arraylist_node_t* current = arraylist->head;
    fossil_arraylist_node_t* temp = NULL;

    while (current) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    // Swap head and tail
    if (temp) {
        arraylist->head = temp->prev;
    }
}

size_t fossil_arraylist_size(const fossil_arraylist_t* arraylist) {
    return arraylist->size;
}

bool fossil_arraylist_not_empty(const fossil_arraylist_t* arraylist) {
    return arraylist->size > 0;
}

bool fossil_arraylist_not_cnullptr(const fossil_arraylist_t* arraylist) {
    return arraylist != NULL;
}

bool fossil_arraylist_is_empty(const fossil_arraylist_t* arraylist) {
    return arraylist->size == 0;
}

bool fossil_arraylist_is_cnullptr(const fossil_arraylist_t* arraylist) {
    return arraylist == NULL;
}

// *****************************************************************************
// Getter and setter functions
// *****************************************************************************

char* fossil_arraylist_get(const fossil_arraylist_t* arraylist, size_t index) {
    if (index >= arraylist->size) {
        return NULL;
    }
    return fossil_tofu_get_value(&arraylist->data[index]);
}

char* fossil_arraylist_get_front(const fossil_arraylist_t* arraylist) {
    return (arraylist->size > 0) ? fossil_tofu_get_value(&arraylist->data[0]) : NULL;
}

char* fossil_arraylist_get_back(const fossil_arraylist_t* arraylist) {
    return (arraylist->size > 0) ? fossil_tofu_get_value(&arraylist->data[arraylist->size - 1]) : NULL;
}

void fossil_arraylist_set(fossil_arraylist_t* arraylist, size_t index, char* element) {
    if (index < arraylist->size) {
        fossil_tofu_set_value(&arraylist->data[index], element);
    }
}

void fossil_arraylist_set_front(fossil_arraylist_t* arraylist, char* element) {
    if (arraylist->size > 0) {
        fossil_tofu_set_value(&arraylist->data[0], element);
    }
}

void fossil_arraylist_set_back(fossil_arraylist_t* arraylist, char* element) {
    if (arraylist->size > 0) {
        fossil_tofu_set_value(&arraylist->data[arraylist->size - 1], element);
    }
}
