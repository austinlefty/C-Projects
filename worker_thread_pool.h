#ifndef WORKER_THREAD_POOL_H
#define WORKER_THREAD_POOL_H

#include <pthread.h>
#include <stdio.h>

#include "request_queue.h"
#include "worker_thread.h"

/*
 *  Worker thread node stored in worker_thread_pool's
 *  linked list of worker threads
 */
struct worker_thread {
    int thread_id;               // thread id - a sequentially assigned number
    pthread_t thread;            // thread identifier returned by pthread_create
    struct worker_thread* next;  // next worker thread
};

struct worker_thread_pool {
    int last_thread_id;                 // Id of last thread in linked list
    int num_threads;                    // number of threads in pool
    struct worker_thread* thread_list;  // linked list of threads
    struct worker_thread* last_thread;  // last thread in list
    struct request_queue* req_queue;
};

/*
 * Creates a worker thread pool with the given mutex,
 * condition variable and request queue.
 */
extern struct worker_thread_pool* create_worker_thread_pool(
    struct request_queue* req_queue);

/* Adds a new worker thread to thread pool */
extern void add_worker_thread(struct worker_thread_pool* pool);

/* Removes the first worker thread from the thread pool */
extern void remove_worker_thread(struct worker_thread_pool* pool);

/* Gets current count of worker threads in thread pool */
extern int get_worker_thread_count(struct worker_thread_pool* pool);

/* Performs resource clean up and cancel all worker threads. */
extern void delete_worker_thread_pool(struct worker_thread_pool* pool);

#endif