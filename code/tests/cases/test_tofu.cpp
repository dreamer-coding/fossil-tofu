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

FOSSIL_TEST_SUITE(cpp_generic_tofu_fixture);

FOSSIL_SETUP(cpp_generic_tofu_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_generic_tofu_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_test_tofu_constructor) {
    fossil::tofu::Tofu tofu("i32", "42");
    ASSUME_ITS_EQUAL_CSTR(tofu.get_value().c_str(), "42");
    ASSUME_ITS_EQUAL_CSTR(tofu.get_type_name().c_str(), "i32");
}

FOSSIL_TEST_CASE(cpp_test_tofu_copy_constructor) {
    fossil::tofu::Tofu tofu1("i32", "42");
    fossil::tofu::Tofu tofu2(tofu1);
    ASSUME_ITS_TRUE(tofu1 == tofu2);
}

FOSSIL_TEST_CASE(cpp_test_tofu_move_constructor) {
    fossil::tofu::Tofu tofu1("i32", "42");
    fossil::tofu::Tofu tofu2(std::move(tofu1));
    ASSUME_ITS_EQUAL_CSTR(tofu2.get_value().c_str(), "42");
}

FOSSIL_TEST_CASE(cpp_test_tofu_assignment_operator) {
    fossil::tofu::Tofu tofu1("i32", "42");
    fossil::tofu::Tofu tofu2("i8", "127");
    tofu2 = tofu1;
    ASSUME_ITS_TRUE(tofu1 == tofu2);
}

FOSSIL_TEST_CASE(cpp_test_tofu_set_value) {
    fossil::tofu::Tofu tofu("i32", "42");
    tofu.set_value("100");
    ASSUME_ITS_EQUAL_CSTR(tofu.get_value().c_str(), "100");
}

FOSSIL_TEST_CASE(cpp_test_tofu_set_mutable) {
    fossil::tofu::Tofu tofu("i32", "42");
    tofu.set_mutable(true);
    ASSUME_ITS_TRUE(tofu.is_mutable());
}

FOSSIL_TEST_CASE(cpp_test_tofu_set_attribute) {
    fossil::tofu::Tofu tofu("i32", "42");
    tofu.set_attribute("Test Attribute", "Test Description", "cpp_test_id");
    const fossil_tofu_attribute_t* attr = tofu.get_attribute();
    ASSUME_ITS_EQUAL_CSTR(attr->name, "Test Attribute");
    ASSUME_ITS_EQUAL_CSTR(attr->description, "Test Description");
    ASSUME_ITS_EQUAL_CSTR(attr->id, "cpp_test_id");
}

FOSSIL_TEST_CASE(cpp_test_tofu_equals_operator) {
    fossil::tofu::Tofu tofu1("i32", "42");
    fossil::tofu::Tofu tofu2("i32", "42");
    ASSUME_ITS_TRUE(tofu1 == tofu2);
}

FOSSIL_TEST_CASE(cpp_test_tofu_not_equals_operator) {
    fossil::tofu::Tofu tofu1("i32", "42");
    fossil::tofu::Tofu tofu2("i32", "100");
    ASSUME_ITS_TRUE(tofu1 != tofu2);
}

FOSSIL_TEST_CASE(cpp_test_tofu_display) {
    fossil::tofu::Tofu tofu("i32", "42");
    tofu.display(); // Ensure no runtime errors occur during display
}

FOSSIL_TEST_CASE(cpp_test_tofu_create_default) {
    fossil::tofu::Tofu tofu = fossil::tofu::Tofu::create_default();
    ASSUME_ITS_TRUE(!tofu.get_value().empty());
}

FOSSIL_TEST_CASE(cpp_test_tofu_validate_type) {
    fossil::tofu::Tofu tofu = fossil::tofu::Tofu::validate_type("i32");
    ASSUME_ITS_EQUAL_CSTR(tofu.get_type_name().c_str(), "i32");
}

FOSSIL_TEST_CASE(cpp_test_tofu_edge_case_empty_value) {
    fossil::tofu::Tofu tofu("i32", "");
    ASSUME_ITS_EQUAL_CSTR(tofu.get_value().c_str(), "");
    ASSUME_ITS_EQUAL_CSTR(tofu.get_type_name().c_str(), "i32");
}

FOSSIL_TEST_CASE(cpp_test_tofu_edge_case_invalid_type) {
    try {
        fossil::tofu::Tofu tofu("invalid_type", "42");
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        ASSUME_ITS_TRUE(true); // Exception expected
    }
}

FOSSIL_TEST_CASE(cpp_test_tofu_edge_case_large_value) {
    std::string large_value(10000, '9'); // Very large value
    fossil::tofu::Tofu tofu("i64", large_value.c_str());
    ASSUME_ITS_EQUAL_CSTR(tofu.get_value().c_str(), large_value.c_str());
}

FOSSIL_TEST_CASE(cpp_test_tofu_edge_case_null_value) {
    try {
        fossil::tofu::Tofu tofu("i32", nullptr);
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        ASSUME_ITS_TRUE(true); // Exception expected
    }
}

FOSSIL_TEST_CASE(cpp_test_tofu_edge_case_empty_type) {
    try {
        fossil::tofu::Tofu tofu("", "42");
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        ASSUME_ITS_TRUE(true); // Exception expected
    }
}

FOSSIL_TEST_CASE(cpp_test_tofu_cycle_through_types) {
    const char* type_ids[] = {
        "i8", "i16", "i32", "i64", "u8", "u16", "u32", "u64",
        "hex", "octal", "float", "double", "wstr", "cstr",
        "cchar", "wchar", "bool", "size", "any"
    };

    const char* test_value = "test_value";

    for (const char* type_id : type_ids) {
        fossil::tofu::Tofu tofu(type_id, test_value);
        ASSUME_ITS_EQUAL_CSTR(tofu.get_type_name().c_str(), type_id);
        ASSUME_ITS_EQUAL_CSTR(tofu.get_value().c_str(), test_value);
    }
}

FOSSIL_TEST_CASE(cpp_test_tofu_edge_case_invalid_type) {
    try {
        fossil::tofu::Tofu tofu("invalid_type", "42");
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        ASSUME_ITS_TRUE(true); // Exception expected
    }
}

FOSSIL_TEST_CASE(cpp_test_tofu_edge_case_large_value) {
    std::string large_value(10000, '9'); // Very large value
    fossil::tofu::Tofu tofu("i64", large_value.c_str());
    ASSUME_ITS_EQUAL_CSTR(tofu.get_value().c_str(), large_value.c_str());
}

FOSSIL_TEST_CASE(cpp_test_tofu_edge_case_null_value) {
    try {
        fossil::tofu::Tofu tofu("i32", nullptr);
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        ASSUME_ITS_TRUE(true); // Exception expected
    }
}

FOSSIL_TEST_CASE(cpp_test_tofu_edge_case_empty_type) {
    try {
        fossil::tofu::Tofu tofu("", "42");
        ASSUME_ITS_TRUE(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        ASSUME_ITS_TRUE(true); // Exception expected
    }
}

FOSSIL_TEST_CASE(cpp_test_tofu_cycle_through_types) {
    const char* type_ids[] = {
        "i8", "i16", "i32", "i64", "u8", "u16", "u32", "u64",
        "hex", "octal", "float", "double", "wstr", "cstr",
        "cchar", "wchar", "bool", "size", "any"
    };

    const char* test_value = "test_value";

    for (const char* type_id : type_ids) {
        fossil::tofu::Tofu tofu(type_id, test_value);
        ASSUME_ITS_EQUAL_CSTR(tofu.get_type_name().c_str(), type_id);
        ASSUME_ITS_EQUAL_CSTR(tofu.get_value().c_str(), test_value);
    }
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_generic_tofu_tests) {    
    // Generic ToFu Fixture
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_constructor);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_copy_constructor);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_move_constructor);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_assignment_operator);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_set_value);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_set_mutable);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_set_attribute);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_equals_operator);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_not_equals_operator);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_display);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_create_default);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_validate_type);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_edge_case_empty_value);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_edge_case_invalid_type);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_edge_case_large_value);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_edge_case_null_value);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_edge_case_empty_type);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_cycle_through_types);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_edge_case_invalid_type);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_edge_case_large_value);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_edge_case_null_value);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_edge_case_empty_type);
    FOSSIL_TEST_ADD(cpp_generic_tofu_fixture, cpp_test_tofu_cycle_through_types);

    // Register the test group
    FOSSIL_TEST_REGISTER(cpp_generic_tofu_fixture);
} // end of tests
