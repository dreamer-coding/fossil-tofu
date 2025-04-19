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
    fossil::tofu::Vector vector("i32");
    vector.push_back("42");
    ASSUME_ITS_TRUE(vector.size() == 1);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0), "42");
}

FOSSIL_TEST_CASE(cpp_test_vector_class_push_front) {
    fossil::tofu::Vector vector("i32");
    vector.push_back("42");
    vector.push_front("84");
    ASSUME_ITS_TRUE(vector.size() == 2);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0), "84");
    ASSUME_ITS_EQUAL_CSTR(vector.get(1), "42");
}

FOSSIL_TEST_CASE(cpp_test_vector_class_push_at) {
    fossil::tofu::Vector vector("i32");
    vector.push_back("42");
    vector.push_back("126");
    vector.push_at(1, "84");
    ASSUME_ITS_TRUE(vector.size() == 3);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0), "42");
    ASSUME_ITS_EQUAL_CSTR(vector.get(1), "84");
    ASSUME_ITS_EQUAL_CSTR(vector.get(2), "126");
}

FOSSIL_TEST_CASE(cpp_test_vector_class_pop_back) {
    fossil::tofu::Vector vector("i32");
    vector.push_back("42");
    vector.push_back("84");
    vector.pop_back();
    ASSUME_ITS_TRUE(vector.size() == 1);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0), "42");
}

FOSSIL_TEST_CASE(cpp_test_vector_class_pop_front) {
    fossil::tofu::Vector vector("i32");
    vector.push_back("42");
    vector.push_back("84");
    vector.pop_front();
    ASSUME_ITS_TRUE(vector.size() == 1);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0), "84");
}

FOSSIL_TEST_CASE(cpp_test_vector_class_pop_at) {
    fossil::tofu::Vector vector("i32");
    vector.push_back("42");
    vector.push_back("84");
    vector.push_back("126");
    vector.pop_at(1);
    ASSUME_ITS_TRUE(vector.size() == 2);
    ASSUME_ITS_EQUAL_CSTR(vector.get(0), "42");
    ASSUME_ITS_EQUAL_CSTR(vector.get(1), "126");
}

FOSSIL_TEST_CASE(cpp_test_vector_class_is_empty) {
    fossil::tofu::Vector vector("i32");
    ASSUME_ITS_TRUE(vector.is_empty());
    vector.push_back("42");
    ASSUME_ITS_TRUE(!vector.is_empty());
}

FOSSIL_TEST_CASE(cpp_test_vector_class_size) {
    fossil::tofu::Vector vector("i32");
    ASSUME_ITS_TRUE(vector.size() == 0);
    vector.push_back("42");
    ASSUME_ITS_TRUE(vector.size() == 1);
}

FOSSIL_TEST_CASE(cpp_test_vector_class_get_set) {
    fossil::tofu::Vector vector("i32");
    vector.push_back("42");
    vector.set(0, "84");
    ASSUME_ITS_EQUAL_CSTR(vector.get(0), "84");
}

FOSSIL_TEST_CASE(cpp_test_vector_class_get_front_back) {
    fossil::tofu::Vector vector("i32");
    vector.push_back("42");
    vector.push_back("84");
    ASSUME_ITS_EQUAL_CSTR(vector.get_front().c_str(), "42");
    ASSUME_ITS_EQUAL_CSTR(vector.get_back().c_str(), "84");
}

FOSSIL_TEST_CASE(cpp_test_vector_class_equality_operator) {
    fossil::tofu::Vector vector1("i32");
    fossil::tofu::Vector vector2("i32");
    vector1.push_back("42");
    vector2.push_back("42");
    ASSUME_ITS_TRUE(vector1 == vector2);
    vector2.push_back("84");
    ASSUME_ITS_TRUE(vector1 != vector2);
}

FOSSIL_TEST_CASE(cpp_test_vector_class_move_assignment_operator) {
    fossil::tofu::Vector vector1("i32");
    vector1.push_back("42");
    vector1.push_back("84");

    fossil::tofu::Vector vector2("i32");
    vector2 = std::move(vector1);

    ASSUME_ITS_TRUE(vector2.size() == 2);
    ASSUME_ITS_EQUAL_CSTR(vector2.get(0), "42");
    ASSUME_ITS_EQUAL_CSTR(vector2.get(1), "84");
    ASSUME_ITS_TRUE(vector1.is_empty());
}

FOSSIL_TEST_CASE(cpp_test_vector_class_subscript_operator) {
    fossil::tofu::Vector vector("i32");
    vector.push_back("42");
    vector.push_back("84");

    ASSUME_ITS_EQUAL_CSTR(vector[0], "42");
    ASSUME_ITS_EQUAL_CSTR(vector[1], "84");

    vector.set(0, "126");
    ASSUME_ITS_EQUAL_CSTR(vector[0], "126");

    try {
        vector[2]; // Accessing out of bounds
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        ASSUME_ITS_TRUE(true); // Exception caught as expected
    }
}

FOSSIL_TEST_CASE(cpp_test_vector_class_const_subscript_operator) {
    fossil::tofu::Vector vector("i32");
    vector.push_back("42");
    vector.push_back("84");

    const fossil::tofu::Vector& const_vector = vector;
    ASSUME_ITS_EQUAL_CSTR(const_vector[0], "42");
    ASSUME_ITS_EQUAL_CSTR(const_vector[1], "84");

    try {
        const_vector[2]; // Accessing out of bounds
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        ASSUME_ITS_TRUE(true); // Exception caught as expected
    }
}

FOSSIL_TEST_CASE(cpp_test_vector_class_inequality_operator) {
    fossil::tofu::Vector vector1("i32");
    fossil::tofu::Vector vector2("i32");

    vector1.push_back("42");
    vector2.push_back("84");

    ASSUME_ITS_TRUE(vector1 != vector2);
    vector2.set(0, "42");
    ASSUME_ITS_TRUE(vector1 == vector2);
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
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_is_empty);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_size);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_get_set);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_get_front_back);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_equality_operator);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_move_assignment_operator);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_subscript_operator);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_const_subscript_operator);
    FOSSIL_TEST_ADD(cpp_vector_tofu_fixture, cpp_test_vector_class_inequality_operator);

    FOSSIL_TEST_REGISTER(cpp_vector_tofu_fixture);
} // end of tests
