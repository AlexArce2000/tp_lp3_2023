#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

struct job {
    struct job* next;
    int job_number;
};

struct job* job_queue = NULL;
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t job_queue_count;

void initialize_job_queue() {
    job_queue = NULL;
    sem_init(&job_queue_count, 0, 0);
}

void process_job(struct job* j) {
    printf("Processing job #%d\n", j->job_number);
    // Simulate work by sleeping for a random period (1 to 3 seconds)
    sleep((rand() % 3) + 1);
    printf("Job #%d completed\n", j->job_number);
}

void* thread_function(void* arg) {
    while (1) {
        struct job* next_job;
        sem_wait(&job_queue_count);
        pthread_mutex_lock(&job_queue_mutex);
        next_job = job_queue;
        job_queue = job_queue->next;
        pthread_mutex_unlock(&job_queue_mutex);
        if (next_job == NULL)
            break;
        process_job(next_job);
        free(next_job);
    }
    return NULL;
}

void enqueue_job(int job_number) {
    struct job* new_job;
    new_job = (struct job*)malloc(sizeof(struct job));
    new_job->job_number = job_number;
    pthread_mutex_lock(&job_queue_mutex);
    new_job->next = job_queue;
    job_queue = new_job;
    sem_post(&job_queue_count);
    pthread_mutex_unlock(&job_queue_mutex);
}

int main() {
    initialize_job_queue();

    // Enqueue some jobs
    for (int i = 0; i < 10; i++) {
        enqueue_job(i + 1);
    }

    // Create threads to process the jobs
    pthread_t threads[5];
    for (int i = 0; i < 5; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    // Wait for the threads to finish
    for (int i = 0; i < 5; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining thread\n");
            return 1;
        }
    }

    return 0;
}
