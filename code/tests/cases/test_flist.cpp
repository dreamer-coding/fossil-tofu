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

FOSSIL_TEST_SUITE(cpp_flist_tofu_fixture);

FOSSIL_SETUP(cpp_flist_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_flist_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_flist_insert_and_get) {
    fossil::tofu::FList flist("any");
    flist.insert(tofu::Tofu("any", "value1"));
    flist.insert(tofu::Tofu("any", "value2"));
    flist.insert(tofu::Tofu("any", "value3"));

    ASSUME_ITS_TRUE(flist.size() == 3);
    ASSUME_ITS_TRUE(flist.get(0).get_value() == "value1");
    ASSUME_ITS_TRUE(flist.get(1).get_value() == "value2");
    ASSUME_ITS_TRUE(flist.get(2).get_value() == "value3");
}

FOSSIL_TEST_CASE(cpp_test_flist_set_and_get) {
    fossil::tofu::FList flist("any");
    flist.insert(tofu::Tofu("any", "value1"));
    flist.insert(tofu::Tofu("any", "value2"));
    flist.insert(tofu::Tofu("any", "value3"));

    flist.set(1, tofu::Tofu("any", "new_value"));
    ASSUME_ITS_TRUE(flist.get(1).get_value() == "new_value");
}

FOSSIL_TEST_CASE(cpp_test_flist_reverse_forward) {
    fossil::tofu::FList flist("any");
    flist.insert(tofu::Tofu("any", "value1"));
    flist.insert(tofu::Tofu("any", "value2"));
    flist.insert(tofu::Tofu("any", "value3"));

    flist.reverse_forward();
    ASSUME_ITS_TRUE(flist.get(0).get_value() == "value3");
    ASSUME_ITS_TRUE(flist.get(1).get_value() == "value2");
    ASSUME_ITS_TRUE(flist.get(2).get_value() == "value1");
}

FOSSIL_TEST_CASE(cpp_test_flist_reverse_backward) {
    fossil::tofu::FList flist("any");
    flist.insert(tofu::Tofu("any", "value1"));
    flist.insert(tofu::Tofu("any", "value2"));
    flist.insert(tofu::Tofu("any", "value3"));

    flist.reverse_backward();
    ASSUME_ITS_TRUE(flist.get(0).get_value() == "value3");
    ASSUME_ITS_TRUE(flist.get(1).get_value() == "value2");
    ASSUME_ITS_TRUE(flist.get(2).get_value() == "value1");
}

FOSSIL_TEST_CASE(cpp_test_flist_front_and_back) {
    fossil::tofu::FList flist("any");
    flist.insert(tofu::Tofu("any", "value1"));
    flist.insert(tofu::Tofu("any", "value2"));
    flist.insert(tofu::Tofu("any", "value3"));

    ASSUME_ITS_TRUE(flist.front().get_value() == "value1");
    ASSUME_ITS_TRUE(flist.back().get_value() == "value3");
}

FOSSIL_TEST_CASE(cpp_test_flist_set_front_and_back) {
    fossil::tofu::FList flist("any");
    flist.insert(tofu::Tofu("any", "value1"));
    flist.insert(tofu::Tofu("any", "value2"));
    flist.insert(tofu::Tofu("any", "value3"));

    flist.set_front(tofu::Tofu("any", "new_front"));
    flist.set_back(tofu::Tofu("any", "new_back"));

    ASSUME_ITS_TRUE(flist.front().get_value() == "new_front");
    ASSUME_ITS_TRUE(flist.back().get_value() == "new_back");
}

FOSSIL_TEST_CASE(cpp_test_flist_is_empty) {
    fossil::tofu::FList flist("any");
    ASSUME_ITS_TRUE(flist.size() == 0);
    ASSUME_ITS_TRUE(!flist.not_empty());

    flist.insert(tofu::Tofu("any", "value1"));
    ASSUME_ITS_TRUE(flist.not_empty());
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_flist_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_flist_tofu_fixture, cpp_test_flist_insert_and_get);
    FOSSIL_TEST_ADD(cpp_flist_tofu_fixture, cpp_test_flist_set_and_get);
    FOSSIL_TEST_ADD(cpp_flist_tofu_fixture, cpp_test_flist_reverse_forward);
    FOSSIL_TEST_ADD(cpp_flist_tofu_fixture, cpp_test_flist_reverse_backward);
    FOSSIL_TEST_ADD(cpp_flist_tofu_fixture, cpp_test_flist_front_and_back);
    FOSSIL_TEST_ADD(cpp_flist_tofu_fixture, cpp_test_flist_set_front_and_back);
    FOSSIL_TEST_ADD(cpp_flist_tofu_fixture, cpp_test_flist_is_empty);

    FOSSIL_TEST_REGISTER(cpp_flist_tofu_fixture);
} // end of tests
