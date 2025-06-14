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
#include <fossil/pizza/framework.h>

#include "fossil/tofu/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_SUITE(c_mapof_tofu_fixture);

FOSSIL_SETUP(c_mapof_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(c_mapof_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(c_test_mapof_create_and_destroy) {
    fossil_mapof_t* map = fossil_mapof_create_container("i32", "str");
    ASSUME_NOT_CNULL(map);
    ASSUME_ITS_EQUAL_CSTR(map->key_type, "i32");
    ASSUME_ITS_EQUAL_CSTR(map->value_type, "str");
    ASSUME_ITS_EQUAL_I32(fossil_mapof_size(map), 0);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST(c_test_mapof_create_default) {
    fossil_mapof_t* map = fossil_mapof_create_default();
    ASSUME_NOT_CNULL(map);
    ASSUME_ITS_EQUAL_CSTR(map->key_type, "any");
    ASSUME_ITS_EQUAL_CSTR(map->value_type, "any");
    fossil_mapof_destroy(map);
}

FOSSIL_TEST(c_test_mapof_insert_and_contains) {
    fossil_mapof_t* map = fossil_mapof_create_container("i32", "str");
    int32_t result = fossil_mapof_insert(map, "10", "hello");
    ASSUME_ITS_EQUAL_I32(result, FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_mapof_contains(map, "10"));
    ASSUME_ITS_EQUAL_I32(fossil_mapof_size(map), 1);
    fossil_tofu_t value = fossil_mapof_get(map, "10");
    ASSUME_ITS_EQUAL_CSTR(value.value.data, "hello");
    fossil_mapof_destroy(map);
}

FOSSIL_TEST(c_test_mapof_remove) {
    fossil_mapof_t* map = fossil_mapof_create_container("i32", "str");
    fossil_mapof_insert(map, "20", "foo");
    fossil_mapof_insert(map, "30", "bar");
    ASSUME_ITS_TRUE(fossil_mapof_contains(map, "20"));
    int32_t result = fossil_mapof_remove(map, "20");
    ASSUME_ITS_EQUAL_I32(result, FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_FALSE(fossil_mapof_contains(map, "20"));
    ASSUME_ITS_EQUAL_I32(fossil_mapof_size(map), 1);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST(c_test_mapof_copy_constructor) {
    fossil_mapof_t* map1 = fossil_mapof_create_container("i32", "str");
    fossil_mapof_insert(map1, "100", "alpha");
    fossil_mapof_insert(map1, "200", "beta");
    fossil_mapof_t* map2 = fossil_mapof_create_copy(map1);
    ASSUME_ITS_EQUAL_I32(fossil_mapof_size(map1), fossil_mapof_size(map2));
    ASSUME_ITS_TRUE(fossil_mapof_contains(map2, "100"));
    ASSUME_ITS_TRUE(fossil_mapof_contains(map2, "200"));
    fossil_tofu_t v1 = fossil_mapof_get(map2, "100");
    fossil_tofu_t v2 = fossil_mapof_get(map2, "200");
    ASSUME_ITS_EQUAL_CSTR(v1.value.data, "alpha");
    ASSUME_ITS_EQUAL_CSTR(v2.value.data, "beta");
    fossil_mapof_destroy(map1);
    fossil_mapof_destroy(map2);
}

FOSSIL_TEST(c_test_mapof_move_constructor) {
    fossil_mapof_t* map1 = fossil_mapof_create_container("i32", "str");
    fossil_mapof_insert(map1, "300", "foo");
    fossil_mapof_insert(map1, "400", "bar");
    size_t orig_size = fossil_mapof_size(map1);
    fossil_mapof_t* map2 = fossil_mapof_create_move(map1);
    ASSUME_ITS_EQUAL_I32(fossil_mapof_size(map2), orig_size);
    ASSUME_ITS_TRUE(fossil_mapof_contains(map2, "300"));
    ASSUME_ITS_TRUE(fossil_mapof_contains(map2, "400"));
    ASSUME_ITS_EQUAL_I32(fossil_mapof_size(map1), 0);
    fossil_mapof_destroy(map1);
    fossil_mapof_destroy(map2);
}

FOSSIL_TEST(c_test_mapof_is_empty_and_not_empty) {
    fossil_mapof_t* map = fossil_mapof_create_container("i32", "str");
    ASSUME_ITS_TRUE(fossil_mapof_is_empty(map));
    ASSUME_ITS_FALSE(fossil_mapof_not_empty(map));
    fossil_mapof_insert(map, "1", "one");
    ASSUME_ITS_FALSE(fossil_mapof_is_empty(map));
    ASSUME_ITS_TRUE(fossil_mapof_not_empty(map));
    fossil_mapof_destroy(map);
}

FOSSIL_TEST(c_test_mapof_insert_duplicate) {
    fossil_mapof_t* map = fossil_mapof_create_container("i32", "str");
    fossil_mapof_insert(map, "55", "foo");
    size_t size_before = fossil_mapof_size(map);
    fossil_mapof_insert(map, "55", "bar"); // Should update value, not add new entry
    size_t size_after = fossil_mapof_size(map);
    ASSUME_ITS_MORE_THAN_I32(size_after, size_before);
    fossil_tofu_t value = fossil_mapof_get(map, "55");
    ASSUME_ITS_EQUAL_CSTR(value.value.data, "bar");
    fossil_mapof_destroy(map);
}

FOSSIL_TEST(c_test_mapof_remove_nonexistent) {
    fossil_mapof_t* map = fossil_mapof_create_container("i32", "str");
    fossil_mapof_insert(map, "77", "baz");
    int32_t result = fossil_mapof_remove(map, "88");
    ASSUME_ITS_EQUAL_I32(result, FOSSIL_TOFU_FAILURE);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST(c_test_mapof_null_args) {
    ASSUME_ITS_EQUAL_I32(fossil_mapof_insert(NULL, "1", "a"), FOSSIL_TOFU_FAILURE);
    ASSUME_ITS_EQUAL_I32(fossil_mapof_insert((fossil_mapof_t*)1, NULL, "a"), FOSSIL_TOFU_FAILURE);
    ASSUME_ITS_EQUAL_I32(fossil_mapof_insert((fossil_mapof_t*)1, "1", NULL), FOSSIL_TOFU_FAILURE);
    ASSUME_ITS_EQUAL_I32(fossil_mapof_remove(NULL, "1"), FOSSIL_TOFU_FAILURE);
    ASSUME_ITS_EQUAL_I32(fossil_mapof_remove((fossil_mapof_t*)1, NULL), FOSSIL_TOFU_FAILURE);
    ASSUME_ITS_FALSE(fossil_mapof_contains(NULL, "1"));
    ASSUME_ITS_FALSE(fossil_mapof_contains((fossil_mapof_t*)1, NULL));
    ASSUME_ITS_EQUAL_I32(fossil_mapof_size(NULL), 0);
    ASSUME_ITS_FALSE(fossil_mapof_not_empty(NULL));
    ASSUME_ITS_TRUE(fossil_mapof_is_empty(NULL));
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_mapof_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(c_mapof_tofu_fixture, c_test_mapof_create_and_destroy);
    FOSSIL_TEST_ADD(c_mapof_tofu_fixture, c_test_mapof_create_default);
    FOSSIL_TEST_ADD(c_mapof_tofu_fixture, c_test_mapof_insert_and_contains);
    FOSSIL_TEST_ADD(c_mapof_tofu_fixture, c_test_mapof_remove);
    FOSSIL_TEST_ADD(c_mapof_tofu_fixture, c_test_mapof_copy_constructor);
    FOSSIL_TEST_ADD(c_mapof_tofu_fixture, c_test_mapof_move_constructor);
    FOSSIL_TEST_ADD(c_mapof_tofu_fixture, c_test_mapof_is_empty_and_not_empty);
    FOSSIL_TEST_ADD(c_mapof_tofu_fixture, c_test_mapof_insert_duplicate);
    FOSSIL_TEST_ADD(c_mapof_tofu_fixture, c_test_mapof_remove_nonexistent);
    FOSSIL_TEST_ADD(c_mapof_tofu_fixture, c_test_mapof_null_args);

    // Register the test group
    FOSSIL_TEST_REGISTER(c_mapof_tofu_fixture);
} // end of tests
