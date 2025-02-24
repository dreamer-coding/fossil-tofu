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
#include "fossil/tofu/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Hash function for the map keys.
 *
 * @param key The key to hash.
 * @return    The hash value of the key.
 */
size_t fossil_map_hash(const char* key) {
    size_t hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }

    return hash;
}

// *****************************************************************************
// Function prototypes
// *****************************************************************************

fossil_map_t* fossil_map_create_container(const char* type, const char* map_type) {
    fossil_map_t* map = (fossil_map_t*)fossil_tofu_alloc(sizeof(fossil_map_t));
    if (map == NULL) {
        return NULL;
    }
    map->map_type = map_type;
    map->type = type;
    map->size = 0;
    if (strcmp(map_type, "unordered") == 0) {
        map->bucket_count = 10;
        map->buckets = (fossil_map_node_t**)fossil_tofu_alloc(map->bucket_count * sizeof(fossil_map_node_t*));
        if (map->buckets == NULL) {
            fossil_tofu_free(map);
            return NULL;
        }
        for (size_t i = 0; i < map->bucket_count; i++) {
            map->buckets[i] = NULL;
        }
    } else if (strcmp(map_type, "ordered") == 0) {
        map->head = NULL;
    } else {
        fossil_tofu_free(map);
        return NULL;
    }
    return map;
}

fossil_map_t* fossil_map_create_default(void) {
    return fossil_map_create_container("any", "unordered");
}

fossil_map_t* fossil_map_create_copy(const fossil_map_t* other) {
    fossil_map_t* map = (fossil_map_t*)fossil_tofu_alloc(sizeof(fossil_map_t));
    if (map == NULL) {
        return NULL;
    }
    map->map_type = other->map_type;
    map->type = other->type;
    map->size = other->size;
    if (strcmp(other->map_type, "unordered") == 0) {
        map->bucket_count = other->bucket_count;
        map->buckets = (fossil_map_node_t**)fossil_tofu_alloc(map->bucket_count * sizeof(fossil_map_node_t*));
        if (map->buckets == NULL) {
            fossil_tofu_free(map);
            return NULL;
        }
        for (size_t i = 0; i < map->bucket_count; i++) {
            map->buckets[i] = NULL;
            fossil_map_node_t* current = other->buckets[i];
            while (current != NULL) {
                fossil_map_node_t* node = (fossil_map_node_t*)fossil_tofu_alloc(sizeof(fossil_map_node_t));
                if (node == NULL) {
                    fossil_map_destroy(map);
                    return NULL;
                }
                node->key = fossil_tofu_strdup(current->key);
                if (node->key == NULL) {
                    fossil_tofu_free(node);
                    fossil_map_destroy(map);
                    return NULL;
                }
                node->value = current->value;
                node->next = map->buckets[i];
                map->buckets[i] = node;
                current = current->next;
            }
        }
    } else if (strcmp(other->map_type, "ordered") == 0) {
        map->head = NULL;
        fossil_map_node_t* current = other->head;
        while (current != NULL) {
            fossil_map_node_t* node = (fossil_map_node_t*)fossil_tofu_alloc(sizeof(fossil_map_node_t));
            if (node == NULL) {
                fossil_map_destroy(map);
                return NULL;
            }
            node->key = fossil_tofu_strdup(current->key);
            if (node->key == NULL) {
                fossil_tofu_free(node);
                fossil_map_destroy(map);
                return NULL;
            }
            node->value = current->value;
            node->next = map->head;
            map->head = node;
            current = current->next;
        }
    } else {
        fossil_tofu_free(map);
        return NULL;
    }
    return map;
}

fossil_map_t* fossil_map_create_move(fossil_map_t* other) {
    fossil_map_t* map = (fossil_map_t*)fossil_tofu_alloc(sizeof(fossil_map_t));
    if (map == NULL) {
        return NULL;
    }
    map->map_type = other->map_type;
    map->type = other->type;
    map->size = other->size;
    if (strcmp(other->map_type, "unordered") == 0) {
        map->bucket_count = other->bucket_count;
        map->buckets = other->buckets;
        other->buckets = NULL;
    } else if (strcmp(other->map_type, "ordered") == 0) {
        map->head = other->head;
        other->head = NULL;
    } else {
        fossil_tofu_free(map);
        return NULL;
    }
    fossil_tofu_free(other);
    return map;
}

void fossil_map_destroy(fossil_map_t* map) {
    if (map == NULL) {
        return;
    }
    if (strcmp(map->map_type, "unordered") == 0) {
        for (size_t i = 0; i < map->bucket_count; i++) {
            fossil_map_node_t* current = map->buckets[i];
            while (current != NULL) {
                fossil_map_node_t* temp = current;
                current = current->next;
                fossil_tofu_free(temp->key);
                fossil_tofu_free(temp);
            }
        }
        fossil_tofu_free(map->buckets);
    } else if (strcmp(map->map_type, "ordered") == 0) {
        fossil_map_node_t* current = map->head;
        while (current != NULL) {
            fossil_map_node_t* temp = current;
            current = current->next;
            fossil_tofu_free(temp->key);
            fossil_tofu_free(temp);
        }
    }
    fossil_tofu_free(map);
}

int fossil_map_insert(fossil_map_t* map, const char* key, fossil_tofu_t value) {
    if (map == NULL || key == NULL) {
        return -1;
    }
    if (strcmp(map->map_type, "unordered") == 0) {
        size_t index = fossil_map_hash(key) % map->bucket_count;
        fossil_map_node_t* current = map->buckets[index];
        while (current != NULL) {
            if (strcmp(current->key, key) == 0) {
                return -1;  // Key already exists
            }
            current = current->next;
        }
        fossil_map_node_t* node = (fossil_map_node_t*)fossil_tofu_alloc(sizeof(fossil_map_node_t));
        if (node == NULL) {
            return -1;
        }
        node->key = fossil_tofu_strdup(key);
        if (node->key == NULL) {
            fossil_tofu_free(node);
            return -1;
        }
        node->value = value;
        node->next = map->buckets[index];
        map->buckets[index] = node;
    } else if (strcmp(map->map_type, "ordered") == 0) {
        fossil_map_node_t* current = map->head;
        while (current != NULL) {
            if (strcmp(current->key, key) == 0) {
                return -1;  // Key already exists
            }
            current = current->next;
        }
        fossil_map_node_t* node = (fossil_map_node_t*)fossil_tofu_alloc(sizeof(fossil_map_node_t));
        if (node == NULL) {
            return -1;
        }
        node->key = fossil_tofu_strdup(key);
        if (node->key == NULL) {
            fossil_tofu_free(node);
            return -1;
        }
        node->value = value;
        node->next = map->head;
        map->head = node;
    } else {
        return -1;
    }
    map->size++;
    return 0;
}

int fossil_map_erase(fossil_map_t* map, const char* key) {
    if (map == NULL || key == NULL) {
        return -1;
    }
    if (strcmp(map->map_type, "unordered") == 0) {
        size_t index = fossil_map_hash(key) % map->bucket_count;
        fossil_map_node_t** current = &map->buckets[index];
        while (*current != NULL) {
            if (strcmp((*current)->key, key) == 0) {
                fossil_map_node_t* temp = *current;
                *current = (*current)->next;
                fossil_tofu_free(temp->key);
                fossil_tofu_free(temp);
                map->size--;
                return 0;
            }
            current = &(*current)->next;
        }
    } else if (strcmp(map->map_type, "ordered") == 0) {
        fossil_map_node_t** current = &map->head;
        while (*current != NULL) {
            if (strcmp((*current)->key, key) == 0) {
                fossil_map_node_t* temp = *current;
                *current = (*current)->next;
                fossil_tofu_free(temp->key);
                fossil_tofu_free(temp);
                map->size--;
                return 0;
            }
            current = &(*current)->next;
        }
    } else {
        return -1;
    }
    return -1;
}

fossil_tofu_t* fossil_map_get(const fossil_map_t* map, const char* key) {
    if (map == NULL || key == NULL) {
        return NULL;
    }
    if (strcmp(map->map_type, "unordered") == 0) {
        size_t index = fossil_map_hash(key) % map->bucket_count;
        fossil_map_node_t* current = map->buckets[index];
        while (current != NULL) {
            if (strcmp(current->key, key) == 0) {
                return &current->value;
            }
            current = current->next;
        }
    } else if (strcmp(map->map_type, "ordered") == 0) {
        fossil_map_node_t* current = map->head;
        while (current != NULL) {
            if (strcmp(current->key, key) == 0) {
                return &current->value;
            }
            current = current->next;
        }
    }
    return NULL;
}

bool fossil_map_contains(const fossil_map_t* map, const char* key) {
    return fossil_map_get(map, key) != NULL;
}

size_t fossil_map_size(const fossil_map_t* map) {
    return map == NULL ? 0 : map->size;
}

bool fossil_map_not_cnullptr(const fossil_map_t* map) {
    return map != NULL;
}

bool fossil_map_is_cnullptr(const fossil_map_t* map) {
    return map == NULL;
}

bool fossil_map_not_empty(const fossil_map_t* map) {
    return map != NULL && map->size > 0;
}

bool fossil_map_is_empty(const fossil_map_t* map) {
    return map == NULL || map->size == 0;
}
