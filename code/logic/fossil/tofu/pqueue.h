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
#ifndef FOSSIL_TOFU_PQUEUE_H
#define FOSSIL_TOFU_PQUEUE_H

#include "tofu.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct fossil_pqueue_node_t {
    fossil_tofu_t data;
    int32_t priority;
    struct fossil_pqueue_node_t* next;
} fossil_pqueue_node_t;

typedef struct fossil_pqueue_t {
    fossil_pqueue_node_t* front;
    char* type;
} fossil_pqueue_t;

/**
 * Create a new priority queue with the specified data type.
 *
 * @param queue_type The type of data the priority queue will store.
 * @return           The created priority queue.
 */
fossil_pqueue_t* fossil_pqueue_create(char* type);

/**
 * Erase the contents of the priority queue and free allocated memory.
 *
 * @param pqueue The priority queue to erase.
 */
void fossil_pqueue_erase(fossil_pqueue_t* pqueue);

/**
 * Insert data into the priority queue with the specified priority.
 *
 * @param pqueue   The priority queue to insert data into.
 * @param data     The data to insert.
 * @param priority The priority of the data.
 * @return         The error code indicating the success or failure of the operation.
 */
int32_t fossil_pqueue_insert(fossil_pqueue_t* pqueue, fossil_tofu_t data, int32_t priority);

/**
 * Remove data from the priority queue.
 *
 * @param pqueue   The priority queue to remove data from.
 * @param data     The data to remove.
 * @param priority The priority of the data.
 * @return         The error code indicating the success or failure of the operation.
 */
int32_t fossil_pqueue_remove(fossil_pqueue_t* pqueue, fossil_tofu_t* data, int32_t priority);

/**
 * Search for data in the priority queue.
 *
 * @param pqueue   The priority queue to search.
 * @param data     The data to search for.
 * @param priority The priority of the data.
 * @return         The error code indicating the success or failure of the operation.
 */
int32_t fossil_pqueue_search(const fossil_pqueue_t* pqueue, fossil_tofu_t data, int32_t priority);

/**
 * Get the size of the priority queue.
 *
 * @param pqueue The priority queue for which to get the size.
 * @return       The size of the priority queue.
 */
size_t fossil_pqueue_size(const fossil_pqueue_t* pqueue);

/**
 * Get the data from the priority queue matching the specified data and priority.
 *
 * @param pqueue   The priority queue from which to get the data.
 * @param data     The data to search for.
 * @param priority The priority of the data.
 * @return         A pointer to the matching data, or NULL if not found.
 */
fossil_tofu_t* fossil_pqueue_getter(fossil_pqueue_t* pqueue, fossil_tofu_t data, int32_t priority);

/**
 * Set data in the priority queue with the specified priority.
 *
 * @param pqueue   The priority queue in which to set the data.
 * @param data     The data to set.
 * @param priority The priority of the data.
 * @return         The error code indicating the success or failure of the operation.
 */
int32_t fossil_pqueue_setter(fossil_pqueue_t* pqueue, fossil_tofu_t data, int32_t priority);

/**
 * Check if the priority queue is not empty.
 *
 * @param pqueue The priority queue to check.
 * @return       True if the priority queue is not empty, false otherwise.
 */
bool fossil_pqueue_not_empty(const fossil_pqueue_t* pqueue);

/**
 * Check if the priority queue is not a null pointer.
 *
 * @param pqueue The priority queue to check.
 * @return       True if the priority queue is not a null pointer, false otherwise.
 */
bool fossil_pqueue_not_cnullptr(const fossil_pqueue_t* pqueue);

/**
 * Check if the priority queue is empty.
 *
 * @param pqueue The priority queue to check.
 * @return       True if the priority queue is empty, false otherwise.
 */
bool fossil_pqueue_is_empty(const fossil_pqueue_t* pqueue);

/**
 * Check if the priority queue is a null pointer.
 *
 * @param pqueue The priority queue to check.
 * @return       True if the priority queue is a null pointer, false otherwise.
 */
bool fossil_pqueue_is_cnullptr(const fossil_pqueue_t* pqueue);

#ifdef __cplusplus
}
#endif

#endif /* FOSSIL_TOFU_FRAMEWORK_H */
