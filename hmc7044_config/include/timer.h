/*
 * timer.h
 *
 *  Created on: Nov 20, 2019
 *      Author: jpierce
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

typedef struct
{
    uint32_t currentTime_us;
    uint32_t elapsedTime_us;
    uint32_t timeOut_us;
    uint32_t timerStart_us;
    uint8_t  timerExpired;

} timerSettings_t;

int32_t HAL_setTimeout_ms(uint32_t timeOut_ms);
uint32_t HAL_setTimeout_us(uint32_t timeOut_us);
int32_t HAL_hasTimeoutExpired(void);
int32_t HAL_wait_us(uint32_t time_us);
int32_t HAL_wait_ms(uint32_t time_ms);

#endif /* SRC_TIMER_H_ */
