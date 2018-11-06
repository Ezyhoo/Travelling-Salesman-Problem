/** Student Name: Yizhi Hu
 *  File Name: timer.c
 *  Assignment: project #3
 *
 *  This file is going to implement a timer so that it will print out the
 *  the interval time each algorithm took
 */
#include "timer.h"

#define MILLION 1000000
#define MINUTE 60

struct timeval *t;
time_t startSec;
time_t startMicroSeconds;

time_t intervalMin;
time_t intervalSec;
time_t intervalMicroSec;

/**
 * This function start a timer
 *
 */
void startTime(){

    intervalMin = 0;
    t = (struct timeval*) malloc (sizeof(struct timeval));
    gettimeofday(t,NULL);
    startSec = t->tv_sec;
    startMicroSeconds = t->tv_usec;


}

/**
 * This function calculate the time that a algorithm took
 *
 */
void getIntervalTime(){

    gettimeofday(t,NULL);
    long int endMicroSec = t->tv_usec;
//    printf("The end micro seconds would be %ld\n",endMicroSec);

   long int endSec = t->tv_sec;
//    printf("Total seconds spend is %ld\n", endSec - startSec);

    if(endMicroSec - startMicroSeconds < 0){   //check if we need to borrow from second to micro second
        endSec -= 1;
        endMicroSec += MILLION;
    }

    intervalMicroSec = endMicroSec - startMicroSeconds;
    intervalSec = endSec - startSec;

    while(intervalSec / MINUTE > 0){
        intervalSec -= MINUTE;
        intervalMin++;
    }

}

/**
 * This algorithm call getIntervalTime and print out the time that
 * the algorithm took
 */
void endTime(){
//    if(timeIsInit == 1){
//        while(i <= 10000000){
//            i++;
//        }
//    }
//    printf("Now the timer pointer is at address %p\n",t);
    getIntervalTime();
    printf("The run time of this algorithm is %ld minute(s), %ld seconds, and %ld micro seconds.\n\n",intervalMin, intervalSec, intervalMicroSec);
    free(t);
}

