/*
 * gpshandle.h
 *
 *  Created on: Jan 27, 2024
 *      Author: win 10
 */

#ifndef GPSHANDLE_H_
#define GPSHANDLE_H_

#include <stm32f1xx.h>
#include <string.h>
#include <stdlib.h>
#define WGS84_A 6378137.0f
#define WGS84_ECC_SQUARED 0.00669437999014f
#define PI 3.14159265f
/*******************************************************************************
 * @brief GPS data structure for storing parsed data
 ******************************************************************************/
#define RxBuffer_SIZE 64  //configure uart receive buffer size
#define DataBuffer_SIZE 512 //gather a few rxBuffer frames before parsing
typedef struct NMEA_DATA {
	float latitude; //latitude in degrees with decimal places
    char latSide;  // N or S
    float longitude; //longitude in degrees with decimal places
    char lonSide; // E or W
    float altitude; //altitude in meters
    float hdop; //horizontal dilution of precision
    int satelliteCount; //number of satellites used in measurement
    int fix; // 1 = fix, 0 = no fix
    char lastMeasure[10]; // hhmmss.ss UTC of last successful measurement; time read from the GPS module
} GPS;
/*******************************************************************************
 * @brief Parses NMEA data from the GPS module
 * @param gps_data Pointer to GPS struct, writes data to it
 * @param buffer Pointer to buffer string with NMEA data
 ******************************************************************************/
void nmea_parse(GPS *gps_data, uint8_t *buffer);
void ecefToEnu(float x, float y, float z, float latRef, float lonRef,
               float* e, float* n, float* u);
void gpsToEcef(float lat, float lon, float* x, float* y, float* z);
#endif /* GPSHANDLE_H_ */
