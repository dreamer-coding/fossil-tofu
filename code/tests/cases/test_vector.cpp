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

FOSSIL_TEST_SUITE(cpp_vector_tofu_fixture);

FOSSIL_SETUP(cpp_vector_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_vector_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_vector_class_push_back) {
    fossil::tofu::Vector vector("i8");
    vector.push_back(fossil::tofu::Tofu("i8", "42"));
    ASSUME_ITS_TRUE(vector.size() == 1);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0).get_value().c_str(), "42");

    // Edge case: Push back on an empty vector
    fossil::tofu::Vector empty_vector("i8");
    empty_vector.push_back(fossil::tofu::Tofu("i8", "99"));
    ASSUME_ITS_TRUE(empty_vector.size() == 1);
    ASSUME_ITS_EQUAL_CSTR(empty_vector.get(0).get_value().c_str(), "99");
}

FOSSIL_TEST_CASE(cpp_test_vector_class_push_front) {
    fossil::tofu::Vector vector("i8");
    vector.push_back(fossil::tofu::Tofu("i8", "42"));
    vector.push_front(fossil::tofu::Tofu("i8", "84"));
    ASSUME_ITS_TRUE(vector.size() == 2);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0).get_value().c_str(), "84");
    ASSUME_ITS_EQUAL_CSTR(vector.get(1).get_value().c_str(), "42");

    // Edge case: Push front on an empty vector
    fossil::tofu::Vector empty_vector("i8");
    empty_vector.push_front(fossil::tofu::Tofu("i8", "99"));
    ASSUME_ITS_TRUE(empty_vector.size() == 1);
    ASSUME_ITS_EQUAL_CSTR(empty_vector.get(0).get_value().c_str(), "99");
}

FOSSIL_TEST_CASE(cpp_test_vector_class_push_at) {
    fossil::tofu::Vector vector("i8");
    vector.push_back(fossil::tofu::Tofu("i8", "42"));
    vector.push_back(fossil::tofu::Tofu("i8", "126"));
    vector.push_at(1, fossil::tofu::Tofu("i8", "84"));
    ASSUME_ITS_TRUE(vector.size() == 3);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0).get_value().c_str(), "42");
    ASSUME_ITS_EQUAL_CSTR(vector.get(1).get_value().c_str(), "84");
    ASSUME_ITS_EQUAL_CSTR(vector.get(2).get_value().c_str(), "126");

    // Edge case: Push at an invalid index
    try {
        vector.push_at(10, fossil::tofu::Tofu("i8", "99"));
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::out_of_range&) {
        ASSUME_ITS_TRUE(true); // Exception caught as expected
    }
}

FOSSIL_TEST_CASE(cpp_test_vector_class_pop_back) {
    fossil::tofu::Vector vector("i8");
    vector.push_back(fossil::tofu::Tofu("i8", "42"));
    vector.push_back(fossil::tofu::Tofu("i8", "84"));
    vector.pop_back();
    ASSUME_ITS_TRUE(vector.size() == 1);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0).get_value().c_str(), "42");

    // Edge case: Pop back on an empty vector
    fossil::tofu::Vector empty_vector("i8");
    try {
        empty_vector.pop_back();
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::out_of_range&) {
        ASSUME_ITS_TRUE(true); // Exception caught as expected
    }
}

FOSSIL_TEST_CASE(cpp_test_vector_class_pop_front) {
    fossil::tofu::Vector vector("i8");
    vector.push_back(fossil::tofu::Tofu("i8", "42"));
    vector.push_back(fossil::tofu::Tofu("i8", "84"));
    vector.pop_front();
    ASSUME_ITS_TRUE(vector.size() == 1);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0).get_value().c_str(), "84");

    // Edge case: Pop front on an empty vector
    fossil::tofu::Vector empty_vector("i8");
    try {
        empty_vector.pop_front();
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::out_of_range&) {
        ASSUME_ITS_TRUE(true); // Exception caught as expected
    }
}

FOSSIL_TEST_CASE(cpp_test_vector_class_pop_at) {
    fossil::tofu::Vector vector("i8");
    vector.push_back(fossil::tofu::Tofu("i8", "42"));
    vector.push_back(fossil::tofu::Tofu("i8", "84"));
    vector.push_back(fossil::tofu::Tofu("i8", "126"));
    vector.pop_at(1);
    ASSUME_ITS_TRUE(vector.size() == 2);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0).get_value().c_str(), "42");
    ASSUME_ITS_EQUAL_CSTR(vector.get(1).get_value().c_str(), "126");

    // Edge case: Pop at an invalid index
    try {
        vector.pop_at(10);
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::out_of_range&) {
        ASSUME_ITS_TRUE(true); // Exception caught as expected
    }
}

FOSSIL_TEST_CASE(cpp_test_vector_class_erase) {
    fossil::tofu::Vector vector("i8");
    vector.push_back(fossil::tofu::Tofu("i8", "42"));
    vector.push_back(fossil::tofu::Tofu("i8", "84"));
    vector.erase();
    ASSUME_ITS_TRUE(vector.is_empty());

    // Edge case: Erase an already empty vector
    fossil::tofu::Vector empty_vector("i8");
    empty_vector.erase();
    ASSUME_ITS_TRUE(empty_vector.is_empty());
}

FOSSIL_TEST_CASE(cpp_test_vector_class_set) {
    fossil::tofu::Vector vector("i8");
    vector.push_back(fossil::tofu::Tofu("i8", "42"));
    vector.set(0, fossil::tofu::Tofu("i8", "84"));
    ASSUME_ITS_EQUAL_CSTR(vector.get(0).get_value().c_str(), "84");

    // Edge case: Set at an invalid index
    try {
        vector.set(10, fossil::tofu::Tofu("i8", "99"));
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::out_of_range&) {
        ASSUME_ITS_TRUE(true); // Exception caught as expected
    }
}

FOSSIL_TEST_CASE(cpp_test_vector_class_is_empty) {
    fossil::tofu::Vector vector("i8");
    ASSUME_ITS_TRUE(vector.is_empty());
    vector.push_back(fossil::tofu::Tofu("i8", "42"));
    ASSUME_ITS_TRUE(!vector.is_empty());

    // Edge case: Check is_empty after erase
    vector.erase();
    ASSUME_ITS_TRUE(vector.is_empty());
}

FOSSIL_TEST_CASE(cpp_test_vector_class_size) {
    fossil::tofu::Vector vector("i8");
    ASSUME_ITS_TRUE(vector.size() == 0);
    vector.push_back(fossil::tofu::Tofu("i8", "42"));
    ASSUME_ITS_TRUE(vector.size() == 1);

    // Edge case: Check size after multiple operations
    vector.push_back(fossil::tofu::Tofu("i8", "84"));
    vector.pop_front();
    ASSUME_ITS_TRUE(vector.size() == 1);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_vector_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_push_back);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_push_front);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_push_at);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_pop_back);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_pop_front);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_pop_at);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_erase);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_set);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_is_empty);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_size);

    FOSSIL_TEST_REGISTER(cpp_vector_tofu_fixture);
} // end of tests
