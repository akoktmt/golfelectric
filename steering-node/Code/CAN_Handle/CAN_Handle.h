/*
 * CAN_Handle.h
 *
 *  Created on: Dec 22, 2023
 *      Author: win 10
 */

#ifndef CAN_HANDLE_H_
#define CAN_HANDLE_H_
#include "main.h"
HAL_StatusTypeDef CAN_HandleSendData(const uint32_t arbitration_id,
                           const uint8_t* data, const uint8_t size);
void CAN_Config_filtering(uint8_t FilterBank, uint16_t NodeID);
void float2Bytes(uint8_t bytes_temp[4],float float_variable);
float bytes2Float(uint8_t bytes[4]);
void float2Bytes( uint8_t bytes_temp[4],float float_variable);
#endif /* CAN_HANDLE_H_ */
