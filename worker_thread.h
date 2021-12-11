#ifndef WORKER_THREAD_H
#define WORKER_THREAD_H

#include <pthread.h>
#include <stdio.h>

/* Parameters to be passed to worker thread */
struct worker_thread_params {
    int thread_id;
    struct request_queue* req_queue;
};

/*
 * The worker thread's main loop function.
 * Pass this as the start routine to pthread_create(3)
 * This function picks requests off the queue to process.
 *
 * When no more items are on the queue for processing, then
 * the threads waits until requests are placed in the queue.
 *
 * The worker_thread_param should be cast to type
 * struct worker_thread_param.
 */
extern void* do_work(void* thread_params);

#endif
