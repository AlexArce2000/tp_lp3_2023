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
struct job* job_queue = NULL;

/* A mutex protecting job_queue. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

/* Function to process a job (customize this as needed). */
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
    while (1) {
        struct job* next_job;
        /* Lock the mutex on the job queue. */
        pthread_mutex_lock(&job_queue_mutex);
        /* Now it's safe to check if the queue is empty. */
        if (job_queue == NULL)
            next_job = NULL;
        else {
            /* Get the next available job. */
            next_job = job_queue;
            /* Remove this job from the list. */
            job_queue = job_queue->next;
        }
        /* Unlock the mutex on the job queue because we're done with the queue for now. */
        pthread_mutex_unlock(&job_queue_mutex);
        /* Was the queue empty? If so, end the thread. */
        if (next_job == NULL)
            break;
        /* Carry out the work. */
        process_job(next_job);
        /* Clean up. */
        free(next_job);
    }
    return NULL;
}

int main() {
    // Create some jobs and add them to the queue
    for (int i = 0; i < 20; i++) {
        struct job* new_job = (struct job*)malloc(sizeof(struct job));
        new_job->next = job_queue;
        job_queue = new_job;
        new_job->job_number = i + 1; // Assign a job number
    }

    // Create threads to process the jobs (customize the number of threads as needed)
    pthread_t threads[20];
    for (int i = 0; i < 20; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    // Wait for the threads to finish
    for (int i = 0; i < 20; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining thread\n");
            return 1;
        }
    }

    return 0;
}
