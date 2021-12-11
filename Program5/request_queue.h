#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

/* Linked list request node */
struct request {
    int number;
    struct request* next;
};

/* structure for a request queue */
struct request_queue {
    struct request* request_list;  // request linked list
    struct request* last_request;  // last request in list
    int num_requests;              // number of requests in the queue
    bool is_closed;  // true when queue no more requests will be generated
    pthread_mutex_t* mutex;    // queue's mutex
    pthread_cond_t* cond_var;  // queue's condition variable
};

/*
 * create a requests queue. associate it with the given mutex
 * and condition variables.
 */
extern struct request_queue* create_request_queue(pthread_mutex_t* mutex,
                                                  pthread_cond_t* cond_var);

/* add a request to the requests list */
extern void add_request(struct request_queue* req_queue, int request_num);

/*
 * Returns the oldest pending request in the queue.
 * Returns NULL if no requests are pending.
 * The returned request is removed from the queue.
 * The receiver must free the request to release its memory.
 */
extern struct request* get_request(struct request_queue* req_queue);

/* returns the number of pending requests in the queue */
extern int get_pending_request_count(struct request_queue* req_queue);

/* free any resources used by request queue */
extern void delete_request_queue(struct request_queue* req_queue);

/* close the queue as it is no longer accepting requests */
extern void close_request_queue(struct request_queue* req_queue);

/* returns true if the request queue is closed */
extern bool is_request_queue_closed(struct request_queue* req_queue);

#endif
