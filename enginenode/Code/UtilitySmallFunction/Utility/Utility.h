/*
 * Utility.h
 *
 *  Created on: Jun 26, 2023
 *      Author: vanti
 */

#ifndef UTILITY_UTILITY_H_
#define UTILITY_UTILITY_H_
#include "stdint.h"

void reverseStr(char* str, int len);

int intToStr(int x, char str[], int d);

int quick_pow10(int n);
int FloatToStr(float n, char* res, int afterpoint);
float StrToFloat(char *string);
float bytes2Float(uint8_t bytes[4]);
void float2Bytes( uint8_t bytes_temp[4],float float_variable);

#endif /* UTILITY_UTILITY_H_ */
