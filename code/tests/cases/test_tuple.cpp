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

FOSSIL_TEST_CASE(cpp_test_tuple_add_multiple_elements) {
    fossil::tofu::Tuple tuple("i32");
    tuple.add(fossil::tofu::Tofu("42"));
    tuple.add(fossil::tofu::Tofu("84"));
    tuple.add(fossil::tofu::Tofu("126"));
    ASSUME_ITS_EQUAL(tuple.size(), 3);
    ASSUME_ITS_EQUAL(tuple.get(0).get_value(), "42");
    ASSUME_ITS_EQUAL(tuple.get(1).get_value(), "84");
    ASSUME_ITS_EQUAL(tuple.get(2).get_value(), "126");
}

FOSSIL_TEST_CASE(cpp_test_tuple_remove_element) {
    fossil::tofu::Tuple tuple("i32");
    tuple.add(fossil::tofu::Tofu("42"));
    tuple.add(fossil::tofu::Tofu("84"));
    tuple.remove(0);
    ASSUME_ITS_EQUAL(tuple.size(), 1);
    ASSUME_ITS_EQUAL(tuple.get(0).get_value(), "84");
}

FOSSIL_TEST_CASE(cpp_test_tuple_clear_elements) {
    fossil::tofu::Tuple tuple("i32");
    tuple.add(fossil::tofu::Tofu("42"));
    tuple.add(fossil::tofu::Tofu("84"));
    tuple.clear();
    ASSUME_ITS_TRUE(tuple.is_empty());
    ASSUME_ITS_EQUAL(tuple.size(), 0);
}

FOSSIL_TEST_CASE(cpp_test_tuple_set_element) {
    fossil::tofu::Tuple tuple("i32");
    tuple.add(fossil::tofu::Tofu("42"));
    tuple.set(0, fossil::tofu::Tofu("84"));
    ASSUME_ITS_EQUAL(tuple.get(0).get_value(), "84");
}

FOSSIL_TEST_CASE(cpp_test_tuple_get_front_and_back) {
    fossil::tofu::Tuple tuple("i32");
    tuple.add(fossil::tofu::Tofu("42"));
    tuple.add(fossil::tofu::Tofu("84"));
    ASSUME_ITS_EQUAL(tuple.get_front().get_value(), "42");
    ASSUME_ITS_EQUAL(tuple.get_back().get_value(), "84");
}

FOSSIL_TEST_CASE(cpp_test_tuple_set_front_and_back) {
    fossil::tofu::Tuple tuple("i32");
    tuple.add(fossil::tofu::Tofu("42"));
    tuple.add(fossil::tofu::Tofu("84"));
    tuple.set_front(fossil::tofu::Tofu("21"));
    tuple.set_back(fossil::tofu::Tofu("126"));
    ASSUME_ITS_EQUAL(tuple.get_front().get_value(), "21");
    ASSUME_ITS_EQUAL(tuple.get_back().get_value(), "126");
}

FOSSIL_TEST_CASE(cpp_test_tuple_capacity) {
    fossil::tofu::Tuple tuple("i32");
    tuple.add(fossil::tofu::Tofu("42"));
    tuple.add(fossil::tofu::Tofu("84"));
    ASSUME_ITS_TRUE(tuple.capacity() >= tuple.size());
}

FOSSIL_TEST_CASE(cpp_test_tuple_copy_constructor) {
    fossil::tofu::Tuple original("i32");
    original.add(fossil::tofu::Tofu("42"));
    fossil::tofu::Tuple copy(original);
    ASSUME_ITS_EQUAL(copy.size(), 1);
    ASSUME_ITS_EQUAL(copy.get(0).get_value(), "42");
}

FOSSIL_TEST_CASE(cpp_test_tuple_move_constructor) {
    fossil::tofu::Tuple original("i32");
    original.add(fossil::tofu::Tofu("42"));
    fossil::tofu::Tuple moved(std::move(original));
    ASSUME_ITS_EQUAL(moved.size(), 1);
    ASSUME_ITS_EQUAL(moved.get(0).get_value(), "42");
    ASSUME_ITS_TRUE(original.is_empty());
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_tuple_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_add_multiple_elements);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_remove_element);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_clear_elements);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_set_element);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_get_front_and_back);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_set_front_and_back);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_capacity);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_copy_constructor);
    FOSSIL_TEST_ADD(cpp_tuple_tofu_fixture, cpp_test_tuple_move_constructor);

    FOSSIL_TEST_REGISTER(cpp_tuple_tofu_fixture);
} // end of tests
