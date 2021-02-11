#ifndef SENSOR_H
#define SENSOR_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif
#include <MHZ19.h>
#include <SoftwareSerial.h>

/*********
     * Define
     *********/
#define SENSOR_ID 001

#define MEASU_BUFFER_SIZE 2110

/***************
* Definiciones
***************/
typedef struct medicion
{
    uint16_t valorCo2;
    uint8_t valorTemp;
    time_t fecha;
} co2Measu_t;

void sensorInit();
void sensorAutocal();
co2Measu_t readSensor();

#endif
