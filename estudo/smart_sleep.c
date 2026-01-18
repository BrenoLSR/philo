#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

long get_time_in_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void smart_sleep(long time_in_ms)
{
    long start;

    start = get_time_in_ms();
    while (get_time_in_ms() - start < time_in_ms)
    {
        usleep(100); // dorme 100 microsegundos
    }
}

int main(void)
{
    long start;
    long end;

    start = get_time_in_ms();
    smart_sleep(500); // 500 ms
    end = get_time_in_ms();

    printf("Slept for: %ld ms\n", end - start);
    return 0;
}