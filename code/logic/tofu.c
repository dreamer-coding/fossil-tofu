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
#include "fossil/tofu/tofu.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <wchar.h>
#include <time.h>

// Lookup table for valid strings corresponding to each tofu type.
static char *_TOFU_TYPE_ID[] = {
    "i8",
    "i16",
    "i32",
    "i64",
    "u8",
    "u16",
    "u32",
    "u64",
    "hex",
    "octal",
    "float",
    "double",
    "wstr",
    "cstr",
    "cchar",
    "wchar",
    "bool",
    "size",
    "any"
};

static char *_TOFU_TYPE_NAME[] = {
    "Signed 8-bit Integer",
    "Signed 16-bit Integer",
    "Signed 32-bit Integer",
    "Signed 64-bit Integer",
    "Unsigned 8-bit Integer",
    "Unsigned 16-bit Integer",
    "Unsigned 32-bit Integer",
    "Unsigned 64-bit Integer",
    "Hexadecimal",
    "Octal",
    "Float",
    "Double",
    "Wide String",
    "C String",
    "Byte",
    "Char",
    "Wide Char",
    "Boolean",
    "Size",
    "Any"
};

static char *_TOFU_TYPE_INFO[] = {
    "An 8-bit signed integer value",
    "A 16-bit signed integer value",
    "A 32-bit signed integer value",
    "A 64-bit signed integer value",
    "An 8-bit unsigned integer value",
    "A 16-bit unsigned integer value",
    "A 32-bit unsigned integer value",
    "A 64-bit unsigned integer value",
    "A hexadecimal value",
    "An octal value",
    "A single-precision floating point value",
    "A double-precision floating point value",
    "A wide string value",
    "A C string value",
    "A byte value",
    "A character value",
    "A wide character value",
    "A boolean value",
    "A size value",
    "A generic value"
};

fossil_tofu_type_t fossil_tofu_validate_type(const char *type_str) {
    if (type_str == NULL) return FOSSIL_TOFU_TYPE_ANY;

    for (size_t i = 0; i < sizeof(_TOFU_TYPE_ID) / sizeof(_TOFU_TYPE_ID[0]); i++) {
        if (strcmp(type_str, _TOFU_TYPE_ID[i]) == 0) {
            return (fossil_tofu_type_t)i;
        }
    }

    return FOSSIL_TOFU_TYPE_ANY;
}

// *****************************************************************************
// Managment functions
// *****************************************************************************

fossil_tofu_t fossil_tofu_create(char* type, char* value) {
    fossil_tofu_t tofu;
    fossil_tofu_type_t type_enum = fossil_tofu_validate_type(type);
    if (type_enum > FOSSIL_TOFU_TYPE_ANY || type_enum < 0) {
        fprintf(stderr, "Invalid type: %s\n", type);
        tofu.type = FOSSIL_TOFU_TYPE_ANY;
    } else {
        tofu.type = type_enum;
    }

    tofu.value.data = fossil_tofu_strdup(value);
    tofu.value.mutable = true;

    tofu.attribute.name = fossil_tofu_strdup(_TOFU_TYPE_NAME[tofu.type]);
    tofu.attribute.description = fossil_tofu_strdup(_TOFU_TYPE_INFO[tofu.type]);
    tofu.attribute.id = fossil_tofu_strdup(_TOFU_TYPE_ID[tofu.type]);

    return tofu;
}

void fossil_tofu_destroy(fossil_tofu_t *tofu) {
    if (tofu == NULL) return;
    fossil_tofu_free(tofu->value.data);
    fossil_tofu_free(tofu->attribute.name);
    fossil_tofu_free(tofu->attribute.description);
    fossil_tofu_free(tofu->attribute.id);
}

// *****************************************************************************
// Utility functions
// *****************************************************************************

int fossil_tofu_set_value(fossil_tofu_t *tofu, char *value) {
    if (tofu == NULL || !tofu->value.mutable) return FOSSIL_TOFU_FAILURE;

    fossil_tofu_free(tofu->value.data);
    tofu->value.data = fossil_tofu_strdup(value);
    return FOSSIL_TOFU_SUCCESS;
}

char* fossil_tofu_get_value(const fossil_tofu_t *tofu) {
    return tofu != NULL ? tofu->value.data : NULL;
}

bool fossil_tofu_is_mutable(const fossil_tofu_t *tofu) {
    return tofu != NULL && tofu->value.mutable;
}

int fossil_tofu_set_mutable(fossil_tofu_t *tofu, bool mutable) {
    if (tofu == NULL) return FOSSIL_TOFU_FAILURE;

    tofu->value.mutable = mutable;
    return FOSSIL_TOFU_SUCCESS;
}

fossil_tofu_type_t fossil_tofu_get_type(const fossil_tofu_t *tofu) {
    return tofu != NULL ? tofu->type : FOSSIL_TOFU_TYPE_ANY;
}

const char* fossil_tofu_type_name(fossil_tofu_type_t type) {
    if (type >= 0 && type < sizeof(_TOFU_TYPE_NAME) / sizeof(_TOFU_TYPE_NAME[0])) {
        return _TOFU_TYPE_NAME[type];
    }
    return "Unknown Type";
}

const char* fossil_tofu_type_info(fossil_tofu_type_t type) {
    if (type >= 0 && type < sizeof(_TOFU_TYPE_NAME) / sizeof(_TOFU_TYPE_NAME[0])) {
        return _TOFU_TYPE_NAME[type];
    }
    return "No type info available.";
}

void fossil_tofu_display(const fossil_tofu_t *tofu) {
    if (tofu == NULL) return;

    printf("Type: %s\n", fossil_tofu_type_name(tofu->type));
    printf("Value: %s\n", tofu->value.data);
    printf("Attribute Name: %s\n", tofu->attribute.name);
    printf("Description: %s\n", tofu->attribute.description);
    printf("ID: %s\n", tofu->attribute.id);
}

int fossil_tofu_set_attribute(fossil_tofu_t *tofu, const char *name, const char *description, const char *id) {
    if (tofu == NULL) return FOSSIL_TOFU_FAILURE;

    fossil_tofu_free(tofu->attribute.name);
    fossil_tofu_free(tofu->attribute.description);
    fossil_tofu_free(tofu->attribute.id);

    tofu->attribute.name = fossil_tofu_strdup(name);
    tofu->attribute.description = fossil_tofu_strdup(description);
    tofu->attribute.id = fossil_tofu_strdup(id);

    return FOSSIL_TOFU_SUCCESS;
}

const fossil_tofu_attribute_t* fossil_tofu_get_attribute(const fossil_tofu_t *tofu) {
    return tofu != NULL ? &tofu->attribute : NULL;
}

bool fossil_tofu_equals(const fossil_tofu_t *tofu1, const fossil_tofu_t *tofu2) {
    if (tofu1 == NULL || tofu2 == NULL) return false;

    return tofu1->type == tofu2->type &&
           strcmp(tofu1->value.data, tofu2->value.data) == 0;
}

int fossil_tofu_copy(fossil_tofu_t *dest, const fossil_tofu_t *src) {
    if (dest == NULL || src == NULL) return FOSSIL_TOFU_FAILURE;

    dest->type = src->type;
    dest->value.data = fossil_tofu_strdup(src->value.data);
    dest->value.mutable = src->value.mutable;

    dest->attribute.name = fossil_tofu_strdup(src->attribute.name);
    dest->attribute.description = fossil_tofu_strdup(src->attribute.description);
    dest->attribute.id = fossil_tofu_strdup(src->attribute.id);

    return FOSSIL_TOFU_SUCCESS;
}

// *****************************************************************************
// Algorithm functions
// *****************************************************************************

int fossil_tofu_algorithm_compare(const fossil_tofu_t *tofu1, const fossil_tofu_t *tofu2) {
    if (tofu1 == NULL || tofu2 == NULL) return 0;

    if (tofu1->type != tofu2->type) {
        return (int)tofu1->type - (int)tofu2->type;
    }

    return strcmp(tofu1->value.data, tofu2->value.data);
}

int fossil_tofu_algorithm_search(const fossil_tofu_t *array, size_t size, const fossil_tofu_t *tofu) {
    if (array == NULL || tofu == NULL) return -1;

    for (size_t i = 0; i < size; i++) {
        if (fossil_tofu_equals(&array[i], tofu)) {
            return (int)i;
        }
    }

    return -1;
}

int fossil_tofu_algorithm_sort(fossil_tofu_t *array, size_t size, bool ascending) {
    if (array == NULL || size == 0) return FOSSIL_TOFU_FAILURE;

    fossil_tofu_t temp;
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = i + 1; j < size; j++) {
            int cmp = fossil_tofu_algorithm_compare(&array[i], &array[j]);
            if ((ascending && cmp > 0) || (!ascending && cmp < 0)) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    return FOSSIL_TOFU_SUCCESS;
}

int fossil_tofu_algorithm_transform(fossil_tofu_t *array, size_t size, int (*transform_fn)(fossil_tofu_t *tofu)) {
    if (array == NULL || size == 0) return FOSSIL_TOFU_FAILURE;

    for (size_t i = 0; i < size; i++) {
        if (transform_fn(&array[i]) != FOSSIL_TOFU_SUCCESS) {
            return FOSSIL_TOFU_FAILURE;
        }
    }

    return FOSSIL_TOFU_SUCCESS;
}

void* fossil_tofu_algorithm_accumulate(const fossil_tofu_t *array, size_t size, void* (*accumulate_fn)(const fossil_tofu_t *tofu, void *accum), void* initial) {
    if (array == NULL || size == 0) return NULL;

    void *accum = initial;
    for (size_t i = 0; i < size; i++) {
        accum = accumulate_fn(&array[i], accum);
    }

    return accum;
}

int fossil_tofu_algorithm_filter(const fossil_tofu_t *array, size_t size, bool (*filter_fn)(const fossil_tofu_t *tofu), fossil_tofu_t **result, size_t *result_size) {
    if (array == NULL || size == 0) return FOSSIL_TOFU_FAILURE;

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (filter_fn(&array[i])) {
            count++;
        }
    }

    if (count == 0) {
        *result = NULL;
        *result_size = 0;
        return FOSSIL_TOFU_SUCCESS;
    }

    *result = fossil_tofu_alloc(count * sizeof(fossil_tofu_t));
    if (*result == NULL) {
        return FOSSIL_TOFU_FAILURE;
    }

    size_t j = 0;
    for (size_t i = 0; i < size; i++) {
        if (filter_fn(&array[i])) {
            fossil_tofu_copy(&(*result)[j], &array[i]);
            j++;
        }
    }

    *result_size = count;
    return FOSSIL_TOFU_SUCCESS;
}

int fossil_tofu_algorithm_reverse(fossil_tofu_t *array, size_t size) {
    if (array == NULL || size == 0) return FOSSIL_TOFU_FAILURE;

    fossil_tofu_t temp;
    for (size_t i = 0; i < size / 2; i++) {
        temp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = temp;
    }

    return FOSSIL_TOFU_SUCCESS;
}

fossil_tofu_t* fossil_tofu_algorithm_min(const fossil_tofu_t *array, size_t size, int (*compare_fn)(const fossil_tofu_t *tofu1, const fossil_tofu_t *tofu2)) {
    if (array == NULL || size == 0) return NULL;

    fossil_tofu_t *min = (fossil_tofu_t*)&array[0];
    for (size_t i = 1; i < size; i++) {
        if (compare_fn(&array[i], min) < 0) {
            min = (fossil_tofu_t*)&array[i];
        }
    }

    return min;
}

fossil_tofu_t* fossil_tofu_algorithm_max(const fossil_tofu_t *array, size_t size, int (*compare_fn)(const fossil_tofu_t *tofu1, const fossil_tofu_t *tofu2)) {
    if (array == NULL || size == 0) return NULL;

    fossil_tofu_t *max = (fossil_tofu_t*)&array[0];
    for (size_t i = 1; i < size; i++) {
        if (compare_fn(&array[i], max) > 0) {
            max = (fossil_tofu_t*)&array[i];
        }
    }

    return max;
}

void* fossil_tofu_algorithm_sum(const fossil_tofu_t *array, size_t size, void* (*sum_fn)(const fossil_tofu_t *tofu)) {
    if (array == NULL || size == 0) return NULL;

    void *sum = sum_fn(&array[0]);
    for (size_t i = 1; i < size; i++) {
        sum = sum_fn(&array[i]);
    }

    return sum;
}

// *****************************************************************************
// Memory management functions
// *****************************************************************************

tofu_memory_t fossil_tofu_alloc(size_t size) {
    if (size == 0) {
        fprintf(stderr, "Error: Cannot allocate zero bytes\n");
        return NULL;
    }

    tofu_memory_t ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }
    return ptr;
}

tofu_memory_t fossil_tofu_realloc(tofu_memory_t ptr, size_t size) {
    if (size == 0) {
        fprintf(stderr, "Error: Cannot reallocate to zero bytes\n");
        fossil_tofu_free(ptr);
        return NULL;
    }

    tofu_memory_t new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        fprintf(stderr, "Error: Memory reallocation failed\n");
        return NULL; // Return NULL if reallocation fails
    }

    return new_ptr;
}

void fossil_tofu_free(tofu_memory_t ptr) {
    if (ptr) {
        free(ptr);
    } else {
        fprintf(stderr, "Warning: Attempted to free a NULL pointer\n");
    }
} // end of fun

char* fossil_tofu_strdup(const char* str) {
    if (!str) {
        fprintf(stderr, "Error: NULL pointer passed to fossil_tofu_strdup\n");
        return NULL; // Handle NULL pointer gracefully
    }

    size_t len = 0;
    while (str[len] != '\0') len++; // Calculate the length of the string

    char* dup = fossil_tofu_alloc((len + 1) * sizeof(char)); // Allocate memory for the duplicate string
    if (!dup) {
        fprintf(stderr, "Error: Memory allocation failed in fossil_tofu_strdup\n");
        return NULL; // Return NULL if allocation fails
    }

    for (size_t i = 0; i < len; i++) {
        dup[i] = str[i]; // Copy each character from the original string to the duplicate
    }
    dup[len] = '\0'; // Add null terminator to the end of the duplicate string

    return dup;
} // end of fun
