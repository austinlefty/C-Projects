#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "request_queue.h"
#include "worker_thread.h"
#include "worker_thread_pool.h"

//Define Variables
#define WORKER_THREADS 5
#define REQUESTS 200

//PThread Initializers
pthread_mutex_t pm = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t pc = PTHREAD_COND_INITIALIZER;

//Keeps track of task number
int task_num = 0;

int main(int argc, char const *argv[]){

    //Creates request queue and thread pool
    struct request_queue* queue = create_request_queue(&pm, &pc);
    struct worker_thread_pool* pool = create_worker_thread_pool(queue);

    //Adds threads to thread pool
    for(int i = 0; i < WORKER_THREADS; i++){
        add_worker_thread(pool);
    }

    //Adds requests to request queue
    while(task_num < REQUESTS){
        add_request(queue, task_num);
        task_num++;
    }

    for (int i = 0; i < WORKER_THREADS; i++) {
        pthread_join(pool -> thread_list -> thread, NULL);
        printf("Thread %d Exiting.\n", (i+1));
        pool->thread_list = pool->thread_list->next;
    }

    printf("Processed %d Requests.\n", task_num);

    //Free Memory
    close_request_queue(queue);
    delete_worker_thread_pool(pool);
    delete_request_queue(queue);
    pthread_mutex_destroy(&pm);
    pthread_cond_destroy(&pc);
    
    pthread_exit(NULL);

    return 0;
}