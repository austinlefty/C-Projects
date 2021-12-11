#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "request_queue.h"
#include "worker_thread.h"
#include "worker_thread_pool.h"

static int next_id = 0;

struct worker_thread_pool* create_worker_thread_pool(struct request_queue* req_queue) {
    //Creates thread pool
    struct worker_thread_pool* pool = malloc(sizeof(struct worker_thread_pool));

    //Gives structure values to created thread pool
    pool -> last_thread_id = 0;
    pool -> num_threads = 0;
    pool -> thread_list = NULL;
    pool -> last_thread = NULL;
    pool -> req_queue = req_queue;
    
    return pool;
}

void add_worker_thread(struct worker_thread_pool* pool) {

    //Creates thread, thread params, and worker thread
    pthread_t t;
    struct worker_thread_params* params = malloc(sizeof(struct worker_thread_params));
    struct worker_thread* thread = malloc(sizeof(struct worker_thread));

    //Gets new thread from pool
    struct worker_thread* new_next = pool -> thread_list;
    thread -> next = new_next;

    //Increments thread id
    thread -> thread_id = next_id++;

    pool -> num_threads++;
    pool -> thread_list = thread;
    pool -> last_thread_id = thread -> thread_id;
    params -> req_queue = pool -> req_queue;
    params -> thread_id = thread -> thread_id;
    
    thread -> thread = pthread_create(&t, NULL, do_work, params);
}

void delete_worker_thread_pool(struct worker_thread_pool* pool) {
    //free(pool); //Deleting pool causes a segmentation fault
}