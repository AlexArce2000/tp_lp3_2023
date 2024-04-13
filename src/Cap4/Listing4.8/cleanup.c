#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Allocate a temporary buffer. */
void* allocate_buffer(size_t size)
{
    return malloc(size);
}

/* Deallocate a temporary buffer. */
void deallocate_buffer(void* buffer)
{
    free(buffer);
}

/* Function prototype for do_some_work */
void do_some_work();

void* thread_function(void* arg)
{
    /* Do some work in the thread. */
    do_some_work();

    return NULL;
}

void do_some_work()
{
    /* Allocate a temporary buffer. */
    void* temp_buffer = allocate_buffer(1024);
    /* Register a cleanup handler for this buffer, to deallocate it in
       case the thread exits or is cancelled. */
    pthread_cleanup_push(deallocate_buffer, temp_buffer);

    /* Simulate some work (calculations) */
    for (int i = 0; i < 5; i++) {
        printf("Thread is working... %d\n", i);
        sleep(1); // Simula trabajo
    }

    printf("Thread has finished its work.\n");

    /* Unregister the cleanup handler. Because we pass a nonzero value,
       this actually performs the cleanup by calling
       deallocate_buffer. */
    pthread_cleanup_pop(1);
}

int main()
{
    pthread_t thread;

    /* Create a thread. */
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    /* Wait for the thread to finish. */
    if (pthread_join(thread, NULL) != 0) {
        fprintf(stderr, "Error joining thread\n");
        return 1;
    }

    return 0;
}
