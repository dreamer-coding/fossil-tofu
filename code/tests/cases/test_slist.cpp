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

FOSSIL_TEST_SUITE(cpp_slist_tofu_fixture);

FOSSIL_SETUP(cpp_slist_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_slist_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_slist_class_create_with_type) {
    fossil::tofu::SList slist("i32");
    ASSUME_ITS_TRUE(slist.not_empty() == false);
    ASSUME_ITS_TRUE(slist.is_empty() == true);
}

FOSSIL_TEST_CASE(cpp_test_slist_class_create_default) {
    fossil::tofu::SList slist;
    ASSUME_ITS_TRUE(slist.not_empty() == false);
    ASSUME_ITS_TRUE(slist.is_empty() == true);
}

FOSSIL_TEST_CASE(cpp_test_slist_class_insert) {
    fossil::tofu::SList slist("i32");
    fossil::tofu::Tofu tofu("i32", "42");
    ASSUME_ITS_TRUE(slist.insert(tofu) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(slist.size() == 1);
}

FOSSIL_TEST_CASE(cpp_test_slist_class_remove) {
    fossil::tofu::SList slist("i32");
    fossil::tofu::Tofu tofu("i32", "42");
    slist.insert(tofu);
    ASSUME_ITS_TRUE(slist.remove(tofu) == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_TRUE(slist.is_empty() == true);
}

FOSSIL_TEST_CASE(cpp_test_slist_class_search) {
    fossil::tofu::SList slist("i32");
    fossil::tofu::Tofu tofu("i32", "42");
    slist.insert(tofu);
    fossil::tofu::Tofu result = slist.search(tofu);
    ASSUME_ITS_TRUE(result.get_value() == "42");
}

FOSSIL_TEST_CASE(cpp_test_slist_class_get_front) {
    fossil::tofu::SList slist("i32");
    fossil::tofu::Tofu tofu("i32", "42");
    slist.insert(tofu);
    fossil::tofu::Tofu front = slist.get_front();
    ASSUME_ITS_TRUE(front.get_value() == "42");
}

FOSSIL_TEST_CASE(cpp_test_slist_class_get_back) {
    fossil::tofu::SList slist("i32");
    fossil::tofu::Tofu tofu("i32", "42");
    slist.insert(tofu);
    fossil::tofu::Tofu back = slist.get_back();
    ASSUME_ITS_TRUE(back.get_value() == "42");
}

FOSSIL_TEST_CASE(cpp_test_slist_class_multiple_insertions) {
    fossil::tofu::SList slist("i32");
    fossil::tofu::Tofu tofu1("i32", "42");
    fossil::tofu::Tofu tofu2("i32", "84");
    slist.insert(tofu1);
    slist.insert(tofu2);
    ASSUME_ITS_TRUE(slist.size() == 2);
    ASSUME_ITS_TRUE(slist.not_empty() == true);
}

FOSSIL_TEST_CASE(cpp_test_slist_class_empty_after_clear) {
    fossil::tofu::SList slist("i32");
    fossil::tofu::Tofu tofu("i32", "42");
    slist.insert(tofu);
    slist.remove(tofu);
    ASSUME_ITS_TRUE(slist.is_empty() == true);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_slist_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_slist_tofu_fixture, cpp_test_slist_class_create_with_type);
    FOSSIL_TEST_ADD(cpp_slist_tofu_fixture, cpp_test_slist_class_create_default);
    FOSSIL_TEST_ADD(cpp_slist_tofu_fixture, cpp_test_slist_class_insert);
    FOSSIL_TEST_ADD(cpp_slist_tofu_fixture, cpp_test_slist_class_remove);
    FOSSIL_TEST_ADD(cpp_slist_tofu_fixture, cpp_test_slist_class_search);
    FOSSIL_TEST_ADD(cpp_slist_tofu_fixture, cpp_test_slist_class_get_front);
    FOSSIL_TEST_ADD(cpp_slist_tofu_fixture, cpp_test_slist_class_get_back);
    FOSSIL_TEST_ADD(cpp_slist_tofu_fixture, cpp_test_slist_class_multiple_insertions);
    FOSSIL_TEST_ADD(cpp_slist_tofu_fixture, cpp_test_slist_class_empty_after_clear);

    FOSSIL_TEST_REGISTER(cpp_slist_tofu_fixture);
} // end of tests
