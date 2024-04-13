#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // Para usleep

int thread_flag;
pthread_mutex_t thread_flag_mutex;

void initialize_flag()
{
    pthread_mutex_init(&thread_flag_mutex, NULL);
    thread_flag = 0;
}

/* Función personalizada que representa el trabajo a realizar. */
void do_work()
{
    // Coloca aquí el código de la tarea que deseas realizar.
    printf("Haciendo trabajo...\n");
    // Por ejemplo, espera un segundo.
    sleep(1);
}

/* Función del hilo que verifica la bandera y ejecuta do_work si está activa. */
void* thread_function(void* thread_arg)
{
    while (1) {
        int flag_is_set;

        /* Protege la bandera con un candado de mutex. */
        pthread_mutex_lock(&thread_flag_mutex);
        flag_is_set = thread_flag;
        pthread_mutex_unlock(&thread_flag_mutex);

        if (flag_is_set)
            do_work();
        /* Else no hace nada. Simplemente entra en bucle nuevamente. */
    }
    return NULL;
}

/* Establece el valor de la bandera del hilo en FLAG_VALUE. */
void set_thread_flag(int flag_value)
{
    /* Protege la bandera con un candado de mutex. */
    pthread_mutex_lock(&thread_flag_mutex);
    thread_flag = flag_value;
    pthread_mutex_unlock(&thread_flag_mutex);
}

int main()
{
    initialize_flag();
    
    // Crea un hilo para ejecutar thread_function.
    pthread_t thread;
    pthread_create(&thread, NULL, thread_function, NULL);
    
    // Activa la bandera para que el hilo comience a ejecutar do_work.
    set_thread_flag(1);

    // Espera un tiempo para que el hilo pueda ejecutar do_work.
    sleep(5);

    // Desactiva la bandera para que el hilo deje de ejecutar do_work.
    set_thread_flag(0);

    // Espera a que el hilo termine antes de salir del programa.
    pthread_join(thread, NULL);

    return 0;
}
