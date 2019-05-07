#include <sys/signal.h>
#include <time.h>
#include <sys/time.h>
#include "disk.h"

#define COUNTDOWN_VALUE 10

#define TIMEOUT_INTERVAL 2
#define TIMEOUT_DELAY 5

timer_t gTimerid;
int count = COUNTDOWN_VALUE;
int size;

void disk_timer(void)
{
    struct itimerspec value;
    //simfs generate content
}

void start_timer(void)
{
    struct itimerspec value;

    value.it_value.tv_sec = TIMEOUT_DELAY;
    value.it_value.tv_nsec = 0;

    value.it_interval.tv_sec = TIMEOUT_INTERVAL;
    value.it_interval.tv_nsec = 0;

    timer_create (CLOCK_REALTIME, NULL, &gTimerid);

    timer_settime (gTimerid, 0, &value, NULL);

}

void stop_timer(void)
{
    struct itimerspec value;

    value.it_value.tv_sec = 0;
    value.it_value.tv_nsec = 0;

    value.it_interval.tv_sec = 0;
    value.it_interval.tv_nsec = 0;

    timer_settime (gTimerid, 0, &value, NULL);
}

void timer_callback(int sig)
{
    printf("Caught timer signal: %d ... !!\n", sig);
    struct timeval ts;
    time_t tm;

    time(&tm); // man 3 time
    printf("Time: %s", ctime(&tm)); // man ctime

    gettimeofday(&ts, NULL); // man gettimeofday
    printf("Time: %ld.%06ld secs.\n\n", (long)ts.tv_sec, (long)ts.tv_usec);
    count--;
}

char GenerateContent(int size)
{
    size = (size <= 0 ? rand() % 1000 : size); // arbitrarily chosen as an example

    char *content = malloc(size);

    int firstPrintable = ' ';
    int len = '~' - firstPrintable;

    for (int i = 0; i < size - 1; i++)
        *(content + i) = firstPrintable + rand() % len;

    content[size - 1] = '\0';
    return content;
}
int makeRandomCrapHappen(int lower, int upper,)
{
    int num = (rand() %(upper - lower + 1)) + lower;
    return num;
}

int main(int ac, char **av)
{
    char* buffer = malloc( 8 * SECT_SIZE);
    size = makeRandomCrapHappen(0, SECT_SIZE);
    (void) signal(SIGALRM, timer_callback);
    start_timer();
    *buffer = GenerateContent(size);
    if(ac < 2)
    {
        writeDisk(makeRandomCrapHappen(0, MAX_LOGICAL_SECTOR) , size , buffer);
        printf();
        readDisk(makeRandomCrapHappen(0, MAX_LOGICAL_SECTOR) , size , buffer)
    }
    else if()
    {

    }
    while (count >= 0);
}
