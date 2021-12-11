#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "request_queue.h"
#include "worker_thread.h"
#include "worker_thread_pool.h"

static bool is_prime(int n);
static void process_request(struct request* request, int thread_id);

/*
 * Processes one request.
 */
static void process_request(struct request* request, int thread_id) {
    if (request) {
        //printf("THREAD [%d] processing TASK [%d]\t\n", thread_id, request->number);
        //fflush(stdout);
        // Should really do some real work here - so find some primes
        for (int i = 1; i < 10001; ++i) {
            is_prime(i);
        }
        //printf("THREAD [%d] Ended TASK[%d]\t\n\n", thread_id, request->number);
    }

#ifdef DEBUG
    printf("thread-%d processed request [%d]\n", thread_id, request->number);
#endif
}

static bool is_prime(int n) {
    if (n == 1) return false;
    bool prime = true;
    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            prime = false;
            return prime;
        }
    }
    return prime;
}

/*
 * This function continuously runs/loops.
 * if there's a request on the queue, take it off the
 * the queue and call process_request().
 *
 * if no requests are pending then wait on the condition
 * variable until a request arrives.
 *
 * Exit the thread when the request queue is closed.
 */
void* do_work(void* thread_params) {
    //Creates worker thread params 
    struct worker_thread_params* params = thread_params;
    printf("Thread %d Starting.\n", params -> thread_id + 1);
    
    //Locks mutex
    pthread_mutex_lock(params -> req_queue -> mutex);

    while(1){
        if(is_request_queue_closed(params -> req_queue)){
            break;
        }

        while(params -> req_queue -> num_requests == 0){
            pthread_cond_wait(params -> req_queue -> cond_var, params -> req_queue -> mutex);
        }

        //Creates and processes request
        struct request* request = get_request(params -> req_queue);
        process_request(request, params -> thread_id);
    }

    //Unlocks mutex
    pthread_mutex_unlock(params -> req_queue -> mutex);
    pthread_exit(NULL);
}
