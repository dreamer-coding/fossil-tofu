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

using namespace fossil;

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_SUITE(cpp_tuple_tofu_fixture);

FOSSIL_SETUP(cpp_tuple_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_tuple_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_tuple_create_destroy) {
    fossil_tuple_t* tuple = fossil::tuple_create("i32");
    ASSUME_ITS_TRUE(tuple != NULL);
    ASSUME_ITS_TRUE(fossil::tuple_is_empty(tuple) == true);
    fossil::tuple_destroy(tuple);
}

FOSSIL_TEST_CASE(cpp_test_tuple_add) {
    fossil_tuple_t* tuple = fossil::tuple_create("i32");
    fossil::tuple_add(tuple, "42");
    ASSUME_ITS_TRUE(fossil::tuple_size(tuple) == 1);
    ASSUME_ITS_EQUAL_CSTR(fossil::tuple_get(tuple, 0).c_str(), "42");
    fossil::tuple_destroy(tuple);
}

FOSSIL_TEST_CASE(cpp_test_tuple_remove) {
    fossil_tuple_t* tuple = fossil::tuple_create("i32");
    fossil::tuple_add(tuple, "42");
    fossil::tuple_add(tuple, "84");
    fossil::tuple_remove(tuple, 0);
    ASSUME_ITS_TRUE(fossil::tuple_size(tuple) == 1);
    ASSUME_ITS_EQUAL_CSTR(fossil::tuple_get(tuple, 0).c_str(), "84");
    fossil::tuple_destroy(tuple);
}

FOSSIL_TEST_CASE(cpp_test_tuple_clear) {
    fossil_tuple_t* tuple = fossil::tuple_create("i32");
    fossil::tuple_add(tuple, "42");
    fossil::tuple_add(tuple, "84");
    fossil::tuple_clear(tuple);
    ASSUME_ITS_TRUE(fossil::tuple_is_empty(tuple) == true);
    fossil::tuple_destroy(tuple);
}

FOSSIL_TEST_CASE(cpp_test_tuple_algorithm_search) {
    fossil_tuple_t* tuple = fossil::tuple_create("i32");
    fossil::tuple_add(tuple, "42");
    fossil::tuple_add(tuple, "84");
    fossil::tuple_add(tuple, "126");
    ASSUME_ITS_TRUE(fossil::tuple_algorithm_search(tuple, "84") == 1);
    fossil::tuple_destroy(tuple);
}

FOSSIL_TEST_CASE(cpp_test_tuple_algorithm_sort) {
    fossil_tuple_t* tuple = fossil::tuple_create("i32");
    fossil::tuple_add(tuple, "126");
    fossil::tuple_add(tuple, "42");
    fossil::tuple_add(tuple, "84");
    ASSUME_ITS_TRUE(fossil::tuple_algorithm_sort(tuple) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_EQUAL_CSTR(fossil::tuple_get(tuple, 0).c_str(), "42");
    ASSUME_ITS_EQUAL_CSTR(fossil::tuple_get(tuple, 1).c_str(), "84");
    ASSUME_ITS_EQUAL_CSTR(fossil::tuple_get(tuple, 2).c_str(), "126");
    fossil::tuple_destroy(tuple);
}

FOSSIL_TEST_CASE(cpp_test_tuple_algorithm_reverse) {
    fossil_tuple_t* tuple = fossil::tuple_create("i32");
    fossil::tuple_add(tuple, "42");
    fossil::tuple_add(tuple, "84");
    fossil::tuple_add(tuple, "126");
    ASSUME_ITS_TRUE(fossil::tuple_algorithm_reverse(tuple) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_EQUAL_CSTR(fossil::tuple_get(tuple, 0).c_str(), "126");
    ASSUME_ITS_EQUAL_CSTR(fossil::tuple_get(tuple, 1).c_str(), "84");
    ASSUME_ITS_EQUAL_CSTR(fossil::tuple_get(tuple, 2).c_str(), "42");
    fossil::tuple_destroy(tuple);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_tuple_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_create_destroy);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_add);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_remove);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_clear);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_algorithm_search);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_algorithm_sort);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_algorithm_reverse);

    FOSSIL_TEST_REGISTER(cpp_tuple_tofu_fixture);
} // end of tests
