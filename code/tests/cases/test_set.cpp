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

FOSSIL_TEST_SUITE(cpp_set_tofu_fixture);

FOSSIL_SETUP(cpp_set_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_set_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_set_insert) {
    auto set = fossil::set_create_container("i32");
    fossil::set_insert(set, "42");
    ASSUME_ITS_TRUE(fossil::set_size(set) == 1);
    fossil::set_destroy(set);
}

FOSSIL_TEST_CASE(cpp_test_set_erase) {
    auto set = fossil::set_create_container("i32");
    fossil::set_insert(set, "42");
    fossil::set_erase(set);
    ASSUME_ITS_TRUE(fossil::set_is_empty(set) == true);
    fossil::set_destroy(set);
}

FOSSIL_TEST_CASE(cpp_test_set_not_empty) {
    auto set = fossil::set_create_container("i32");
    fossil::set_insert(set, "42");
    ASSUME_ITS_TRUE(fossil::set_not_empty(set) == true);
    fossil::set_destroy(set);
}

FOSSIL_TEST_CASE(cpp_test_set_not_cnullptr) {
    auto set = fossil::set_create_container("i32");
    ASSUME_ITS_TRUE(fossil::set_not_cnullptr(set) == true);
    fossil::set_destroy(set);
}

FOSSIL_TEST_CASE(cpp_test_set_is_cnullptr) {
    auto set = nullptr;
    ASSUME_ITS_TRUE(fossil::set_is_cnullptr(set) == true);
}

FOSSIL_TEST_CASE(cpp_test_set_is_empty) {
    auto set = fossil::set_create_container("i32");
    ASSUME_ITS_TRUE(fossil::set_is_empty(set) == true);
    fossil::set_destroy(set);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_set_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_set_tofu_fixture, cpp_test_set_insert);
    FOSSIL_TEST_ADD(cpp_set_tofu_fixture, cpp_test_set_erase);
    FOSSIL_TEST_ADD(cpp_set_tofu_fixture, cpp_test_set_not_empty);
    FOSSIL_TEST_ADD(cpp_set_tofu_fixture, cpp_test_set_not_cnullptr);
    FOSSIL_TEST_ADD(cpp_set_tofu_fixture, cpp_test_set_is_cnullptr);
    FOSSIL_TEST_ADD(cpp_set_tofu_fixture, cpp_test_set_is_empty);

    FOSSIL_TEST_REGISTER(cpp_set_tofu_fixture);
} // end of tests
