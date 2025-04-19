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

FOSSIL_TEST_SUITE(cpp_pqueue_tofu_fixture);

FOSSIL_SETUP(cpp_pqueue_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_pqueue_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_pqueue_class_insert) {
    fossil::tofu::PQueue pqueue("i32");
    tofu::Tofu data("i32", "42");
    pqueue.insert(data, 0);
    ASSUME_ITS_TRUE(pqueue.size() == 1);
}

FOSSIL_TEST_CASE(cpp_test_pqueue_class_remove) {
    fossil::tofu::PQueue pqueue("i32");
    tofu::Tofu data("i32", "42");
    pqueue.insert(data, 0);
    pqueue.remove(0);
    ASSUME_ITS_TRUE(pqueue.is_empty());
}

FOSSIL_TEST_CASE(cpp_test_pqueue_class_get_front) {
    fossil::tofu::PQueue pqueue("i32");
    tofu::Tofu data("i32", "42");
    pqueue.insert(data, 0);
    tofu::Tofu front = pqueue.get_front();
    ASSUME_ITS_TRUE(front.get_value() == "42");
}

FOSSIL_TEST_CASE(cpp_test_pqueue_class_get_back) {
    fossil::tofu::PQueue pqueue("i32");
    tofu::Tofu data("i32", "42");
    pqueue.insert(data, 0);
    tofu::Tofu back = pqueue.get_back();
    ASSUME_ITS_TRUE(back.get_value() == "42");
}

FOSSIL_TEST_CASE(cpp_test_pqueue_class_get_at) {
    fossil::tofu::PQueue pqueue("i32");
    tofu::Tofu data("i32", "42");
    pqueue.insert(data, 0);
    tofu::Tofu at = pqueue.get_at(0);
    ASSUME_ITS_TRUE(at.get_value() == "42");
}

FOSSIL_TEST_CASE(cpp_test_pqueue_class_set_front) {
    fossil::tofu::PQueue pqueue("i32");
    tofu::Tofu data("i32", "42");
    pqueue.insert(data, 0);
    tofu::Tofu new_data("i32", "84");
    pqueue.set_front(new_data);
    tofu::Tofu front = pqueue.get_front();
    ASSUME_ITS_TRUE(front.get_value() == "84");
}

FOSSIL_TEST_CASE(cpp_test_pqueue_class_set_back) {
    fossil::tofu::PQueue pqueue("i32");
    tofu::Tofu data("i32", "42");
    pqueue.insert(data, 0);
    tofu::Tofu new_data("i32", "84");
    pqueue.set_back(new_data);
    tofu::Tofu back = pqueue.get_back();
    ASSUME_ITS_TRUE(back.get_value() == "84");
}

FOSSIL_TEST_CASE(cpp_test_pqueue_class_set_at) {
    fossil::tofu::PQueue pqueue("i32");
    tofu::Tofu data("i32", "42");
    pqueue.insert(data, 0);
    tofu::Tofu new_data("i32", "84");
    pqueue.set_at(0, new_data);
    tofu::Tofu at = pqueue.get_at(0);
    ASSUME_ITS_TRUE(at.get_value() == "84");
}

FOSSIL_TEST_CASE(cpp_test_pqueue_class_not_empty) {
    fossil::tofu::PQueue pqueue("i32");
    tofu::Tofu data("i32", "42");
    pqueue.insert(data, 0);
    ASSUME_ITS_TRUE(pqueue.not_empty());
}

FOSSIL_TEST_CASE(cpp_test_pqueue_class_is_empty) {
    fossil::tofu::PQueue pqueue("i32");
    ASSUME_ITS_TRUE(pqueue.is_empty());
}

FOSSIL_TEST_CASE(cpp_test_pqueue_class_not_cnullptr) {
    fossil::tofu::PQueue pqueue("i32");
    ASSUME_ITS_TRUE(pqueue.not_cnullptr());
}

FOSSIL_TEST_CASE(cpp_test_pqueue_class_is_cnullptr) {
    fossil::tofu::PQueue* pqueue = nullptr;
    ASSUME_ITS_TRUE(pqueue == nullptr);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_pqueue_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_insert);
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_remove);
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_get_front);
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_get_back);
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_get_at);
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_set_front);
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_set_back);
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_set_at);
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_not_empty);
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_is_empty);
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_not_cnullptr);
    FOSSIL_TEST_ADD(cpp_pqueue_tofu_fixture, cpp_test_pqueue_class_is_cnullptr);

    FOSSIL_TEST_REGISTER(cpp_pqueue_tofu_fixture);
} // end of tests
