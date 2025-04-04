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

FOSSIL_TEST_SUITE(cpp_mapof_tofu_fixture);

FOSSIL_SETUP(cpp_mapof_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_mapof_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_mapof_insert) {
    fossil_mapof_t* map = fossil_mapof_create_container(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    ASSUME_ITS_TRUE(fossil_mapof_insert(map, const_cast<char*>("key1"), const_cast<char*>("value1")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_mapof_size(map) == 1);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_mapof_remove) {
    fossil_mapof_t* map = fossil_mapof_create_container(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    fossil_mapof_insert(map, const_cast<char*>("key1"), const_cast<char*>("value1"));
    ASSUME_ITS_TRUE(fossil_mapof_remove(map, const_cast<char*>("key1")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_mapof_is_empty(map) == true);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_mapof_contains) {
    fossil_mapof_t* map = fossil_mapof_create_container(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    fossil_mapof_insert(map, const_cast<char*>("key1"), const_cast<char*>("value1"));
    ASSUME_ITS_TRUE(fossil_mapof_contains(map, const_cast<char*>("key1")) == true);
    ASSUME_ITS_TRUE(fossil_mapof_contains(map, const_cast<char*>("key2")) == false);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_mapof_get) {
    fossil_mapof_t* map = fossil_mapof_create_container(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    fossil_mapof_insert(map, const_cast<char*>("key1"), const_cast<char*>("value1"));
    fossil_tofu_t value = fossil_mapof_get(map, const_cast<char*>("key1"));
    ASSUME_ITS_TRUE(strcmp(fossil_tofu_get_value(&value), "value1") == 0);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_mapof_set) {
    fossil_mapof_t* map = fossil_mapof_create_container(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    fossil_mapof_insert(map, const_cast<char*>("key1"), const_cast<char*>("value1"));
    ASSUME_ITS_TRUE(fossil_mapof_set(map, const_cast<char*>("key1"), const_cast<char*>("value2")) == FOSSIL_TOFU_SUCCESS);
    fossil_tofu_t value = fossil_mapof_get(map, const_cast<char*>("key1"));
    ASSUME_ITS_TRUE(strcmp(fossil_tofu_get_value(&value), "value2") == 0);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_mapof_size) {
    fossil_mapof_t* map = fossil_mapof_create_container(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    fossil_mapof_insert(map, const_cast<char*>("key1"), const_cast<char*>("value1"));
    fossil_mapof_insert(map, const_cast<char*>("key2"), const_cast<char*>("value2"));
    ASSUME_ITS_TRUE(fossil_mapof_size(map) == 2);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_mapof_not_empty) {
    fossil_mapof_t* map = fossil_mapof_create_container(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    fossil_mapof_insert(map, const_cast<char*>("key1"), const_cast<char*>("value1"));
    ASSUME_ITS_TRUE(fossil_mapof_not_empty(map) == true);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_mapof_is_empty) {
    fossil_mapof_t* map = fossil_mapof_create_container(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    ASSUME_ITS_TRUE(fossil_mapof_is_empty(map) == true);
    fossil_mapof_insert(map, const_cast<char*>("key1"), const_cast<char*>("value1"));
    ASSUME_ITS_TRUE(fossil_mapof_is_empty(map) == false);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_mapof_insert_multiple) {
    fossil_mapof_t* map = fossil_mapof_create_container(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    ASSUME_ITS_TRUE(fossil_mapof_insert(map, const_cast<char*>("key1"), const_cast<char*>("value1")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_mapof_insert(map, const_cast<char*>("key2"), const_cast<char*>("value2")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_mapof_insert(map, const_cast<char*>("key3"), const_cast<char*>("value3")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_mapof_size(map) == 3);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_mapof_remove_multiple) {
    fossil_mapof_t* map = fossil_mapof_create_container(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    fossil_mapof_insert(map, const_cast<char*>("key1"), const_cast<char*>("value1"));
    fossil_mapof_insert(map, const_cast<char*>("key2"), const_cast<char*>("value2"));
    fossil_mapof_insert(map, const_cast<char*>("key3"), const_cast<char*>("value3"));
    ASSUME_ITS_TRUE(fossil_mapof_remove(map, const_cast<char*>("key1")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_mapof_remove(map, const_cast<char*>("key2")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_mapof_size(map) == 1);
    fossil_mapof_destroy(map);
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_insert) {
    fossil::tofu::MapOf map(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    ASSUME_ITS_TRUE(map.insert(const_cast<char*>("key1"), const_cast<char*>("value1")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(map.size() == 1);
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_remove) {
    fossil::tofu::MapOf map(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    map.insert(const_cast<char*>("key1"), const_cast<char*>("value1"));
    ASSUME_ITS_TRUE(map.remove(const_cast<char*>("key1")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(map.is_empty() == true);
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_contains) {
    fossil::tofu::MapOf map(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    map.insert(const_cast<char*>("key1"), const_cast<char*>("value1"));
    ASSUME_ITS_TRUE(map.contains(const_cast<char*>("key1")) == true);
    ASSUME_ITS_TRUE(map.contains(const_cast<char*>("key2")) == false);
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_get) {
    fossil::tofu::MapOf map(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    map.insert(const_cast<char*>("key1"), const_cast<char*>("value1"));
    fossil_tofu_t value = map.get(const_cast<char*>("key1"));
    ASSUME_ITS_TRUE(strcmp(fossil_tofu_get_value(&value), "value1") == 0);
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_set) {
    fossil::tofu::MapOf map(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    map.insert(const_cast<char*>("key1"), const_cast<char*>("value1"));
    ASSUME_ITS_TRUE(map.set(const_cast<char*>("key1"), const_cast<char*>("value2")) == FOSSIL_TOFU_SUCCESS);
    fossil_tofu_t value = map.get(const_cast<char*>("key1"));
    ASSUME_ITS_TRUE(strcmp(fossil_tofu_get_value(&value), "value2") == 0);
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_size) {
    fossil::tofu::MapOf map(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    map.insert(const_cast<char*>("key1"), const_cast<char*>("value1"));
    map.insert(const_cast<char*>("key2"), const_cast<char*>("value2"));
    ASSUME_ITS_TRUE(map.size() == 2);
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_not_empty) {
    fossil::tofu::MapOf map(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    map.insert(const_cast<char*>("key1"), const_cast<char*>("value1"));
    ASSUME_ITS_TRUE(map.not_empty() == true);
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_is_empty) {
    fossil::tofu::MapOf map(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    ASSUME_ITS_TRUE(map.is_empty() == true);
    map.insert(const_cast<char*>("key1"), const_cast<char*>("value1"));
    ASSUME_ITS_TRUE(map.is_empty() == false);
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_insert_multiple) {
    fossil::tofu::MapOf map(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    ASSUME_ITS_TRUE(map.insert(const_cast<char*>("key1"), const_cast<char*>("value1")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(map.insert(const_cast<char*>("key2"), const_cast<char*>("value2")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(map.insert(const_cast<char*>("key3"), const_cast<char*>("value3")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(map.size() == 3);
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_remove_multiple) {
    fossil::tofu::MapOf map(const_cast<char*>("cstr"), const_cast<char*>("cstr"));
    map.insert(const_cast<char*>("key1"), const_cast<char*>("value1"));
    map.insert(const_cast<char*>("key2"), const_cast<char*>("value2"));
    map.insert(const_cast<char*>("key3"), const_cast<char*>("value3"));
    ASSUME_ITS_TRUE(map.remove(const_cast<char*>("key1")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(map.remove(const_cast<char*>("key2")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(map.size() == 1);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_mapof_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_insert);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_remove);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_contains);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_get);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_set);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_size);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_not_empty);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_is_empty);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_insert_multiple);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_remove_multiple);

    // Class ToFu Fixture
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_insert);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_remove);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_contains);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_get);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_set);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_size);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_not_empty);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_is_empty);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_insert_multiple);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_remove_multiple);

    FOSSIL_TEST_REGISTER(cpp_mapof_tofu_fixture);
} // end of tests
