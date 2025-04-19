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

FOSSIL_TEST_CASE(cpp_test_mapof_class_insert_and_get) {
    fossil::tofu::MapOf map("cstr", "cstr");
    ASSUME_ITS_TRUE(map.insert(Tofu("key1"), Tofu("value1")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(map.insert(Tofu("key2"), Tofu("value2")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(map.insert(Tofu("key3"), Tofu("value3")) == FOSSIL_TOFU_SUCCESS);

    Tofu value1 = map.get(Tofu("key1"));
    Tofu value2 = map.get(Tofu("key2"));
    Tofu value3 = map.get(Tofu("key3"));

    ASSUME_ITS_TRUE(value1.get_value() == "value1");
    ASSUME_ITS_TRUE(value2.get_value() == "value2");
    ASSUME_ITS_TRUE(value3.get_value() == "value3");
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_remove) {
    fossil::tofu::MapOf map("cstr", "cstr");
    map.insert(Tofu("key1"), Tofu("value1"));
    map.insert(Tofu("key2"), Tofu("value2"));
    map.insert(Tofu("key3"), Tofu("value3"));

    ASSUME_ITS_TRUE(map.remove(Tofu("key1")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(map.remove(Tofu("key2")) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(map.size() == 1);
    ASSUME_ITS_TRUE(map.contains(Tofu("key3")));
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_contains) {
    fossil::tofu::MapOf map("cstr", "cstr");
    map.insert(Tofu("key1"), Tofu("value1"));
    map.insert(Tofu("key2"), Tofu("value2"));

    ASSUME_ITS_TRUE(map.contains(Tofu("key1")));
    ASSUME_ITS_TRUE(map.contains(Tofu("key2")));
    ASSUME_ITS_FALSE(map.contains(Tofu("key3")));
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_set) {
    fossil::tofu::MapOf map("cstr", "cstr");
    map.insert(Tofu("key1"), Tofu("value1"));
    ASSUME_ITS_TRUE(map.set(Tofu("key1"), Tofu("new_value1")) == FOSSIL_TOFU_SUCCESS);

    Tofu value = map.get(Tofu("key1"));
    ASSUME_ITS_TRUE(value.get_value() == "new_value1");
}

FOSSIL_TEST_CASE(cpp_test_mapof_class_size_and_empty) {
    fossil::tofu::MapOf map("cstr", "cstr");
    ASSUME_ITS_TRUE(map.is_empty());
    ASSUME_ITS_TRUE(map.size() == 0);

    map.insert(Tofu("key1"), Tofu("value1"));
    ASSUME_ITS_FALSE(map.is_empty());
    ASSUME_ITS_TRUE(map.size() == 1);

    map.remove(Tofu("key1"));
    ASSUME_ITS_TRUE(map.is_empty());
    ASSUME_ITS_TRUE(map.size() == 0);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_mapof_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_insert_and_get);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_remove);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_contains);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_set);
    FOSSIL_TEST_ADD(cpp_mapof_tofu_fixture, cpp_test_mapof_class_size_and_empty);

    FOSSIL_TEST_REGISTER(cpp_mapof_tofu_fixture);
} // end of tests
