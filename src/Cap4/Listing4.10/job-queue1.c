#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct job {
    /* Link field for linked list. */
    struct job* next;
    /* Other fields describing work to be done... */
    int job_number;
};

/* A linked list of pending jobs. */
struct job* job_queue = NULL; // Inicializamos la lista como vacía

/* Function to process a job. */
void process_job(struct job* j) {
    printf("Processing job #%d\n", j->job_number);
    // Simulated delay
    for (int i = 0; i < 1000000; i++) {
        // This loop is just to simulate some work
    }
    printf("Job #%d processed\n", j->job_number);
}

/* Process queued jobs until the queue is empty. */
void* thread_function(void* arg) {
    while (job_queue != NULL) {
        /* Get the next available job. */
        struct job* next_job = job_queue;
        /* Remove this job from the list. */
        job_queue = job_queue->next;
        /* Carry out the work. */
        process_job(next_job);
        /* Clean up. */
        free(next_job);
    }
    return NULL;
}

int main() {
    // Create some jobs and add them to the queue
    for (int i = 0; i < 5; i++) {
        struct job* new_job = (struct job*)malloc(sizeof(struct job));
        new_job->next = job_queue;
        job_queue = new_job;
        new_job->job_number = i + 1; // Assign a job number
    }

    // Create a thread to process the jobs
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // Wait for the thread to finish
    if (pthread_join(thread, NULL) != 0) {
        fprintf(stderr, "Error joining thread\n");
        return 1;
    }

    return 0;
}
