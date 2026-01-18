#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *routine(void *arg)
{
    int id;

    id = *(int *)arg;
    printf("Thread %d started\n", id);
    usleep(100000); // 100 ms
    printf("Thread %d finished\n", id);
    return NULL;
}

int main(void)
{
    pthread_t threads[5];
    int ids[5];
    int i;

    i = 0;
    while (i < 5)
    {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, routine, &ids[i]);
        i++;
    }

    i = 0;
    while (i < 5)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    return 0;
}
