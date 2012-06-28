#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    struct timeval tempo1, tempo2;

    long elapsed_utime;    /* elapsed time in microseconds */
    long elapsed_mtime;    /* elapsed time in milliseconds */
    long elapsed_seconds;  /* diff between seconds counter */
    long elapsed_useconds; /* diff between microseconds counter */

    printf("Enter q to quit timing loop: ");
    gettimeofday(&tempo1, NULL);
    while (getchar() != 'q') {

    }

    gettimeofday(&tempo2, NULL);
    
    elapsed_seconds  = tempo2.tv_sec  - tempo1.tv_sec;
    elapsed_useconds = tempo2.tv_usec - tempo1.tv_usec;

    printf("Elapsed time = %ld seconds + %ld microseconds\n",
            elapsed_seconds, elapsed_useconds);

    elapsed_utime = (elapsed_seconds) * 1000000 + elapsed_useconds;
    elapsed_mtime = ((elapsed_seconds) * 1000 + elapsed_useconds/1000.0) + 0.5;

    printf("Elapsed time = %ld microseconds\n", elapsed_utime);
    printf("Elapsed time = %ld milliseconds\n", elapsed_mtime);

    return 0;
}
