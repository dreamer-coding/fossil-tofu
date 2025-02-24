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

FOSSIL_TEST_SUITE(c_map_tofu_fixture);

FOSSIL_SETUP(c_map_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(c_map_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_map_create_destroy) {
    fossil_map_t* map = fossil_map_create_container("ordered", "i32");
    ASSUME_ITS_TRUE(map != NULL);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(c_test_map_create_default) {
    fossil_map_t* map = fossil_map_create_default();
    ASSUME_ITS_TRUE(map != NULL);
    ASSUME_ITS_TRUE(fossil_map_size(map) == 0);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(c_test_map_create_copy) {
    fossil_map_t* map1 = fossil_map_create_container("ordered", "i32");
    fossil_tofu_t tofu = fossil_tofu_create("i32", "42");
    fossil_map_insert(map1, "key1", tofu);
    fossil_map_t* map2 = fossil_map_create_copy(map1);
    ASSUME_ITS_TRUE(map2 != NULL);
    ASSUME_ITS_TRUE(fossil_map_size(map2) == 1);
    fossil_tofu_t* value = fossil_map_get(map2, "key1");
    ASSUME_ITS_TRUE(value != NULL);
    ASSUME_ITS_EQUAL_CSTR(value->value.data, "42");
    fossil_map_destroy(map1);
    fossil_map_destroy(map2);
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_map_create_move) {
    fossil_map_t* map1 = fossil_map_create_container("ordered", "i32");
    fossil_tofu_t tofu = fossil_tofu_create("i32", "42");
    fossil_map_insert(map1, "key1", tofu);
    fossil_map_t* map2 = fossil_map_create_move(map1);
    ASSUME_ITS_TRUE(map2 != NULL);
    ASSUME_ITS_TRUE(fossil_map_size(map2) == 1);
    ASSUME_ITS_TRUE(fossil_map_size(map1) == 0);
    fossil_tofu_t* value = fossil_map_get(map2, "key1");
    ASSUME_ITS_TRUE(value != NULL);
    ASSUME_ITS_EQUAL_CSTR(value->value.data, "42");
    fossil_map_destroy(map2);
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_map_insert_get) {
    fossil_map_t* map = fossil_map_create_container("ordered", "i32");
    fossil_tofu_t tofu = fossil_tofu_create("i32", "42");
    ASSUME_ITS_TRUE(fossil_map_insert(map, "key1", tofu) == FOSSIL_TOFU_SUCCESS);
    fossil_tofu_t* value = fossil_map_get(map, "key1");
    ASSUME_ITS_TRUE(value != NULL);
    ASSUME_ITS_EQUAL_CSTR(value->value.data, "42");
    fossil_map_destroy(map);
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_map_erase) {
    fossil_map_t* map = fossil_map_create_container("ordered", "i32");
    fossil_tofu_t tofu = fossil_tofu_create("i32", "42");
    fossil_map_insert(map, "key1", tofu);
    ASSUME_ITS_TRUE(fossil_map_erase(map, "key1") == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_map_get(map, "key1") == NULL);
    fossil_map_destroy(map);
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_map_contains) {
    fossil_map_t* map = fossil_map_create_container("ordered", "i32");
    fossil_tofu_t tofu = fossil_tofu_create("i32", "42");
    fossil_map_insert(map, "key1", tofu);
    ASSUME_ITS_TRUE(fossil_map_contains(map, "key1") == true);
    ASSUME_ITS_TRUE(fossil_map_contains(map, "key2") == false);
    fossil_map_destroy(map);
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_map_size) {
    fossil_map_t* map = fossil_map_create_container("ordered", "i32");
    fossil_tofu_t tofu1 = fossil_tofu_create("i32", "42");
    fossil_tofu_t tofu2 = fossil_tofu_create("i32", "84");
    fossil_map_insert(map, "key1", tofu1);
    fossil_map_insert(map, "key2", tofu2);
    ASSUME_ITS_TRUE(fossil_map_size(map) == 2);
    fossil_map_destroy(map);
    fossil_tofu_destroy(&tofu1);
    fossil_tofu_destroy(&tofu2);
}

FOSSIL_TEST_CASE(c_test_map_not_empty) {
    fossil_map_t* map = fossil_map_create_container("ordered", "i32");
    fossil_tofu_t tofu = fossil_tofu_create("i32", "42");
    fossil_map_insert(map, "key1", tofu);
    ASSUME_ITS_TRUE(fossil_map_not_empty(map) == true);
    fossil_map_destroy(map);
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_map_is_empty) {
    fossil_map_t* map = fossil_map_create_container("ordered", "i32");
    ASSUME_ITS_TRUE(fossil_map_is_empty(map) == true);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(c_test_map_not_cnullptr) {
    fossil_map_t* map = fossil_map_create_container("ordered", "i32");
    ASSUME_ITS_TRUE(fossil_map_not_cnullptr(map) == true);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(c_test_map_is_cnullptr) {
    fossil_map_t* map = NULL;
    ASSUME_ITS_TRUE(fossil_map_is_cnullptr(map) == true);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(c_tofu_map_tests) {
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_create_destroy);
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_create_default);
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_create_copy);
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_create_move);
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_insert_get);
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_erase);
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_contains);
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_size);
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_not_empty);
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_is_empty);
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_not_cnullptr);
    FOSSIL_TEST_ADD(c_map_tofu_fixture, c_test_map_is_cnullptr);

    FOSSIL_TEST_REGISTER(c_map_tofu_fixture);
}
