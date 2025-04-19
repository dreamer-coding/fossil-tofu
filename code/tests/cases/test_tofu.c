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

FOSSIL_TEST_SUITE(c_generic_tofu_fixture);

FOSSIL_SETUP(c_generic_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(c_generic_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(c_test_create_destroy_u8) {
    fossil_tofu_t tofu = fossil_tofu_create("u8", "255");
    ASSUME_ITS_TRUE(tofu.type == FOSSIL_TOFU_TYPE_U8);
    ASSUME_ITS_EQUAL_CSTR(tofu.value.data, "255");
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_create_destroy_float) {
    fossil_tofu_t tofu = fossil_tofu_create("float", "3.14");
    ASSUME_ITS_TRUE(tofu.type == FOSSIL_TOFU_TYPE_FLOAT);
    ASSUME_ITS_EQUAL_CSTR(tofu.value.data, "3.14");
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_create_default) {
    fossil_tofu_t *tofu = fossil_tofu_create_default();
    ASSUME_ITS_TRUE(tofu->type == FOSSIL_TOFU_TYPE_ANY);
    ASSUME_ITS_EQUAL_CSTR(tofu->value.data, "");
    fossil_tofu_destroy(tofu);
}

FOSSIL_TEST_CASE(c_test_create_copy) {
    fossil_tofu_t tofu = fossil_tofu_create("i16", "32767");
    fossil_tofu_t *copy = fossil_tofu_create_copy(&tofu);
    ASSUME_ITS_TRUE(copy->type == FOSSIL_TOFU_TYPE_I16);
    ASSUME_ITS_EQUAL_CSTR(copy->value.data, "32767");
    fossil_tofu_destroy(&tofu);
    fossil_tofu_destroy(copy);
}

FOSSIL_TEST_CASE(c_test_create_move) {
    fossil_tofu_t tofu = fossil_tofu_create("i32", "2147483647");
    fossil_tofu_t *moved = fossil_tofu_create_move(&tofu);
    ASSUME_ITS_TRUE(moved->type == FOSSIL_TOFU_TYPE_I32);
    ASSUME_ITS_EQUAL_CSTR(moved->value.data, "2147483647");
    ASSUME_ITS_TRUE(tofu.value.data == NULL); // Ensure original is cleared
    fossil_tofu_destroy(moved);
}

FOSSIL_TEST_CASE(c_test_set_get_value) {
    fossil_tofu_t tofu = fossil_tofu_create("cstr", "Hello");
    ASSUME_ITS_EQUAL_CSTR(fossil_tofu_get_value(&tofu), "Hello");
    fossil_tofu_set_value(&tofu, "World");
    ASSUME_ITS_EQUAL_CSTR(fossil_tofu_get_value(&tofu), "World");
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_set_mutable) {
    fossil_tofu_t tofu = fossil_tofu_create("bool", "true");
    ASSUME_ITS_TRUE(fossil_tofu_is_mutable(&tofu));
    fossil_tofu_set_mutable(&tofu, false);
    ASSUME_ITS_FALSE(fossil_tofu_is_mutable(&tofu));
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_equals) {
    fossil_tofu_t tofu1 = fossil_tofu_create("i64", "9223372036854775807");
    fossil_tofu_t tofu2 = fossil_tofu_create("i64", "9223372036854775807");
    ASSUME_ITS_TRUE(fossil_tofu_equals(&tofu1, &tofu2));
    fossil_tofu_set_value(&tofu2, "0");
    ASSUME_ITS_FALSE(fossil_tofu_equals(&tofu1, &tofu2));
    fossil_tofu_destroy(&tofu1);
    fossil_tofu_destroy(&tofu2);
}

FOSSIL_TEST_CASE(c_test_set_attribute) {
    fossil_tofu_t tofu = fossil_tofu_create("i8", "127");
    int result = fossil_tofu_set_attribute(&tofu, "Test", "Test Description", "test_id");
    ASSUME_ITS_TRUE(result == FOSSIL_TOFU_SUCCESS);
    const fossil_tofu_attribute_t *attr = fossil_tofu_get_attribute(&tofu);
    ASSUME_ITS_EQUAL_CSTR(attr->name, "Test");
    ASSUME_ITS_EQUAL_CSTR(attr->description, "Test Description");
    ASSUME_ITS_EQUAL_CSTR(attr->id, "test_id");
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_get_attribute) {
    fossil_tofu_t tofu = fossil_tofu_create("u16", "65535");
    const fossil_tofu_attribute_t *attr = fossil_tofu_get_attribute(&tofu);
    int result = fossil_tofu_set_attribute(&tofu, "Test", "Test Description", "test_id");
    ASSUME_ITS_TRUE(result == FOSSIL_TOFU_SUCCESS);
    attr = fossil_tofu_get_attribute(&tofu);
    ASSUME_ITS_EQUAL_CSTR(attr->name, "Test");
    ASSUME_ITS_EQUAL_CSTR(attr->description, "Test Description");
    ASSUME_ITS_EQUAL_CSTR(attr->id, "test_id");
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_create_empty_type) {
    fossil_tofu_t tofu = fossil_tofu_create("", "123");
    ASSUME_ITS_TRUE(tofu.type == FOSSIL_TOFU_TYPE_ANY);
    ASSUME_ITS_EQUAL_CSTR(tofu.value.data, "123");
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_create_large_value) {
    char large_value[1024];
    memset(large_value, 'A', sizeof(large_value) - 1);
    large_value[sizeof(large_value) - 1] = '\0';

    fossil_tofu_t tofu = fossil_tofu_create("cstr", large_value);
    ASSUME_ITS_TRUE(tofu.type == FOSSIL_TOFU_TYPE_CSTR);
    ASSUME_ITS_EQUAL_CSTR(tofu.value.data, large_value);
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_set_value_large) {
    char large_value[2048];
    memset(large_value, 'B', sizeof(large_value) - 1);
    large_value[sizeof(large_value) - 1] = '\0';

    fossil_tofu_t tofu = fossil_tofu_create("cstr", "Initial");
    int result = fossil_tofu_set_value(&tofu, large_value);
    ASSUME_ITS_TRUE(result == FOSSIL_TOFU_SUCCESS);
    ASSUME_ITS_EQUAL_CSTR(tofu.value.data, large_value);
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_set_mutable_null_tofu) {
    int result = fossil_tofu_set_mutable(NULL, true);
    ASSUME_ITS_TRUE(result == FOSSIL_TOFU_FAILURE);
}

FOSSIL_TEST_CASE(c_test_equals_null_tofu) {
    fossil_tofu_t tofu = fossil_tofu_create("i16", "123");
    ASSUME_ITS_FALSE(fossil_tofu_equals(&tofu, NULL));
    ASSUME_ITS_FALSE(fossil_tofu_equals(NULL, &tofu));
    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_destroy_null_tofu) {
    fossil_tofu_destroy(NULL); // Should not crash
}

FOSSIL_TEST_CASE(c_test_stress_create_destroy) {
    for (int i = 0; i < 1000000; ++i) {
        fossil_tofu_t tofu = fossil_tofu_create("i32", "42");
        ASSUME_ITS_TRUE(tofu.type == FOSSIL_TOFU_TYPE_I32);
        ASSUME_ITS_EQUAL_CSTR(tofu.value.data, "42");
        fossil_tofu_destroy(&tofu);
    }
}

FOSSIL_TEST_CASE(c_test_stress_set_value) {
    fossil_tofu_t tofu = fossil_tofu_create("cstr", "Initial");
    char large_value[1024];
    memset(large_value, 'C', sizeof(large_value) - 1);
    large_value[sizeof(large_value) - 1] = '\0';

    for (int i = 0; i < 100000; ++i) {
        int result = fossil_tofu_set_value(&tofu, large_value);
        ASSUME_ITS_TRUE(result == FOSSIL_TOFU_SUCCESS);
        ASSUME_ITS_EQUAL_CSTR(tofu.value.data, large_value);
    }

    fossil_tofu_destroy(&tofu);
}

FOSSIL_TEST_CASE(c_test_stress_create_copy) {
    fossil_tofu_t tofu = fossil_tofu_create("i16", "12345");

    for (int i = 0; i < 500000; ++i) {
        fossil_tofu_t *copy = fossil_tofu_create_copy(&tofu);
        ASSUME_ITS_TRUE(copy->type == FOSSIL_TOFU_TYPE_I16);
        ASSUME_ITS_EQUAL_CSTR(copy->value.data, "12345");
        fossil_tofu_destroy(copy);
    }

    fossil_tofu_destroy(&tofu);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_generic_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_create_destroy_u8);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_create_destroy_float);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_create_default);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_create_copy);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_create_move);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_set_get_value);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_set_mutable);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_equals);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_set_attribute);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_get_attribute);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_create_empty_type);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_create_large_value);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_set_value_large);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_set_mutable_null_tofu);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_equals_null_tofu);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_destroy_null_tofu);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_stress_create_destroy);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_stress_set_value);
    FOSSIL_TEST_ADD(c_generic_tofu_fixture, c_test_stress_create_copy);

    // Register the test group
    FOSSIL_TEST_REGISTER(c_generic_tofu_fixture);
} // end of tests
