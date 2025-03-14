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
    arraylist->data = NULL;
    arraylist->size = 0;
    arraylist->capacity = 0;
    arraylist->type = fossil_tofu_strdup(type);
    return arraylist;
}

fossil_arraylist_t* fossil_arraylist_create_default(void) {
    return fossil_arraylist_create_container("any");
}

fossil_arraylist_t* fossil_arraylist_create_copy(const fossil_arraylist_t* other) {
    fossil_arraylist_t* arraylist = (fossil_arraylist_t*)fossil_tofu_alloc(sizeof(fossil_arraylist_t));
    if (arraylist == NULL) {
        return NULL;
    }
    arraylist->type = fossil_tofu_strdup(other->type);
    arraylist->size = other->size;
    arraylist->capacity = other->capacity;
    arraylist->data = fossil_tofu_alloc(arraylist->capacity * sizeof(void*));
    for (size_t i = 0; i < arraylist->size; i++) {
        arraylist->data[i] = fossil_tofu_create(arraylist->type, fossil_tofu_get_value(&other->data[i]));
    }
    return arraylist;
}

fossil_arraylist_t* fossil_arraylist_create_move(fossil_arraylist_t* other) {
    fossil_arraylist_t* arraylist = (fossil_arraylist_t*)fossil_tofu_alloc(sizeof(fossil_arraylist_t));
    if (arraylist == NULL) {
        return NULL;
    }
    arraylist->type = other->type;
    arraylist->data = other->data;
    arraylist->size = other->size;
    arraylist->capacity = other->capacity;
    other->data = NULL;
    other->size = 0;
    other->capacity = 0;
    return arraylist;
}

void fossil_arraylist_destroy(fossil_arraylist_t* arraylist) {
    for (size_t i = 0; i < arraylist->size; i++) {
        fossil_tofu_destroy(&arraylist->data[i]);
    }
    fossil_tofu_free(arraylist->data);
    fossil_tofu_free(arraylist->type);
    fossil_tofu_free(arraylist);
}

// *****************************************************************************
// Utility functions
// *****************************************************************************

static int32_t fossil_arraylist_resize(fossil_arraylist_t* arraylist) {
    size_t new_capacity = (arraylist->capacity == 0) ? 1 : arraylist->capacity * 2;
    void** new_data = (void**)fossil_tofu_alloc(new_capacity * sizeof(void*));
    if (new_data == NULL) {
        return FOSSIL_TOFU_FAILURE;
    }
    for (size_t i = 0; i < arraylist->size; i++) {
        new_data[i] = arraylist->data[i];
    }
    fossil_tofu_free(arraylist->data);
    arraylist->data = new_data;
    arraylist->capacity = new_capacity;
    return FOSSIL_TOFU_SUCCESS;
}

int32_t fossil_arraylist_insert(fossil_arraylist_t* arraylist, char* data) {
    if (arraylist->size == arraylist->capacity) {
        if (fossil_arraylist_resize(arraylist) == FOSSIL_TOFU_FAILURE) {
            return FOSSIL_TOFU_FAILURE;
        }
    }
    arraylist->data[arraylist->size] = fossil_tofu_create(arraylist->type, data);
    arraylist->size++;
    return FOSSIL_TOFU_SUCCESS;
}

int32_t fossil_arraylist_remove(fossil_arraylist_t* arraylist, size_t index) {
    if (index >= arraylist->size) {
        return FOSSIL_TOFU_FAILURE;
    }
    fossil_tofu_destroy(&arraylist->data[index]);
    for (size_t i = index; i < arraylist->size - 1; i++) {
        arraylist->data[i] = arraylist->data[i + 1];
    }
    arraylist->size--;
    return FOSSIL_TOFU_SUCCESS;
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

bool fossil_arraylist_is_cnullptr(const fossil_arraylist_t* alist) {
    return (alist == NULL);
}

bool fossil_arraylist_not_cnullptr(const fossil_arraylist_t* alist) {
    return (alist != NULL);
}

bool fossil_arraylist_is_empty(const fossil_arraylist_t* alist) {
    return (fossil_arraylist_is_cnullptr(alist) || alist->size == 0);
}

bool fossil_arraylist_not_empty(const fossil_arraylist_t* alist) {
    return (fossil_arraylist_not_cnullptr(alist) && alist->size > 0);
}
