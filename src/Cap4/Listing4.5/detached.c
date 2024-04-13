#include <pthread.h>
#include <stdio.h>

void * thread_function (void *arg){
    while (1)
    {
        printf("HILO\n");
    }
    return NULL;
}

int main(){
    pthread_attr_t attr;
    pthread_t thread;
    


    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread, &attr, &thread_function, NULL);
    pthread_attr_destroy(&attr);

    /* Do work here */
    while (1)
    {
        printf("MAIN\n");
    }

    return 0;

}