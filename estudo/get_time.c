#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

long get_time_in_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int main(void)
{
    long start;
    long end;

    start = get_time_in_ms();
    printf("Start time: %ld ms\n", start);

    sleep(1); // espera 1 segundo

    end = get_time_in_ms();
    printf("End time: %ld ms\n", end);

    printf("Difference: %ld ms\n", end - start);
    return 0;
}