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

FOSSIL_TEST_SUITE(cpp_queue_tofu_fixture);

FOSSIL_SETUP(cpp_queue_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_queue_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_queue_insert) {
    auto queue = fossil::queue_create_container("i32");
    ASSUME_ITS_TRUE(fossil::queue_insert(queue, "42") == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil::queue_size(queue) == 1);
    fossil::queue_destroy(queue);
}

FOSSIL_TEST_CASE(cpp_test_queue_remove) {
    auto queue = fossil::queue_create_container("i32");
    fossil::queue_insert(queue, "42");
    ASSUME_ITS_TRUE(fossil::queue_remove(queue) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil::queue_is_empty(queue) == true);
    fossil::queue_destroy(queue);
}

FOSSIL_TEST_CASE(cpp_test_queue_not_empty) {
    auto queue = fossil::queue_create_container("i32");
    fossil::queue_insert(queue, "42");
    ASSUME_ITS_TRUE(fossil::queue_not_empty(queue) == true);
    fossil::queue_destroy(queue);
}

FOSSIL_TEST_CASE(cpp_test_queue_not_cnullptr) {
    auto queue = fossil::queue_create_container("i32");
    ASSUME_ITS_TRUE(fossil::queue_not_cnullptr(queue) == true);
    fossil::queue_destroy(queue);
}

FOSSIL_TEST_CASE(cpp_test_queue_is_empty) {
    auto queue = fossil::queue_create_container("i32");
    ASSUME_ITS_TRUE(fossil::queue_is_empty(queue) == true);
    fossil::queue_insert(queue, "42");
    ASSUME_ITS_TRUE(fossil::queue_is_empty(queue) == false);
    fossil::queue_destroy(queue);
}

FOSSIL_TEST_CASE(cpp_test_queue_is_cnullptr) {
    fossil_queue_t* queue = nullptr;
    ASSUME_ITS_TRUE(fossil::queue_is_cnullptr(queue) == true);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_queue_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_queue_tofu_fixture, cpp_test_queue_insert);
    FOSSIL_TEST_ADD(cpp_queue_tofu_fixture, cpp_test_queue_remove);
    FOSSIL_TEST_ADD(cpp_queue_tofu_fixture, cpp_test_queue_not_empty);
    FOSSIL_TEST_ADD(cpp_queue_tofu_fixture, cpp_test_queue_not_cnullptr);
    FOSSIL_TEST_ADD(cpp_queue_tofu_fixture, cpp_test_queue_is_empty);
    FOSSIL_TEST_ADD(cpp_queue_tofu_fixture, cpp_test_queue_is_cnullptr);

    FOSSIL_TEST_REGISTER(cpp_queue_tofu_fixture);
} // end of tests