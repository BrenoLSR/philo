#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *routine(void *arg)
{
    printf("Hello from thread!\n");
    sleep(1);
    printf("Thread finished\n");
    return NULL;
}

int main(void)
{
    pthread_t t;

    pthread_create(&t, NULL, routine, NULL);
    pthread_join(t, NULL);

    printf("Main finished\n");
    return 0;
}
