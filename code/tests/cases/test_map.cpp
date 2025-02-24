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

FOSSIL_TEST_SUITE(cpp_map_tofu_fixture);

FOSSIL_SETUP(cpp_map_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_map_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_map_insert) {
    fossil_map_t* map = fossil_map_create_default();
    ASSUME_ITS_TRUE(fossil_map_insert(map, "key1", "value1") == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_map_size(map) == 1);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_map_erase) {
    fossil_map_t* map = fossil_map_create_default();
    fossil_map_insert(map, "key1", "value1");
    ASSUME_ITS_TRUE(fossil_map_erase(map, "key1") == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_map_is_empty(map) == true);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_map_not_empty) {
    fossil_map_t* map = fossil_map_create_default();
    fossil_map_insert(map, "key1", "value1");
    ASSUME_ITS_TRUE(fossil_map_not_empty(map) == true);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_map_not_cnullptr) {
    fossil_map_t* map = fossil_map_create_default();
    ASSUME_ITS_TRUE(fossil_map_not_cnullptr(map) == true);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_map_is_empty) {
    fossil_map_t* map = fossil_map_create_default();
    ASSUME_ITS_TRUE(fossil_map_is_empty(map) == true);
    fossil_map_insert(map, "key1", "value1");
    ASSUME_ITS_TRUE(fossil_map_is_empty(map) == false);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_map_is_cnullptr) {
    fossil_map_t* map = NULL;
    ASSUME_ITS_TRUE(fossil_map_is_cnullptr(map) == true);
}

FOSSIL_TEST_CASE(cpp_test_map_contains) {
    fossil_map_t* map = fossil_map_create_default();
    fossil_map_insert(map, "key1", "value1");
    ASSUME_ITS_TRUE(fossil_map_contains(map, "key1") == true);
    ASSUME_ITS_TRUE(fossil_map_contains(map, "key2") == false);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_map_get) {
    fossil_map_t* map = fossil_map_create_default();
    fossil_map_insert(map, "key1", "value1");
    ASSUME_ITS_TRUE(strcmp(fossil_map_get(map, "key1"), "value1") == 0);
    ASSUME_ITS_TRUE(fossil_map_get(map, "key2") == NULL);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_map_size) {
    fossil_map_t* map = fossil_map_create_default();
    fossil_map_insert(map, "key1", "value1");
    fossil_map_insert(map, "key2", "value2");
    ASSUME_ITS_TRUE(fossil_map_size(map) == 2);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_map_insert_multiple) {
    fossil_map_t* map = fossil_map_create_default();
    ASSUME_ITS_TRUE(fossil_map_insert(map, "key1", "value1") == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_map_insert(map, "key2", "value2") == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_map_insert(map, "key3", "value3") == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_map_size(map) == 3);
    fossil_map_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_map_erase_multiple) {
    fossil_map_t* map = fossil_map_create_default();
    fossil_map_insert(map, "key1", "value1");
    fossil_map_insert(map, "key2", "value2");
    fossil_map_insert(map, "key3", "value3");
    ASSUME_ITS_TRUE(fossil_map_erase(map, "key1") == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_map_erase(map, "key2") == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_map_size(map) == 1);
    fossil_map_destroy(map);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(cpp_map_tofu_tests) {
    FOSSIL_TEST_ADD(cpp_map_tofu_fixture, cpp_test_map_insert);
    FOSSIL_TEST_ADD(cpp_map_tofu_fixture, cpp_test_map_erase);
    FOSSIL_TEST_ADD(cpp_map_tofu_fixture, cpp_test_map_not_empty);
    FOSSIL_TEST_ADD(cpp_map_tofu_fixture, cpp_test_map_not_cnullptr);
    FOSSIL_TEST_ADD(cpp_map_tofu_fixture, cpp_test_map_is_empty);
    FOSSIL_TEST_ADD(cpp_map_tofu_fixture, cpp_test_map_is_cnullptr);
    FOSSIL_TEST_ADD(cpp_map_tofu_fixture, cpp_test_map_contains);
    FOSSIL_TEST_ADD(cpp_map_tofu_fixture, cpp_test_map_get);
    FOSSIL_TEST_ADD(cpp_map_tofu_fixture, cpp_test_map_size);
    FOSSIL_TEST_ADD(cpp_map_tofu_fixture, cpp_test_map_insert_multiple);
    FOSSIL_TEST_ADD(cpp_map_tofu_fixture, cpp_test_map_erase_multiple);

    FOSSIL_TEST_REGISTER(cpp_map_tofu_fixture);
}
