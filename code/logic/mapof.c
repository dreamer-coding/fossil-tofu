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
#include "fossil/tofu/mapof.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new map with a given type instead of capacity
fossil_tofu_mapof_t fossil_tofu_mapof_create(const char *type) {
    fossil_tofu_mapof_t map;

    // Validate if the provided type is supported
    if (!fossil_tofu_is_valid_type(type)) {
        fprintf(stderr, "Error: Invalid type '%s' for map creation.\n", type);
        exit(EXIT_FAILURE);
    }

    // Assign an initial capacity based on type
    if (strcmp(type, "int") == 0 || strcmp(type, "uint") == 0) {
        map.capacity = 10;
    } else if (strcmp(type, "cstr") == 0 || strcmp(type, "bstr") == 0 || strcmp(type, "wstr") == 0) {
        map.capacity = 20;
    } else if (strcmp(type, "float") == 0 || strcmp(type, "double") == 0) {
        map.capacity = 15;
    } else {
        map.capacity = 5;
    }

    map.keys = (fossil_tofu_t *)fossil_tofu_alloc(map.capacity * sizeof(fossil_tofu_t));
    map.values = (fossil_tofu_t *)fossil_tofu_alloc(map.capacity * sizeof(fossil_tofu_t));
    map.size = 0;

    return map;
}

// Function to add a key-value pair to the map
void fossil_tofu_mapof_add(fossil_tofu_mapof_t *map, fossil_tofu_t key, fossil_tofu_t value) {
    if (map->size >= map->capacity) {
        map->capacity *= 2;
        map->keys = (fossil_tofu_t *)fossil_tofu_realloc(map->keys, map->capacity * sizeof(fossil_tofu_t));
        map->values = (fossil_tofu_t *)fossil_tofu_realloc(map->values, map->capacity * sizeof(fossil_tofu_t));
    }
    map->keys[map->size] = key;
    map->values[map->size] = value;
    map->size++;
}

// Function to get a value by key from the map
fossil_tofu_t fossil_tofu_mapof_get(fossil_tofu_mapof_t *map, fossil_tofu_t key) {
    for (size_t i = 0; i < map->size; i++) {
        if (fossil_tofu_equals(map->keys[i], key)) {
            return map->values[i];
        }
    }
    return fossil_tofu_create("ghost", "");
}

// Function to check if a key exists in the map
bool fossil_tofu_mapof_contains(fossil_tofu_mapof_t *map, fossil_tofu_t key) {
    for (size_t i = 0; i < map->size; i++) {
        if (fossil_tofu_equals(map->keys[i], key)) {
            return true;
        }
    }
    return false;
}

// Function to remove a key-value pair from the map
void fossil_tofu_mapof_remove(fossil_tofu_mapof_t *map, fossil_tofu_t key) {
    for (size_t i = 0; i < map->size; i++) {
        if (fossil_tofu_equals(map->keys[i], key)) {
            for (size_t j = i; j < map->size - 1; j++) {
                map->keys[j] = map->keys[j + 1];
                map->values[j] = map->values[j + 1];
            }
            map->size--;
            return;
        }
    }
}

// Function to get the size of the map
size_t fossil_tofu_mapof_size(fossil_tofu_mapof_t *map) {
    return map->size;
}

// Function to check if the map is empty
bool fossil_tofu_mapof_is_empty(fossil_tofu_mapof_t *map) {
    return map->size == 0;
}

// Function to clear the map
void fossil_tofu_mapof_clear(fossil_tofu_mapof_t *map) {
    map->size = 0;
}

// Function to destroy the map and free allocated memory
void fossil_tofu_mapof_erase(fossil_tofu_mapof_t *map) {
    fossil_tofu_free(map->keys);
    fossil_tofu_free(map->values);
}

// Utility function to print the map
void fossil_tofu_mapof_print(fossil_tofu_mapof_t *map) {
    for (size_t i = 0; i < map->size; i++) {
        printf("Key: ");
        fossil_tofu_print(map->keys[i]);
        printf("Value: ");
        fossil_tofu_print(map->values[i]);
    }
}
