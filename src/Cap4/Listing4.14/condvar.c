#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int thread_flag;
pthread_cond_t thread_flag_cv;
pthread_mutex_t thread_flag_mutex;

void initialize_flag()
{
    /* Inicializa el mutex y la variable de condición. */
    pthread_mutex_init(&thread_flag_mutex, NULL);
    pthread_cond_init(&thread_flag_cv, NULL);
    /* Inicializa el valor de la bandera. */
    thread_flag = 0;
}

/* Esta función simula realizar algún trabajo. */
void do_work()
{
    printf("Hilo trabajando...\n");
    usleep(1000000); // Simula un trabajo de 1 segundo.
}

/* Función del hilo que ejecuta el trabajo si la bandera está configurada. */
void *thread_function(void *thread_arg)
{
    while (1)
    {
        /* Bloquea el mutex antes de acceder al valor de la bandera. */
        pthread_mutex_lock(&thread_flag_mutex);
        while (!thread_flag)
        {
            /* La bandera está despejada. Espera una señal en la variable de condición,
               lo que indica que el valor de la bandera ha cambiado. Cuando llega la señal y
               este hilo se desbloquea, vuelve a verificar la bandera. */
            pthread_cond_wait(&thread_flag_cv, &thread_flag_mutex);
        }
        /* Cuando llegamos aquí, sabemos que la bandera debe estar configurada. Desbloquea el mutex. */
        pthread_mutex_unlock(&thread_flag_mutex);
        /* Realiza algún trabajo. */
        do_work();
    }
    return NULL;
}

/* Configura el valor de la bandera del hilo en FLAG_VALUE. */
void set_thread_flag(int flag_value)
{
    /* Bloquea el mutex antes de acceder al valor de la bandera. */
    pthread_mutex_lock(&thread_flag_mutex);
    /* Configura el valor de la bandera y luego señala en caso de que thread_function esté bloqueado,
       esperando que la bandera se configure. Sin embargo, thread_function no puede verificar la bandera
       hasta que se desbloquee el mutex. */
    thread_flag = flag_value;
    pthread_cond_signal(&thread_flag_cv);
    /* Desbloquea el mutex. */
    pthread_mutex_unlock(&thread_flag_mutex);
}

int main()
{
    pthread_t thread;
    initialize_flag();

    /* Crea un hilo que ejecute la función thread_function. */
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0)
    {
        perror("Error al crear el hilo");
        return 1;
    }

    /* Configura la bandera en 1 para que el hilo comience a trabajar. */
    set_thread_flag(1);

    /* Simula la ejecución del programa principal durante un tiempo. */
    sleep(5);

    /* Configura la bandera en 0 para detener el hilo. */
    set_thread_flag(0);

    /* Espera a que el hilo termine. */
    pthread_join(thread, NULL);

    return 0;
}
