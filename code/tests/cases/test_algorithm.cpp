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

FOSSIL_TEST_SUITE(cpp_algorithm_fixture);

FOSSIL_SETUP(cpp_algorithm_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_algorithm_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_algorithm_class_compare) {
    fossil::tofu::Tofu tofu1("i8", "42");
    fossil::tofu::Tofu tofu2("i8", "84");
    ASSUME_ITS_TRUE(fossil::tofu::Algorithm::compare(tofu1, tofu2) < 0);
}

FOSSIL_TEST_CASE(cpp_test_algorithm_class_search) {
    std::vector<fossil::tofu::Tofu> array = {
        fossil::tofu::Tofu("i8", "42"),
        fossil::tofu::Tofu("i8", "84"),
        fossil::tofu::Tofu("i8", "126")
    };
    fossil::tofu::Tofu tofu("i8", "84");
    ASSUME_ITS_TRUE(fossil::tofu::Algorithm::search(array, tofu) == 1);
}

FOSSIL_TEST_CASE(cpp_test_algorithm_class_sort_ascending) {
    std::vector<fossil::tofu::Tofu> array = {
        fossil::tofu::Tofu("i8", "126"),
        fossil::tofu::Tofu("i8", "42"),
        fossil::tofu::Tofu("i8", "84")
    };
    fossil::tofu::Algorithm::sort(array, true);
    ASSUME_ITS_EQUAL_CSTR(array[0].value().data, "42");
    ASSUME_ITS_EQUAL_CSTR(array[1].value().data, "84");
    ASSUME_ITS_EQUAL_CSTR(array[2].value().data, "126");
}

FOSSIL_TEST_CASE(cpp_test_algorithm_class_sort_descending) {
    std::vector<fossil::tofu::Tofu> array = {
        fossil::tofu::Tofu("i8", "42"),
        fossil::tofu::Tofu("i8", "126"),
        fossil::tofu::Tofu("i8", "84")
    };
    fossil::tofu::Algorithm::sort(array, false);
    ASSUME_ITS_EQUAL_CSTR(array[0].value().data, "126");
    ASSUME_ITS_EQUAL_CSTR(array[1].value().data, "84");
    ASSUME_ITS_EQUAL_CSTR(array[2].value().data, "42");
}

FOSSIL_TEST_CASE(cpp_test_algorithm_class_reverse) {
    std::vector<fossil::tofu::Tofu> array = {
        fossil::tofu::Tofu("i8", "42"),
        fossil::tofu::Tofu("i8", "84"),
        fossil::tofu::Tofu("i8", "126")
    };
    fossil::tofu::Algorithm::reverse(array);
    ASSUME_ITS_EQUAL_CSTR(array[0].value().data, "126");
    ASSUME_ITS_EQUAL_CSTR(array[1].value().data, "84");
    ASSUME_ITS_EQUAL_CSTR(array[2].value().data, "42");
}

FOSSIL_TEST_CASE(cpp_test_algorithm_class_min) {
    std::vector<fossil::tofu::Tofu> array = {
        fossil::tofu::Tofu("i8", "126"),
        fossil::tofu::Tofu("i8", "42"),
        fossil::tofu::Tofu("i8", "84")
    };
    fossil::tofu::Tofu min = fossil::tofu::Algorithm::min(array);
    ASSUME_ITS_EQUAL_CSTR(min.value().data, "42");
}

FOSSIL_TEST_CASE(cpp_test_algorithm_class_max) {
    std::vector<fossil::tofu::Tofu> array = {
        fossil::tofu::Tofu("i8", "42"),
        fossil::tofu::Tofu("i8", "84"),
        fossil::tofu::Tofu("i8", "126")
    };
    fossil::tofu::Tofu max = fossil::tofu::Algorithm::max(array);
    ASSUME_ITS_EQUAL_CSTR(max.value().data, "126");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_algorithm_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_algorithm_class_compare);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_algorithm_class_search);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_algorithm_class_sort_ascending);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_algorithm_class_sort_descending);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_algorithm_class_reverse);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_algorithm_class_min);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_algorithm_class_max);

    // Register the fixture
    FOSSIL_TEST_REGISTER(cpp_algorithm_fixture);
} // end of tests
