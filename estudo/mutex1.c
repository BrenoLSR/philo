#include <pthread.h>
#include <stdio.h>

/*
Ciclo de vida do mutex

init

lock

acesso ao recurso

unlock

destroy
*/

int counter = 0;
pthread_mutex_t mutex;

void *routine(void *arg)
{
    int i = 0;
    while (i < 100000)
    {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, routine, NULL);
    pthread_create(&t2, NULL, routine, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);

    printf("Counter: %d\n", counter);
    return 0;
}
