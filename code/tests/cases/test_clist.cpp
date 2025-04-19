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

FOSSIL_TEST_SUITE(cpp_clist_tofu_fixture);

FOSSIL_SETUP(cpp_clist_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_clist_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_clist_get) {
    fossil::tofu::CList clist("i32");
    clist.insert(fossil::tofu::Tofu("cstr", "42"));
    clist.insert(fossil::tofu::Tofu("cstr", "84"));
    ASSUME_ITS_EQUAL_STR(clist.get(0).get_value().c_str(), "42");
    ASSUME_ITS_EQUAL_STR(clist.get(1).get_value().c_str(), "84");
}

FOSSIL_TEST_CASE(cpp_test_clist_get_front) {
    fossil::tofu::CList clist("i32");
    clist.insert(fossil::tofu::Tofu("cstr", "42"));
    clist.insert(fossil::tofu::Tofu("cstr", "84"));
    ASSUME_ITS_EQUAL_STR(clist.get_front().get_value().c_str(), "42");
}

FOSSIL_TEST_CASE(cpp_test_clist_get_back) {
    fossil::tofu::CList clist("i32");
    clist.insert(fossil::tofu::Tofu("cstr", "42"));
    clist.insert(fossil::tofu::Tofu("cstr", "84"));
    ASSUME_ITS_EQUAL_STR(clist.get_back().get_value().c_str(), "84");
}

FOSSIL_TEST_CASE(cpp_test_clist_set) {
    fossil::tofu::CList clist("i32");
    clist.insert(fossil::tofu::Tofu("cstr", "42"));
    clist.set(0, fossil::tofu::Tofu("cstr", "84"));
    ASSUME_ITS_EQUAL_STR(clist.get(0).get_value().c_str(), "84");
}

FOSSIL_TEST_CASE(cpp_test_clist_set_front) {
    fossil::tofu::CList clist("i32");
    clist.insert(fossil::tofu::Tofu("cstr", "42"));
    clist.insert(fossil::tofu::Tofu("cstr", "84"));
    clist.set_front(fossil::tofu::Tofu("cstr", "21"));
    ASSUME_ITS_EQUAL_STR(clist.get_front().get_value().c_str(), "21");
}

FOSSIL_TEST_CASE(cpp_test_clist_set_back) {
    fossil::tofu::CList clist("i32");
    clist.insert(fossil::tofu::Tofu("cstr", "42"));
    clist.insert(fossil::tofu::Tofu("cstr", "84"));
    clist.set_back(fossil::tofu::Tofu("cstr", "168"));
    ASSUME_ITS_EQUAL_STR(clist.get_back().get_value().c_str(), "168");
}

FOSSIL_TEST_CASE(cpp_test_clist_copy_constructor) {
    fossil::tofu::CList clist1("i32");
    clist1.insert(fossil::tofu::Tofu("cstr", "42"));
    fossil::tofu::CList clist2(clist1);
    ASSUME_ITS_EQUAL_STR(clist2.get(0).get_value().c_str(), "42");
}

FOSSIL_TEST_CASE(cpp_test_clist_move_constructor) {
    fossil::tofu::CList clist1("i32");
    clist1.insert(fossil::tofu::Tofu("cstr", "42"));
    fossil::tofu::CList clist2(std::move(clist1));
    ASSUME_ITS_EQUAL_STR(clist2.get(0).get_value().c_str(), "42");
    ASSUME_ITS_TRUE(clist1.size() == 0); // clist1 should be empty after move
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_clist_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_clist_tofu_fixture, cpp_test_clist_get);
    FOSSIL_TEST_ADD(cpp_clist_tofu_fixture, cpp_test_clist_get_front);
    FOSSIL_TEST_ADD(cpp_clist_tofu_fixture, cpp_test_clist_get_back);
    FOSSIL_TEST_ADD(cpp_clist_tofu_fixture, cpp_test_clist_set);
    FOSSIL_TEST_ADD(cpp_clist_tofu_fixture, cpp_test_clist_set_front);
    FOSSIL_TEST_ADD(cpp_clist_tofu_fixture, cpp_test_clist_set_back);
    FOSSIL_TEST_ADD(cpp_clist_tofu_fixture, cpp_test_clist_copy_constructor);
    FOSSIL_TEST_ADD(cpp_clist_tofu_fixture, cpp_test_clist_move_constructor);

    FOSSIL_TEST_REGISTER(cpp_clist_tofu_fixture);
} // end of tests
