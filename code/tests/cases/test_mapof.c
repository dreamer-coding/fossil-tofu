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
#include <fossil/test/framework.h>

#include "fossil/tofu/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_SUITE(c_map_fixture);

FOSSIL_SETUP(c_map_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(c_map_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(test_fossil_map_create) {
    fossil_map_t map = fossil_map_create("int");
    ASSUME_ITS_EQUAL_I32(0, fossil_map_size(&map));
    fossil_map_destroy(&map);
}

FOSSIL_TEST_CASE(test_fossil_map_add_and_get) {
    fossil_map_t map = fossil_map_create("int");
    fossil_tofu_t key = fossil_tofu_create("int", "1");
    fossil_tofu_t value = fossil_tofu_create("int", "100");
    fossil_map_add(&map, key, value);
    fossil_tofu_t retrieved = fossil_map_get(&map, key);
    ASSUME_ITS_EQUAL_I32(100, retrieved.value.int_val);
    fossil_map_destroy(&map);
}

FOSSIL_TEST_CASE(test_fossil_map_contains) {
    fossil_map_t map = fossil_map_create("int");
    fossil_tofu_t key = fossil_tofu_create("int", "1");
    fossil_tofu_t value = fossil_tofu_create("int", "100");
    fossil_map_add(&map, key, value);
    ASSUME_ITS_TRUE(fossil_map_contains(&map, key));
    fossil_map_destroy(&map);
}

FOSSIL_TEST_CASE(test_fossil_map_remove) {
    fossil_map_t map = fossil_map_create("int");
    fossil_tofu_t key = fossil_tofu_create("int", "1");
    fossil_tofu_t value = fossil_tofu_create("int", "100");
    fossil_map_add(&map, key, value);
    fossil_map_remove(&map, key);
    ASSUME_ITS_FALSE(fossil_map_contains(&map, key));
    fossil_map_destroy(&map);
}

FOSSIL_TEST_CASE(test_fossil_map_size) {
    fossil_map_t map = fossil_map_create("int");
    fossil_tofu_t key1 = fossil_tofu_create("int", "1");
    fossil_tofu_t value1 = fossil_tofu_create("int", "100");
    fossil_tofu_t key2 = fossil_tofu_create("int", "2");
    fossil_tofu_t value2 = fossil_tofu_create("int", "200");
    fossil_map_add(&map, key1, value1);
    fossil_map_add(&map, key2, value2);
    ASSUME_ITS_EQUAL_I32(2, fossil_map_size(&map));
    fossil_map_destroy(&map);
}

FOSSIL_TEST_CASE(test_fossil_map_is_empty) {
    fossil_map_t map = fossil_map_create("int");
    ASSUME_ITS_TRUE(fossil_map_is_empty(&map));
    fossil_tofu_t key = fossil_tofu_create("int", "1");
    fossil_tofu_t value = fossil_tofu_create("int", "100");
    fossil_map_add(&map, key, value);
    ASSUME_ITS_FALSE(fossil_map_is_empty(&map));
    fossil_map_destroy(&map);
}

FOSSIL_TEST_CASE(test_fossil_map_clear) {
    fossil_map_t map = fossil_map_create("int");
    fossil_tofu_t key = fossil_tofu_create("int", "1");
    fossil_tofu_t value = fossil_tofu_create("int", "100");
    fossil_map_add(&map, key, value);
    fossil_map_clear(&map);
    ASSUME_ITS_EQUAL_I32(0, fossil_map_size(&map));
    ASSUME_ITS_TRUE(fossil_map_is_empty(&map));
    fossil_map_destroy(&map);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_mapof_structure_tests) {    
    // Generic ToFu MapOf Fixture
    FOSSIL_TEST_ADD(c_map_fixture, test_fossil_map_create);
    FOSSIL_TEST_ADD(c_map_fixture, test_fossil_map_add_and_get);
    FOSSIL_TEST_ADD(c_map_fixture, test_fossil_map_contains);
    FOSSIL_TEST_ADD(c_map_fixture, test_fossil_map_remove);
    FOSSIL_TEST_ADD(c_map_fixture, test_fossil_map_size);
    FOSSIL_TEST_ADD(c_map_fixture, test_fossil_map_is_empty);
    FOSSIL_TEST_ADD(c_map_fixture, test_fossil_map_clear);

    FOSSIL_TEST_REGISTER(c_map_fixture);
} // end of tests
