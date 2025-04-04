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

FOSSIL_TEST_SUITE(c_vector_tofu_fixture);

FOSSIL_SETUP(c_vector_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(c_vector_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_vector_create_destroy) {
    fossil_vector_t* vector = fossil_vector_create_container("i32");
    ASSUME_ITS_TRUE(vector != NULL);
    ASSUME_ITS_TRUE(fossil_vector_is_empty(vector) == true);
    fossil_vector_destroy(vector);
}

FOSSIL_TEST_CASE(c_test_vector_push_back) {
    fossil_vector_t* vector = fossil_vector_create_container("i32");
    fossil_vector_push_back(vector, "42");
    ASSUME_ITS_TRUE(fossil_vector_size(vector) == 1);
    ASSUME_ITS_EQUAL_CSTR(fossil_vector_get(vector, 0), "42");
    fossil_vector_destroy(vector);
}

FOSSIL_TEST_CASE(c_test_vector_push_front) {
    fossil_vector_t* vector = fossil_vector_create_container("i32");
    fossil_vector_push_back(vector, "42");
    fossil_vector_push_front(vector, "84");
    ASSUME_ITS_TRUE(fossil_vector_size(vector) == 2);
    ASSUME_ITS_EQUAL_CSTR(fossil_vector_get(vector, 0), "84");
    ASSUME_ITS_EQUAL_CSTR(fossil_vector_get(vector, 1), "42");
    fossil_vector_destroy(vector);
}

FOSSIL_TEST_CASE(c_test_vector_push_at) {
    fossil_vector_t* vector = fossil_vector_create_container("i32");
    fossil_vector_push_back(vector, "42");
    fossil_vector_push_back(vector, "126");
    fossil_vector_push_at(vector, 1, "84");
    ASSUME_ITS_TRUE(fossil_vector_size(vector) == 3);
    ASSUME_ITS_EQUAL_CSTR(fossil_vector_get(vector, 0), "42");
    ASSUME_ITS_EQUAL_CSTR(fossil_vector_get(vector, 1), "84");
    ASSUME_ITS_EQUAL_CSTR(fossil_vector_get(vector, 2), "126");
    fossil_vector_destroy(vector);
}

FOSSIL_TEST_CASE(c_test_vector_pop_back) {
    fossil_vector_t* vector = fossil_vector_create_container("i32");
    fossil_vector_push_back(vector, "42");
    fossil_vector_push_back(vector, "84");
    fossil_vector_pop_back(vector);
    ASSUME_ITS_TRUE(fossil_vector_size(vector) == 1);
    ASSUME_ITS_EQUAL_CSTR(fossil_vector_get(vector, 0), "42");
    fossil_vector_destroy(vector);
}

FOSSIL_TEST_CASE(c_test_vector_pop_front) {
    fossil_vector_t* vector = fossil_vector_create_container("i32");
    fossil_vector_push_back(vector, "42");
    fossil_vector_push_back(vector, "84");
    fossil_vector_pop_front(vector);
    ASSUME_ITS_TRUE(fossil_vector_size(vector) == 1);
    ASSUME_ITS_EQUAL_CSTR(fossil_vector_get(vector, 0), "84");
    fossil_vector_destroy(vector);
}

FOSSIL_TEST_CASE(c_test_vector_pop_at) {
    fossil_vector_t* vector = fossil_vector_create_container("i32");
    fossil_vector_push_back(vector, "42");
    fossil_vector_push_back(vector, "84");
    fossil_vector_push_back(vector, "126");
    fossil_vector_pop_at(vector, 1);
    ASSUME_ITS_TRUE(fossil_vector_size(vector) == 2);
    ASSUME_ITS_EQUAL_CSTR(fossil_vector_get(vector, 0), "42");
    ASSUME_ITS_EQUAL_CSTR(fossil_vector_get(vector, 1), "126");
    fossil_vector_destroy(vector);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_vector_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(c_vector_tofu_fixture, c_test_vector_create_destroy);
    FOSSIL_TEST_ADD(c_vector_tofu_fixture, c_test_vector_push_back);
    FOSSIL_TEST_ADD(c_vector_tofu_fixture, c_test_vector_push_front);
    FOSSIL_TEST_ADD(c_vector_tofu_fixture, c_test_vector_push_at);
    FOSSIL_TEST_ADD(c_vector_tofu_fixture, c_test_vector_pop_back);
    FOSSIL_TEST_ADD(c_vector_tofu_fixture, c_test_vector_pop_front);
    FOSSIL_TEST_ADD(c_vector_tofu_fixture, c_test_vector_pop_at);

    FOSSIL_TEST_REGISTER(c_vector_tofu_fixture);
} // end of tests
