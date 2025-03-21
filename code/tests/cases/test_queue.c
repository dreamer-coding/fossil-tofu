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

FOSSIL_TEST_SUITE(c_queue_tofu_fixture);

FOSSIL_SETUP(c_queue_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(c_queue_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_queue_insert) {
    fossil_queue_t* queue = fossil_queue_create_container("i32");
    ASSUME_ITS_TRUE(fossil_queue_insert(queue, "42") == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_queue_size(queue) == 1);
    fossil_queue_destroy(queue);
}

FOSSIL_TEST_CASE(c_test_queue_remove) {
    fossil_queue_t* queue = fossil_queue_create_container("i32");
    fossil_queue_insert(queue, "42");
    ASSUME_ITS_TRUE(fossil_queue_remove(queue) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(fossil_queue_is_empty(queue) == true);
    fossil_queue_destroy(queue);
}

FOSSIL_TEST_CASE(c_test_queue_not_empty) {
    fossil_queue_t* queue = fossil_queue_create_container("i32");
    fossil_queue_insert(queue, "42");
    ASSUME_ITS_TRUE(fossil_queue_not_empty(queue) == true);
    fossil_queue_destroy(queue);
}

FOSSIL_TEST_CASE(c_test_queue_not_cnullptr) {
    fossil_queue_t* queue = fossil_queue_create_container("i32");
    ASSUME_ITS_TRUE(fossil_queue_not_cnullptr(queue) == true);
    fossil_queue_destroy(queue);
}

FOSSIL_TEST_CASE(c_test_queue_is_empty) {
    fossil_queue_t* queue = fossil_queue_create_container("i32");
    ASSUME_ITS_TRUE(fossil_queue_is_empty(queue) == true);
    fossil_queue_insert(queue, "42");
    ASSUME_ITS_TRUE(fossil_queue_is_empty(queue) == false);
    fossil_queue_destroy(queue);
}

FOSSIL_TEST_CASE(c_test_queue_is_cnullptr) {
    fossil_queue_t* queue = NULL;
    ASSUME_ITS_TRUE(fossil_queue_is_cnullptr(queue) == true);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_queue_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(c_queue_tofu_fixture, c_test_queue_insert);
    FOSSIL_TEST_ADD(c_queue_tofu_fixture, c_test_queue_remove);
    FOSSIL_TEST_ADD(c_queue_tofu_fixture, c_test_queue_not_empty);
    FOSSIL_TEST_ADD(c_queue_tofu_fixture, c_test_queue_not_cnullptr);
    FOSSIL_TEST_ADD(c_queue_tofu_fixture, c_test_queue_is_empty);
    FOSSIL_TEST_ADD(c_queue_tofu_fixture, c_test_queue_is_cnullptr);

    FOSSIL_TEST_REGISTER(c_queue_tofu_fixture);
} // end of tests
