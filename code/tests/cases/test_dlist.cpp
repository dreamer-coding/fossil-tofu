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

FOSSIL_TEST_SUITE(cpp_dlist_tofu_fixture);

FOSSIL_SETUP(cpp_dlist_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_dlist_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_dlist_get) {
    fossil::tofu::DList dlist("i32");
    dlist.insert(Tofu("cstr", "10"));
    dlist.insert(Tofu("cstr", "20"));
    dlist.insert(Tofu("cstr", "30"));

    Tofu value = dlist.get(1);
    ASSUME_ITS_TRUE(value.get_value() == "20");
}

FOSSIL_TEST_CASE(cpp_test_dlist_get_front) {
    fossil::tofu::DList dlist("i32");
    dlist.insert(Tofu("cstr", "10"));
    dlist.insert(Tofu("cstr", "20"));

    Tofu value = dlist.get_front();
    ASSUME_ITS_TRUE(value.get_value() == "10");
}

FOSSIL_TEST_CASE(cpp_test_dlist_get_back) {
    fossil::tofu::DList dlist("i32");
    dlist.insert(Tofu("cstr", "10"));
    dlist.insert(Tofu("cstr", "20"));

    Tofu value = dlist.get_back();
    ASSUME_ITS_TRUE(value.get_value() == "20");
}

FOSSIL_TEST_CASE(cpp_test_dlist_set) {
    fossil::tofu::DList dlist("i32");
    dlist.insert(Tofu("cstr", "10"));
    dlist.insert(Tofu("cstr", "20"));

    dlist.set(1, Tofu("cstr", "30"));
    Tofu value = dlist.get(1);
    ASSUME_ITS_TRUE(value.get_value() == "30");
}

FOSSIL_TEST_CASE(cpp_test_dlist_set_front) {
    fossil::tofu::DList dlist("i32");
    dlist.insert(Tofu("cstr", "10"));
    dlist.insert(Tofu("cstr", "20"));

    dlist.set_front(Tofu("cstr", "30"));
    Tofu value = dlist.get_front();
    ASSUME_ITS_TRUE(value.get_value() == "30");
}

FOSSIL_TEST_CASE(cpp_test_dlist_set_back) {
    fossil::tofu::DList dlist("i32");
    dlist.insert(Tofu("cstr", "10"));
    dlist.insert(Tofu("cstr", "20"));

    dlist.set_back(Tofu("cstr", "30"));
    Tofu value = dlist.get_back();
    ASSUME_ITS_TRUE(value.get_value() == "30");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_dlist_tofu_tests) {
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_dlist_tofu_fixture, cpp_test_dlist_get);
    FOSSIL_TEST_ADD(cpp_dlist_tofu_fixture, cpp_test_dlist_get_front);
    FOSSIL_TEST_ADD(cpp_dlist_tofu_fixture, cpp_test_dlist_get_back);
    FOSSIL_TEST_ADD(cpp_dlist_tofu_fixture, cpp_test_dlist_set);
    FOSSIL_TEST_ADD(cpp_dlist_tofu_fixture, cpp_test_dlist_set_front);
    FOSSIL_TEST_ADD(cpp_dlist_tofu_fixture, cpp_test_dlist_set_back);

    FOSSIL_TEST_REGISTER(cpp_dlist_tofu_fixture);
} // end of tests
