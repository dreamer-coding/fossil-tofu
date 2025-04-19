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

FOSSIL_TEST_SUITE(cpp_setof_tofu_fixture);

FOSSIL_SETUP(cpp_setof_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_setof_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_setof_class_insert) {
    fossil::tofu::SetOf set("i32");
    Tofu tofu("2147483647");
    set.insert(tofu);
    ASSUME_ITS_TRUE(set.size() == 1);
    ASSUME_ITS_TRUE(set.contains(tofu) == true);
}

FOSSIL_TEST_CASE(cpp_test_setof_class_remove) {
    fossil::tofu::SetOf set("i32");
    Tofu tofu("2147483647");
    set.insert(tofu);
    set.remove(tofu);
    ASSUME_ITS_TRUE(set.size() == 0);
    ASSUME_ITS_TRUE(set.contains(tofu) == false);
}

FOSSIL_TEST_CASE(cpp_test_setof_class_contains) {
    fossil::tofu::SetOf set("i32");
    Tofu tofu("2147483647");
    set.insert(tofu);
    ASSUME_ITS_TRUE(set.contains(tofu) == true);
    Tofu tofu_not_in_set("123");
    ASSUME_ITS_TRUE(set.contains(tofu_not_in_set) == false);
}

FOSSIL_TEST_CASE(cpp_test_setof_class_size) {
    fossil::tofu::SetOf set("i32");
    Tofu tofu1("2147483647");
    Tofu tofu2("123");
    set.insert(tofu1);
    set.insert(tofu2);
    ASSUME_ITS_TRUE(set.size() == 2);
}

FOSSIL_TEST_CASE(cpp_test_setof_class_not_empty) {
    fossil::tofu::SetOf set("i32");
    Tofu tofu("2147483647");
    set.insert(tofu);
    ASSUME_ITS_TRUE(set.not_empty() == true);
}

FOSSIL_TEST_CASE(cpp_test_setof_class_is_empty) {
    fossil::tofu::SetOf set("i32");
    ASSUME_ITS_TRUE(set.is_empty() == true);
    Tofu tofu("2147483647");
    set.insert(tofu);
    ASSUME_ITS_TRUE(set.is_empty() == false);
}


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_setof_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_setof_tofu_fixture, cpp_test_setof_class_insert);
    FOSSIL_TEST_ADD(cpp_setof_tofu_fixture, cpp_test_setof_class_remove);
    FOSSIL_TEST_ADD(cpp_setof_tofu_fixture, cpp_test_setof_class_contains);
    FOSSIL_TEST_ADD(cpp_setof_tofu_fixture, cpp_test_setof_class_size);
    FOSSIL_TEST_ADD(cpp_setof_tofu_fixture, cpp_test_setof_class_not_empty);
    FOSSIL_TEST_ADD(cpp_setof_tofu_fixture, cpp_test_setof_class_is_empty);

    FOSSIL_TEST_REGISTER(cpp_setof_tofu_fixture);
} // end of tests
