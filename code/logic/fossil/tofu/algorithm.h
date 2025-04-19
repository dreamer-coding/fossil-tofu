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
#ifndef fossil_algorithm_H
#define fossil_algorithm_H

#include "tofu.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Function to compare two `fossil_tofu_t` objects.
 *
 * @param tofu1 The first `fossil_tofu_t` object.
 * @param tofu2 The second `fossil_tofu_t` object.
 * @return A negative value if tofu1 < tofu2, 0 if tofu1 == tofu2, or a positive value if tofu1 > tofu2.
 */
int fossil_algorithm_compare(const fossil_tofu_t *tofu1, const fossil_tofu_t *tofu2);

/**
 * Function to search for a `fossil_tofu_t` object in an array of `fossil_tofu_t` objects.
 *
 * @param array The array of `fossil_tofu_t` objects.
 * @param size The number of elements in the array.
 * @param tofu The `fossil_tofu_t` object to search for.
 * @return The index of the tofu object if found, or -1 if not found.
 */
int fossil_algorithm_search(const fossil_tofu_t *array, size_t size, const fossil_tofu_t *tofu);

/**
 * Function to sort an array of `fossil_tofu_t` objects based on their values.
 *
 * @param array The array of `fossil_tofu_t` objects.
 * @param size The number of elements in the array.
 * @param ascending A boolean flag to indicate sorting order: `true` for ascending, `false` for descending.
 * @return `FOSSIL_TOFU_SUCCESS` if sorting is successful, or `FOSSIL_TOFU_FAILURE` if an error occurs.
 */
int fossil_algorithm_sort(fossil_tofu_t *array, size_t size, bool ascending);

/**
 * Function to transform an array of `fossil_tofu_t` objects using a given transformation function.
 *
 * @param array The array of `fossil_tofu_t` objects.
 * @param size The number of elements in the array.
 * @param transform_fn A function pointer to a transformation function that modifies `fossil_tofu_t` objects.
 * @return `FOSSIL_TOFU_SUCCESS` if transformation is successful, or `FOSSIL_TOFU_FAILURE` if an error occurs.
 */
int fossil_algorithm_transform(fossil_tofu_t *array, size_t size, int (*transform_fn)(fossil_tofu_t *tofu));

/**
 * Function to accumulate a value from an array of `fossil_tofu_t` objects based on a given accumulation function.
 *
 * @param array The array of `fossil_tofu_t` objects.
 * @param size The number of elements in the array.
 * @param accumulate_fn A function pointer to an accumulation function that processes `fossil_tofu_t` objects.
 * @param initial The initial value to start the accumulation.
 * @return The accumulated result.
 */
void* fossil_algorithm_accumulate(const fossil_tofu_t *array, size_t size, void* (*accumulate_fn)(const fossil_tofu_t *tofu, void *accum), void* initial);

/**
 * Function to filter an array of `fossil_tofu_t` objects based on a given filtering function.
 *
 * @param array The array of `fossil_tofu_t` objects.
 * @param size The number of elements in the array.
 * @param filter_fn A function pointer to a filtering function that returns `true` if the tofu should be kept, or `false` if it should be excluded.
 * @param result The filtered result, which will be populated with the matching tofu objects.
 * @param result_size A pointer to a size variable that will hold the number of filtered elements.
 * @return `FOSSIL_TOFU_SUCCESS` if filtering is successful, or `FOSSIL_TOFU_FAILURE` if an error occurs.
 */
int fossil_algorithm_filter(const fossil_tofu_t *array, size_t size, bool (*filter_fn)(const fossil_tofu_t *tofu), fossil_tofu_t **result, size_t *result_size);

/**
 * Function to reverse an array of `fossil_tofu_t` objects.
 *
 * @param array The array of `fossil_tofu_t` objects.
 * @param size The number of elements in the array.
 * @return `FOSSIL_TOFU_SUCCESS` if reversal is successful, or `FOSSIL_TOFU_FAILURE` if an error occurs.
 */
int fossil_algorithm_reverse(fossil_tofu_t *array, size_t size);

/**
 * Function to find the minimum `fossil_tofu_t` object from an array based on a given comparison function.
 *
 * @param array The array of `fossil_tofu_t` objects.
 * @param size The number of elements in the array.
 * @param compare_fn A function pointer to a comparison function to determine the minimum.
 * @return A pointer to the minimum `fossil_tofu_t` object.
 */
fossil_tofu_t* fossil_algorithm_min(const fossil_tofu_t *array, size_t size);

/**
 * Function to find the maximum `fossil_tofu_t` object from an array based on a given comparison function.
 *
 * @param array The array of `fossil_tofu_t` objects.
 * @param size The number of elements in the array.
 * @param compare_fn A function pointer to a comparison function to determine the maximum.
 * @return A pointer to the maximum `fossil_tofu_t` object.
 */
fossil_tofu_t* fossil_algorithm_max(const fossil_tofu_t *array, size_t size);

/**
 * Function to calculate the sum of numerical values in an array of `fossil_tofu_t` objects.
 *
 * @param array The array of `fossil_tofu_t` objects.
 * @param size The number of elements in the array.
 * @param sum_fn A function pointer to a sum function that calculates the sum based on tofu values.
 * @return The sum result.
 */
void* fossil_algorithm_sum(const fossil_tofu_t *array, size_t size, void* (*sum_fn)(const fossil_tofu_t *tofu));

#ifdef __cplusplus
}
#include <stdexcept>

namespace fossil {

namespace tofu {

    /**
     * A class that provides static methods for various algorithmic operations
     * on `Tofu` objects. These methods wrap the corresponding C-style
     * functions for easier use in C++ code.
     */
    class Algorithm {
    public:
        /**
         * Compares two `Tofu` objects.
         *
         * @param tofu1 The first `Tofu` object.
         * @param tofu2 The second `Tofu` object.
         * @return A negative value if tofu1 < tofu2, 0 if tofu1 == tofu2, or a positive value if tofu1 > tofu2.
         */
        static int compare(const Tofu& tofu1, const Tofu& tofu2) {
            return fossil_algorithm_compare(tofu1.tofu_.get_value(), tofu2.tofu_.get_value());
        }

        /**
         * Searches for a `Tofu` object in an array.
         *
         * @param array The array of `Tofu` objects.
         * @param tofu The `Tofu` object to search for.
         * @return The index of the tofu object if found, or -1 if not found.
         */
        static int search(const std::vector<Tofu>& array, const Tofu& tofu) {
            std::vector<fossil_tofu_t*> raw_array;
            for (const auto& item : array) {
                raw_array.push_back(item.tofu_.get_value());
            }
            return fossil_algorithm_search(raw_array.data(), raw_array.size(), tofu.tofu_.get_value());
        }

        /**
         * Sorts an array of `Tofu` objects.
         *
         * @param array The array of `Tofu` objects.
         * @param ascending A boolean flag to indicate sorting order: `true` for ascending, `false` for descending.
         */
        static void sort(std::vector<Tofu>& array, bool ascending) {
            std::vector<fossil_tofu_t*> raw_array;
            for (auto& item : array) {
                raw_array.push_back(item.tofu_.get_value());
            }
            fossil_algorithm_sort(raw_array.data(), raw_array.size(), ascending);
        }

        /**
         * Transforms an array of `Tofu` objects using a transformation function.
         *
         * @param array The array of `Tofu` objects.
         * @param transform_fn A function pointer to a transformation function.
         */
        static void transform(std::vector<Tofu>& array, int (*transform_fn)(fossil_tofu_t *tofu)) {
            for (auto& item : array) {
                transform_fn(item.tofu_.get_value());
            }
        }

        /**
         * Filters an array of `Tofu` objects based on a filtering function.
         *
         * @param array The array of `Tofu` objects.
         * @param filter_fn A function pointer to a filtering function.
         * @return A filtered vector of `Tofu` objects.
         */
        static std::vector<Tofu> filter(const std::vector<Tofu>& array, bool (*filter_fn)(const fossil_tofu_t *tofu)) {
            std::vector<Tofu> result;
            for (const auto& item : array) {
                if (filter_fn(item.tofu_.get_value())) {
                    result.push_back(item);
                }
            }
            return result;
        }

        /**
         * Reverses an array of `Tofu` objects.
         *
         * @param array The array of `Tofu` objects.
         */
        static void reverse(std::vector<Tofu>& array) {
            std::vector<fossil_tofu_t*> raw_array;
            for (auto& item : array) {
                raw_array.push_back(item.tofu_.get_value());
            }
            fossil_algorithm_reverse(raw_array.data(), raw_array.size());
        }

        /**
         * Finds the minimum `Tofu` object in an array.
         *
         * @param array The array of `Tofu` objects.
         * @return The minimum `Tofu` object.
         */
        static Tofu min(const std::vector<Tofu>& array) {
            std::vector<fossil_tofu_t*> raw_array;
            for (const auto& item : array) {
                raw_array.push_back(item.tofu_.get_value());
            }
            fossil_tofu_t* min_tofu = fossil_algorithm_min(raw_array.data(), raw_array.size());
            return Tofu(min_tofu->type, min_tofu->value);
        }

        /**
         * Finds the maximum `Tofu` object in an array.
         *
         * @param array The array of `Tofu` objects.
         * @return The maximum `Tofu` object.
         */
        static Tofu max(const std::vector<Tofu>& array) {
            std::vector<fossil_tofu_t*> raw_array;
            for (const auto& item : array) {
                raw_array.push_back(item.tofu_.get_value());
            }
            fossil_tofu_t* max_tofu = fossil_algorithm_max(raw_array.data(), raw_array.size());
            return Tofu(max_tofu->type, max_tofu->value);
        }

        /**
         * Calculates the sum of numerical values in an array of `Tofu` objects.
         *
         * @param array The array of `Tofu` objects.
         * @param sum_fn A function pointer to a sum function.
         * @return The sum result.
         */
        static void* sum(const std::vector<Tofu>& array, void* (*sum_fn)(const fossil_tofu_t *tofu)) {
            std::vector<fossil_tofu_t*> raw_array;
            for (const auto& item : array) {
                raw_array.push_back(item.tofu_.get_value());
            }
            return fossil_algorithm_sum(raw_array.data(), raw_array.size(), sum_fn);
        }
    };

} // namespace tofu

} // namespace fossil

#endif

#endif /* FOSSIL_TOFU_FRAMEWORK_H */
