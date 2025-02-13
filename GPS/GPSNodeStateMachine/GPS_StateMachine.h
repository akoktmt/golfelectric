/*
 * GPS_StateMachine.h
 *
 *  Created on: Jan 27, 2024
 *      Author: win 10
 */

#ifndef GPS_STATEMACHINE_H_
#define GPS_STATEMACHINE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    GPS_INIT=0,
    GPS_WAIT_SIGNAL,
    GPS_GETDATA,
    GPS_CHECK_SIGNAL,
    GPS_RECOVERY,
    GPS_PROCESS,
	GPS_SENDDATA,
	GPS_SENDERRORDATA,
} GPS_State;

typedef struct {
	uint8_t CAN_Error_SenDataCounter;
	uint8_t CAN_Error_SenErrorCounter;
	uint8_t GPS_Error_DataCounter;
}ErrCounter;

void gps_init();
void gps_wait_signal();
void gps_getdata();
void gps_check_signal();
void gps_send_data();
void gps_recovery();
void gps_process();
void send_error_signal();

#endif /* GPS_STATEMACHINE_H_ */
