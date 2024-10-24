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
#include "fossil/tofu/setof.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

fossil_set_t* fossil_set_create(char* type) {
    if (!type) {
        fprintf(stderr, "Error: type cannot be NULL\n");
        return NULL;
    }

    fossil_set_t* set = (fossil_set_t*)fossil_tofu_alloc(sizeof(fossil_set_t));
    if (!set) {
        fprintf(stderr, "Error: Memory allocation failed for fossil_set_t\n");
        return NULL;
    }

    set->head = NULL;
    set->type = type;  // Assuming type is a static string or managed separately
    return set;
}

void fossil_set_destroy(fossil_set_t* set) {
    if (!set) {
        fprintf(stderr, "Error: set cannot be NULL\n");
        return;
    }

    fossil_set_node_t* current = set->head;
    while (current) {
        fossil_set_node_t* next = current->next;
        fossil_tofu_free(current);
        current = next;
    }
    set->head = NULL;
    fossil_tofu_free(set);
}

int32_t fossil_set_insert(fossil_set_t* set, fossil_tofu_t data) {
    if (!set) {
        fprintf(stderr, "Error: set cannot be NULL\n");
        return -1;
    }

    if (fossil_set_contains(set, data)) {
        return FOSSIL_TOFU_FAILURE;  // Duplicate element, insert fails
    }

    fossil_set_node_t* new_node = (fossil_set_node_t*)fossil_tofu_alloc(sizeof(fossil_set_node_t));
    if (!new_node) {
        fprintf(stderr, "Error: Memory allocation failed for fossil_set_node_t\n");
        return -2;  // Allocation failed
    }

    new_node->data = data;
    new_node->next = set->head;
    set->head = new_node;

    return FOSSIL_TOFU_SUCCESS;  // Success
}

int32_t fossil_set_remove(fossil_set_t* set, fossil_tofu_t data) {
    if (!set) {
        fprintf(stderr, "Error: set cannot be NULL\n");
        return -1;
    }

    fossil_set_node_t* current = set->head;
    fossil_set_node_t* prev = NULL;

    while (current) {
        if (fossil_tofu_equals(current->data, data)) {
            if (prev) {
                prev->next = current->next;
            } else {
                set->head = current->next;
            }
            fossil_tofu_free(current);
            return FOSSIL_TOFU_SUCCESS;  // Success
        }
        prev = current;
        current = current->next;
    }
    return FOSSIL_TOFU_FAILURE;  // Element not found
}

int32_t fossil_set_search(const fossil_set_t* set, fossil_tofu_t data) {
    if (!set) {
        fprintf(stderr, "Error: set cannot be NULL\n");
        return -1;
    }

    fossil_set_node_t* current = set->head;
    while (current) {
        if (fossil_tofu_equals(current->data, data)) {
            return FOSSIL_TOFU_SUCCESS;  // Found
        }
        current = current->next;
    }
    return FOSSIL_TOFU_FAILURE;  // Not found
}

int32_t fossil_set_contains(const fossil_set_t* set, fossil_tofu_t data) {
    if (!set) {
        fprintf(stderr, "Error: set cannot be NULL\n");
        return -1;
    }

    return fossil_set_search(set, data) == 0;
}

size_t fossil_set_size(const fossil_set_t* set) {
    if (!set) {
        fprintf(stderr, "Error: set cannot be NULL\n");
        return 0;
    }

    size_t count = 0;
    fossil_set_node_t* current = set->head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

bool fossil_set_not_empty(const fossil_set_t* set) {
    if (!set) {
        fprintf(stderr, "Error: set cannot be NULL\n");
        return false;
    }
    return set->head != NULL;
}

bool fossil_set_not_cnullptr(const fossil_set_t* set) {
    return set != NULL;
}

bool fossil_set_is_empty(const fossil_set_t* set) {
    return set == NULL || set->head == NULL;
}

bool fossil_set_is_cnullptr(const fossil_set_t* set) {
    return set == NULL;
}
