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

FOSSIL_TEST_SUITE(cpp_stack_tofu_fixture);

FOSSIL_SETUP(cpp_stack_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_stack_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_stack_class_insert) {
    fossil::tofu::Stack stack("i32");
    fossil::tofu::Tofu tofu("i32", "42");
    ASSUME_ITS_TRUE(stack.insert(tofu) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(stack.size() == 1);
}

FOSSIL_TEST_CASE(cpp_test_stack_class_remove) {
    fossil::tofu::Stack stack("i32");
    fossil::tofu::Tofu tofu("i32", "42");
    stack.insert(tofu);
    ASSUME_ITS_TRUE(stack.remove() == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(stack.is_empty() == true);
}

FOSSIL_TEST_CASE(cpp_test_stack_class_size) {
    fossil::tofu::Stack stack("i32");
    fossil::tofu::Tofu tofu1("i32", "42");
    fossil::tofu::Tofu tofu2("i32", "84");
    stack.insert(tofu1);
    stack.insert(tofu2);
    ASSUME_ITS_TRUE(stack.size() == 2);
}

FOSSIL_TEST_CASE(cpp_test_stack_class_not_empty) {
    fossil::tofu::Stack stack("i32");
    fossil::tofu::Tofu tofu("i32", "42");
    stack.insert(tofu);
    ASSUME_ITS_TRUE(stack.not_empty() == true);
}

FOSSIL_TEST_CASE(cpp_test_stack_class_is_empty) {
    fossil::tofu::Stack stack("i32");
    ASSUME_ITS_TRUE(stack.is_empty() == true);
    fossil::tofu::Tofu tofu("i32", "42");
    stack.insert(tofu);
    ASSUME_ITS_TRUE(stack.is_empty() == false);
}

FOSSIL_TEST_CASE(cpp_test_stack_class_top) {
    fossil::tofu::Stack stack("i32");
    fossil::tofu::Tofu tofu("i32", "42");
    stack.insert(tofu);
    ASSUME_ITS_EQUAL_CSTR(stack.top().get_value().c_str(), "42");
}

FOSSIL_TEST_CASE(cpp_test_stack_class_get) {
    fossil::tofu::Stack stack("i32");
    fossil::tofu::Tofu tofu1("i32", "42");
    fossil::tofu::Tofu tofu2("i32", "84");
    stack.insert(tofu1);
    stack.insert(tofu2);
    ASSUME_ITS_EQUAL_CSTR(stack.get(0).get_value().c_str(), "42");
    ASSUME_ITS_EQUAL_CSTR(stack.get(1).get_value().c_str(), "84");
}

FOSSIL_TEST_CASE(cpp_test_stack_class_set) {
    fossil::tofu::Stack stack("i32");
    fossil::tofu::Tofu tofu1("i32", "42");
    fossil::tofu::Tofu tofu2("i32", "84");
    stack.insert(tofu1);
    stack.set(0, tofu2);
    ASSUME_ITS_EQUAL_CSTR(stack.get(0).get_value().c_str(), "84");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_stack_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_stack_tofu_fixture, cpp_test_stack_class_insert);
    FOSSIL_TEST_ADD(cpp_stack_tofu_fixture, cpp_test_stack_class_remove);
    FOSSIL_TEST_ADD(cpp_stack_tofu_fixture, cpp_test_stack_class_size);
    FOSSIL_TEST_ADD(cpp_stack_tofu_fixture, cpp_test_stack_class_not_empty);
    FOSSIL_TEST_ADD(cpp_stack_tofu_fixture, cpp_test_stack_class_is_empty);
    FOSSIL_TEST_ADD(cpp_stack_tofu_fixture, cpp_test_stack_class_top);
    FOSSIL_TEST_ADD(cpp_stack_tofu_fixture, cpp_test_stack_class_get);
    FOSSIL_TEST_ADD(cpp_stack_tofu_fixture, cpp_test_stack_class_set);

    FOSSIL_TEST_REGISTER(cpp_stack_tofu_fixture);
} // end of tests
