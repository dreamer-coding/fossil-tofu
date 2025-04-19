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

FOSSIL_TEST_SUITE(cpp_dqueue_tofu_fixture);

FOSSIL_SETUP(cpp_dqueue_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_dqueue_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_dqueue_class_insert) {
    fossil::tofu::DQueue queue;
    fossil::tofu::Tofu tofu("cstr", "test_value");
    queue.insert(tofu);
    ASSUME_ITS_TRUE(queue.size() == 1);
    ASSUME_ITS_TRUE(queue.get_front().get_value() == "test_value");
}

FOSSIL_TEST_CASE(cpp_test_dqueue_class_remove) {
    fossil::tofu::DQueue queue;
    fossil::tofu::Tofu tofu("cstr", "test_value");
    queue.insert(tofu);
    queue.remove();
    ASSUME_ITS_TRUE(queue.size() == 0);
    ASSUME_ITS_TRUE(queue.not_empty() == false);
}

FOSSIL_TEST_CASE(cpp_test_dqueue_class_get) {
    fossil::tofu::DQueue queue;
    fossil::tofu::Tofu tofu1("cstr", "value1");
    fossil::tofu::Tofu tofu2("cstr", "value2");
    queue.insert(tofu1);
    queue.insert(tofu2);
    ASSUME_ITS_TRUE(queue.get(0).get_value() == "value1");
    ASSUME_ITS_TRUE(queue.get(1).get_value() == "value2");
}

FOSSIL_TEST_CASE(cpp_test_dqueue_class_get_front_back) {
    fossil::tofu::DQueue queue;
    fossil::tofu::Tofu tofu1("cstr", "front_value");
    fossil::tofu::Tofu tofu2("cstr", "back_value");
    queue.insert(tofu1);
    queue.insert(tofu2);
    ASSUME_ITS_TRUE(queue.get_front().get_value() == "front_value");
    ASSUME_ITS_TRUE(queue.get_back().get_value() == "back_value");
}

FOSSIL_TEST_CASE(cpp_test_dqueue_class_multiple_operations) {
    fossil::tofu::DQueue queue;
    fossil::tofu::Tofu tofu1("cstr", "value1");
    fossil::tofu::Tofu tofu2("cstr", "value2");
    queue.insert(tofu1);
    queue.insert(tofu2);
    queue.remove();
    ASSUME_ITS_TRUE(queue.size() == 1);
    ASSUME_ITS_TRUE(queue.get_front().get_value() == "value2");
}

FOSSIL_TEST_CASE(cpp_test_dqueue_class_empty_queue) {
    fossil::tofu::DQueue queue;
    ASSUME_ITS_TRUE(queue.size() == 0);
    ASSUME_ITS_TRUE(queue.not_empty() == false);
    try {
        queue.get_front();
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::runtime_error&) {
        ASSUME_ITS_TRUE(true);
    }
}

FOSSIL_TEST_CASE(cpp_test_dqueue_class_copy_constructor) {
    fossil::tofu::DQueue queue1;
    fossil::tofu::Tofu tofu("cstr", "value");
    queue1.insert(tofu);
    fossil::tofu::DQueue queue2(queue1);
    ASSUME_ITS_TRUE(queue2.size() == 1);
    ASSUME_ITS_TRUE(queue2.get_front().get_value() == "value");
}

FOSSIL_TEST_CASE(cpp_test_dqueue_class_move_constructor) {
    fossil::tofu::DQueue queue1;
    fossil::tofu::Tofu tofu("cstr", "value");
    queue1.insert(tofu);
    fossil::tofu::DQueue queue2(std::move(queue1));
    ASSUME_ITS_TRUE(queue2.size() == 1);
    ASSUME_ITS_TRUE(queue2.get_front().get_value() == "value");
    ASSUME_ITS_TRUE(queue1.size() == 0); // Moved-from queue should be empty
}

FOSSIL_TEST_CASE(cpp_test_dqueue_class_copy_assignment) {
    fossil::tofu::DQueue queue1;
    fossil::tofu::Tofu tofu("cstr", "value");
    queue1.insert(tofu);
    fossil::tofu::DQueue queue2;
    queue2 = queue1;
    ASSUME_ITS_TRUE(queue2.size() == 1);
    ASSUME_ITS_TRUE(queue2.get_front().get_value() == "value");
}

FOSSIL_TEST_CASE(cpp_test_dqueue_class_move_assignment) {
    fossil::tofu::DQueue queue1;
    fossil::tofu::Tofu tofu("cstr", "value");
    queue1.insert(tofu);
    fossil::tofu::DQueue queue2;
    queue2 = std::move(queue1);
    ASSUME_ITS_TRUE(queue2.size() == 1);
    ASSUME_ITS_TRUE(queue2.get_front().get_value() == "value");
    ASSUME_ITS_TRUE(queue1.size() == 0); // Moved-from queue should be empty
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_dqueue_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_dqueue_tofu_fixture, cpp_test_dqueue_class_insert);
    FOSSIL_TEST_ADD(cpp_dqueue_tofu_fixture, cpp_test_dqueue_class_remove);
    FOSSIL_TEST_ADD(cpp_dqueue_tofu_fixture, cpp_test_dqueue_class_get);
    FOSSIL_TEST_ADD(cpp_dqueue_tofu_fixture, cpp_test_dqueue_class_get_front_back);
    FOSSIL_TEST_ADD(cpp_dqueue_tofu_fixture, cpp_test_dqueue_class_multiple_operations);
    FOSSIL_TEST_ADD(cpp_dqueue_tofu_fixture, cpp_test_dqueue_class_empty_queue);
    FOSSIL_TEST_ADD(cpp_dqueue_tofu_fixture, cpp_test_dqueue_class_copy_constructor);
    FOSSIL_TEST_ADD(cpp_dqueue_tofu_fixture, cpp_test_dqueue_class_move_constructor);
    FOSSIL_TEST_ADD(cpp_dqueue_tofu_fixture, cpp_test_dqueue_class_copy_assignment);
    FOSSIL_TEST_ADD(cpp_dqueue_tofu_fixture, cpp_test_dqueue_class_move_assignment);

    FOSSIL_TEST_REGISTER(cpp_dqueue_tofu_fixture);
} // end of tests
