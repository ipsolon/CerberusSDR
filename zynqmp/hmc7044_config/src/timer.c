/*
 * timer.c
 *
 *  Created on: Nov 20, 2019
 *      Author: jpierce
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include "timer.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
// Local Forward Declarations ///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////

// Holds timer data while waiting for timeout.
// Assumes single threaded calling function.
timerSettings_t		global_timerData;


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief Retrieves Current Time in us from the platform's system and set it as
 * the timer start time.
 *
 *
 *startTime_us member of global_timerData will be updated with current
 * Time retrieved from the platform's system. Time is stored in us.
 *
 * <B>Dependencies</B>
 * -
 *
 * \param device Pointer to HAL_timerSettings_t data structure
 *
 * \return Returns error from platform layer system calls
 */
int32_t HAL_startTimer_us(void)
{
    struct timespec currTime;

    clock_gettime(CLOCK_MONOTONIC, &currTime);
    global_timerData.timerStart_us = (currTime.tv_sec * 1000000) + (currTime.tv_nsec/1000);

    return 0;
}


/**
 * \brief Checks to see if the time elapsed since timer was started exceeds the
 * desired timeout length.
 *
 *
 * Compares Time Elapsed between the time specified by timerStart_us member of global_timerData
 * and the current time as reported by platform's system.
 * Th time elapsed is stored in the elapsedTime_us member of global_timerData.
 * If the Time Elapsed is greater than the time length specified by the timeOut_us
 * member of global_timerData, timerExpired is set to 1. Otherwise timerExpired is set to 0
 *
 * <B>Dependencies</B>
 * -
 *
 * \param device Pointer to HAL_timerSettings_t data structure
 *
 * \return Returns error from platform layer system calls
 */
int32_t HAL_hasTimeoutExpired(void)
{
    struct timespec currTime;
    int32_t error =0;

    global_timerData.timerExpired = 0;
    clock_gettime(CLOCK_MONOTONIC, &currTime);

    global_timerData.currentTime_us = (currTime.tv_sec * 1000000) + (currTime.tv_nsec/1000);
	global_timerData.elapsedTime_us = global_timerData.currentTime_us - global_timerData.timerStart_us;

    if(global_timerData.elapsedTime_us > global_timerData.timeOut_us)
    {
        global_timerData.timerExpired = 1;
		return 1;
    }
	else
		return 0;

}

//////////////////////////////////////////////////////////////////////////////
int32_t HAL_wait_ms(uint32_t time_ms)
{
   uint32_t retval = 0;
   struct timespec t0;
   struct timespec t1;
   struct timespec *temp;
   struct timespec *waitTime = &t0;
   struct timespec *remaining = &t1;

   waitTime->tv_sec = time_ms/1000;
   waitTime->tv_nsec = (time_ms % 1000) * (1000000);

   do{
       retval = nanosleep(waitTime, remaining);
       temp = waitTime;
       waitTime = remaining;
       remaining = temp;
   }while((retval == -1) && (errno == EINTR));

   if(retval)
   {
       return errno;
   }
   else
   {
       return 0;
   }
}

//////////////////////////////////////////////////////////////////////////////
int32_t HAL_wait_us(uint32_t time_us)
{
   uint32_t retval = 0;
   struct timespec t0;
   struct timespec t1;
   struct timespec *temp;
   struct timespec *waitTime = &t0;
   struct timespec *remaining = &t1;

   waitTime->tv_sec = time_us/1000000;
   waitTime->tv_nsec = (time_us % 1000000) * (1000);

   do{
       retval = nanosleep(waitTime, remaining);
       temp = waitTime;
       waitTime = remaining;
       remaining = temp;
   }while((retval == -1) && (errno == EINTR));

   if(retval)
   {
       return errno;
   }
   else
   {
       return 0;
   }
}


//////////////////////////////////////////////////////////////////////////////
uint32_t HAL_setTimeout_us(uint32_t timeOut_us)
{
	global_timerData.timeOut_us = timeOut_us;
	HAL_startTimer_us();

	return 0;
}


//////////////////////////////////////////////////////////////////////////////
int32_t HAL_setTimeout_ms(uint32_t timeOut_ms)
{
	HAL_setTimeout_us(timeOut_ms * 1000);
    return 0;
}

