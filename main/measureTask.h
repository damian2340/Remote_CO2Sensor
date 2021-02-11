#include "sensor.h"

typedef enum
{
    ErrorMeasure = -0x01,
    IdleFanOn = 0x00,
    IdleFanOff = 0x02,
    BusyMeasureSave = 0x04,
    BusyMeasureTemp = 0x08,
} taskMeasureState_t;

void measureTask();
void fanOff();
void fanON();
void fan50();
co2Measu_t readFirstMeasure();
void eraseFirstMeasure();
void saveMeasure();
int measuSize();
boolean isMeasurenet();
