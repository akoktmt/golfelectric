/*
 * GPS_StateMachine.c
 *
 *  Created on: Jan 27, 2024
 *      Author: win 10
 */

#include "GPS_StateMachine.h"
#include "gpshandle.h"
#include "CAN_Handle.h"
#include "usart.h"
#include "can.h"
extern uint16_t oldPos;
extern uint16_t newPos;
extern uint8_t RxBuffer[RxBuffer_SIZE];
extern uint8_t DataBuffer[DataBuffer_SIZE];
extern GPS myData;
extern GPS_State gpsstate;
extern uint8_t Signalready;
extern uint8_t IsValid;
extern ErrCounter ErrCnt;
uint8_t Lat[4];
uint8_t Long[4];
uint32_t combine_ids(uint8_t id1, uint8_t id2) ;
extern uint8_t Data[8];
//	GPS_INIT,
//    GPS_WAIT_SIGNAL,
//    GPS_GETDATA,
//    GPS_CHECK_SIGNAL,
//    GPS_SEND_DATA,
//    GPS_RECOVERY,
//    GPS_PROCESS,
//    SEND_ERROR_SIGNAL
void gps_wait_signal() {
	while(Signalready==0);
	gpsstate=GPS_GETDATA;
}

void gps_getdata() {
	nmea_parse(&myData, DataBuffer);
	gpsstate=GPS_CHECK_SIGNAL;
}

void gps_check_signal() {
	if(myData.fix==1){
		if(myData.latitude > -90.0 && myData.latitude !=0 && myData.latitude < 90.0 && myData.latitude !=0 && myData.longitude > -180.0 && myData.longitude < 180.0) {
			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_SET);
			gpsstate=GPS_PROCESS;
		}
		else{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
			gpsstate=GPS_SENDERRORDATA;
		}
	}
	else{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
		gpsstate=GPS_SENDERRORDATA;
	}
}
//int Serialcnt=0;
//char str[50];
void gps_recovery() {
	if(ErrCnt.GPS_Error_DataCounter==5){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
			HAL_Delay(2000);
			NVIC_SystemReset();
		}
		else if(ErrCnt.CAN_Error_SenDataCounter==3){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_CAN_ResetError(&hcan);
			gpsstate=GPS_GETDATA;
		}
		else if(ErrCnt.CAN_Error_SenErrorCounter==3){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_CAN_ResetError(&hcan);
			gpsstate=GPS_GETDATA;
		}
		else if(ErrCnt.GPS_Error_DataCounter==5||ErrCnt.CAN_Error_SenDataCounter==6||ErrCnt.CAN_Error_SenErrorCounter==6){
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
			HAL_Delay(2000);
		}
	gpsstate=GPS_GETDATA;
}

void gps_process(){
	float2Bytes(Lat,myData.latitude);
	float2Bytes(Long,myData.longitude);
	Data[0]=Lat[0];
	Data[1]=Lat[1];
	Data[2]=Lat[2];
	Data[3]=Lat[3];
	Data[4]=Long[0];
	Data[5]=Long[1];
	Data[6]=Long[2];
	Data[7]=Long[3];
//	char * str = (char*)malloc(sizeof(char)*200);
//		          sprintf(str, "\r\n%d: Lat: %f %c, Lon: %f %c, Alt: %f m, Satellites: %d HDOP: %f\r\n",
//		                  Serialcnt, myData.latitude, myData.latSide, myData.longitude, myData.lonSide, myData.altitude, myData.satelliteCount, myData.hdop);
//		          HAL_UART_Transmit(&huart3, (uint8_t *)str, strlen(str), 1000);
	gpsstate=GPS_SENDDATA;
}
void send_error_signal() {
	if(CAN_HandleSendData(0x207,Data,8)==HAL_OK){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
			gpsstate=GPS_GETDATA;
			}
			else
			{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
				ErrCnt.CAN_Error_SenErrorCounter++;
				if(ErrCnt.CAN_Error_SenErrorCounter==3||ErrCnt.CAN_Error_SenErrorCounter==6){
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
					gpsstate=GPS_RECOVERY;
				}
				else{
					gpsstate=GPS_GETDATA;
				}
			}
}
void gps_send_data() {
	if(CAN_HandleSendData(0x207,Data,8)==HAL_OK){
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_SET);
			gpsstate=GPS_GETDATA;
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
			ErrCnt.CAN_Error_SenDataCounter++;
			if(ErrCnt.CAN_Error_SenDataCounter==3||ErrCnt.CAN_Error_SenDataCounter==6){
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,GPIO_PIN_SET);
				gpsstate=GPS_RECOVERY;
			}
			else{
				gpsstate=GPS_GETDATA;
			}
		}
}
uint32_t combine_ids(uint8_t id1, uint8_t id2) {

    uint32_t combined_id = ((uint16_t)id1 << 5) | (id2 & 0x1F);

    return combined_id;
}
