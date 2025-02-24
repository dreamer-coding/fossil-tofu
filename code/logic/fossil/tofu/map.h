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
#ifndef FOSSIL_TOFU_MAPOF_H
#define FOSSIL_TOFU_MAPOF_H

#include "tofu.h"

#ifdef __cplusplus
extern "C"
{
#endif

// *****************************************************************************
// Type definitions
// *****************************************************************************

// Node structure for the map (used for both ordered and unordered)
typedef struct fossil_map_node_t {
    char* key;
    fossil_tofu_t value;
    struct fossil_map_node_t* next;  // For chaining in unordered map (hash table) or linked list in ordered map
} fossil_map_node_t;

// Map structure
typedef struct fossil_map_t {
    fossil_map_node_t** buckets;  // For hash table (unordered)
    fossil_map_node_t* head;      // For linked list/tree (ordered)
    size_t bucket_count;          // Only used for unordered maps
    size_t size;
    char* map_type;  // "ordered" or "unordered"
    char* type;      // The type of data the map will store
} fossil_map_t;

// *****************************************************************************
// Function prototypes
// *****************************************************************************

/**
 * Create a new map with the specified type ("ordered" or "unordered").
 *
 * @param map_type The type of map to create.
 * @param type     The type of data the map will store.
 * @return         The created map.
 */
fossil_map_t* fossil_map_create_container(const char* type, const char* map_type);

/**
 * Create a new map with default values.
 * 
 * Time complexity: O(1)
 *
 * @return The created map.
 */
fossil_map_t* fossil_map_create_default(void);

/**
 * Create a new map by copying an existing map.
 * 
 * Time complexity: O(n)
 *
 * @param other The map to copy.
 * @return      The created map.
 */
fossil_map_t* fossil_map_create_copy(const fossil_map_t* other);

/**
 * Create a new map by moving an existing map.
 * 
 * Time complexity: O(1)
 *
 * @param other The map to move.
 * @return      The created map.
 */
fossil_map_t* fossil_map_create_move(fossil_map_t* other);

/**
 * Destroy a map and free allocated memory.
 *
 * @param map The map to destroy.
 */
void fossil_map_destroy(fossil_map_t* map);

/**
 * Insert a key-value pair into the map.
 *
 * @param map   The map to insert into.
 * @param key   The key to insert.
 * @param value The value associated with the key.
 * @return      Error code indicating success or failure.
 */
int fossil_map_insert(fossil_map_t* map, const char* key, fossil_tofu_t value);

/**
 * Remove a key from the map.
 *
 * @param map The map to remove the key from.
 * @param key The key to remove.
 * @return    Error code indicating success or failure.
 */
int fossil_map_erase(fossil_map_t* map, const char* key);

/**
 * Get a value associated with a key.
 *
 * @param map The map to search.
 * @param key The key to look up.
 * @return    The value associated with the key or NULL if not found.
 */
fossil_tofu_t* fossil_map_get(const fossil_map_t* map, const char* key);

/**
 * Check if a key exists in the map.
 *
 * @param map The map to search.
 * @param key The key to check.
 * @return    True if the key exists, false otherwise.
 */
bool fossil_map_contains(const fossil_map_t* map, const char* key);

/**
 * Get the size of the map.
 *
 * @param map The map to check.
 * @return    The number of elements in the map.
 */
size_t fossil_map_size(const fossil_map_t* map);

/**
 * Check if the map is not a null pointer.
 *
 * @param map The map to check.
 * @return    True if the map is not a null pointer, false otherwise.
 */
bool fossil_map_not_cnullptr(const fossil_map_t* map);

/**
 * Check if the map is a null pointer.
 *
 * @param map The map to check.
 * @return    True if the map is a null pointer, false otherwise.
 */
bool fossil_map_is_cnullptr(const fossil_map_t* map);

/**
 * Check if the map is not empty.
 *
 * @param map The map to check.
 * @return    True if the map contains at least one element, false otherwise.
 */
bool fossil_map_not_empty(const fossil_map_t* map);

/**
 * Check if the map is empty.
 *
 * @param map The map to check.
 * @return    True if the map contains no elements, false otherwise.
 */
bool fossil_map_is_empty(const fossil_map_t* map);

#ifdef __cplusplus
}
#include <stdexcept>

namespace fossil {

    namespace tofu {
        
        class Map {
        public:
            /**
             * Create a new map with the specified type ("ordered" or "unordered").
             *
             * @param type     The type of data the map will store.
             * @param map_type The type of map to create.
             */
            Map(const std::string& type, const std::string& map_type) : map_(fossil_map_create_container(type.c_str(), map_type.c_str())) {
                if (map_ == nullptr) {
                    throw std::runtime_error("Failed to create map");
                }
            }

            /**
             * Create a new map with default values.
             */
            Map() : map_(fossil_map_create_default()) {
                if (map_ == nullptr) {
                    throw std::runtime_error("Failed to create map");
                }
            }

            /**
             * Create a new map by copying an existing map.
             *
             * @param other The map to copy.
             */
            Map(const Map& other) : map_(fossil_map_create_copy(other.map_)) {
                if (map_ == nullptr) {
                    throw std::runtime_error("Failed to create map");
                }
            }

            /**
             * Create a new map by moving an existing map.
             *
             * @param other The map to move.
             */
            Map(Map&& other) : map_(fossil_map_create_move(other.map_)) {
                other.map_ = nullptr;
                if (map_ == nullptr) {
                    throw std::runtime_error("Failed to create map");
                }
            }

            /**
             * Destroy the map and free allocated memory.
             */
            ~Map() {
                fossil_map_destroy(map_);
            }

            /**
             * Copy assignment operator.
             *
             * @param other The map to copy.
             * @return      The copied map.
             */
            void insert(const std::string& key, const fossil_tofu_t& value) {
                if (fossil_map_insert(map_, key.c_str(), value) != 0) {
                    throw std::runtime_error("Failed to insert key-value pair");
                }
            }

            /**
             * Move assignment operator.
             *
             * @param other The map to move.
             * @return      The moved map.
             */
            void erase(const std::string& key) {
                if (fossil_map_erase(map_, key.c_str()) != 0) {
                    throw std::runtime_error("Failed to erase key");
                }
            }

            /**
             * Get a value associated with a key.
             *
             * @param key The key to look up.
             * @return    The value associated with the key or NULL if not found.
             */
            fossil_tofu_t* get(const std::string& key) const {
                return fossil_map_get(map_, key.c_str());
            }

            /**
             * Check if a key exists in the map.
             *
             * @param key The key to check.
             * @return    True if the key exists, false otherwise.
             */
            bool contains(const std::string& key) const {
                return fossil_map_contains(map_, key.c_str());
            }

            /**
             * Get the size of the map.
             *
             * @return The number of elements in the map.
             */
            size_t size() const {
                return fossil_map_size(map_);
            }

            /**
             * Check if the map is not a null pointer.
             *
             * @return True if the map is not a null pointer, false otherwise.
             */
            bool not_cnullptr() const {
                return fossil_map_not_cnullptr(map_);
            }

            /**
             * Check if the map is a null pointer.
             *
             * @return True if the map is a null pointer, false otherwise.
             */
            bool is_cnullptr() const {
                return fossil_map_is_cnullptr(map_);
            }

            /**
             * Check if the map is not empty.
             *
             * @return True if the map contains at least one element, false otherwise.
             */
            bool not_empty() const {
                return fossil_map_not_empty(map_);
            }

            /**
             * Check if the map is empty.
             *
             * @return True if the map contains no elements, false otherwise.
             */
            bool is_empty() const {
                return fossil_map_is_empty(map_);
            }

        private:
            fossil_map_t* map_;
        };

    }

} // namespace fossil

#endif

#endif /* FOSSIL_TOFU_FRAMEWORK_H */
