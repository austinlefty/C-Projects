#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "request_queue.h"
#include "worker_thread.h"
#include "worker_thread_pool.h"

struct request_queue* create_request_queue(pthread_mutex_t* p_mutex, pthread_cond_t* p_cond_var) 
{
    //Creates request queue
    struct request_queue* queue = malloc(sizeof(struct request_queue));

    //Gives structure values to created queue
    queue -> request_list = NULL;
    queue -> last_request = NULL;
    queue -> num_requests = 0;
    queue -> is_closed = false;
    queue -> mutex = p_mutex;
    queue -> cond_var = p_cond_var;
    
    return queue;
}

void add_request(struct request_queue* req_queue, int request_num) {
    //Locks mutex 
    pthread_mutex_lock(req_queue -> mutex);

    //Creates request
    struct request* request = malloc(sizeof(struct request));

    //Gives structure values to created request
    request -> number = request_num;
    request -> next = NULL;

    //Assigns request to request list
    if(request_num == 0){
        req_queue -> request_list = request;
    }
    else{
        req_queue -> last_request -> next = request;
    }

    //Assigns latest created request to last request
    req_queue -> last_request = request;
    req_queue -> num_requests++;

    //Unlocks mutex
    pthread_cond_signal(req_queue -> cond_var);
    pthread_mutex_unlock(req_queue -> mutex);
}

/*
 * Returns the oldest pending request in the queue.
 * Returns NULL if no requests are pending.
 * The returned request is removed from the queue.
 * The receiver must free the request to release its memory.
 */
struct request* get_request(struct request_queue* req_queue) {

    //Creates request
    struct request* request = malloc(sizeof(struct request));
    while(1){
        if(req_queue -> num_requests == 0){
            return NULL;
        }
        else{
            request = req_queue -> request_list;
            req_queue ->num_requests--;
            
            if(request -> next != NULL){
            req_queue -> request_list = request -> next;
            }
            
            if(req_queue -> request_list == NULL){
                req_queue -> last_request = NULL;
            }

            return request;
        }
    }
}

int get_pending_request_count(struct request_queue* req_queue) {
    return req_queue -> num_requests;
}

void delete_request_queue(struct request_queue* req_queue) {
    //free(req_queue); //Deleting queue causes a segmentation fault
}

void close_request_queue(struct request_queue* req_queue) {
    req_queue -> is_closed = true;
}

bool is_request_queue_closed(struct request_queue* req_queue) {
    return req_queue -> is_closed;
}