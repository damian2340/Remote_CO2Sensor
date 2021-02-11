#include "hardwareConfig.h"
#include "pantalla.h"
#include "buttonTask.h"
#include "measureTask.h"

extern taskButonState_t ButtonState;
const char c = '°';
taskMeasureState_t measureState = ErrorMeasure;
//bufer circular
co2Measu_t co2Measurements[MEASU_BUFFER_SIZE];
unsigned int measuIndex = 0;
unsigned int measuLength = 0;

void measureTask()
{
    static unsigned int count = 0;
    static char str[10];
    switch (measureState)
    {
    case IdleFanOn:
        if (count < 9)
        {
            fanON();
        }
        else
        {
            measureState = IdleFanOff;
        }
        count++;
        break;
    case IdleFanOff:
        fanOff();
        measureState = BusyMeasureTemp;
        count++;
        break;
    case BusyMeasureTemp:
        if (count == 11)
        {
            displaySetFont(u8g2_font_crox4tb_tf);
        }
        if(ButtonState == ReleasedButtonState){
          displayClear();
          sprintf(str, "%dppm", readSensor().valorCo2);
          displayPrintXY(20, 24, str);
          sprintf(str, "%2d %cC", readSensor().valorTemp, c);
          displayPrintXY(20, 48, str);
        }
        if (count == 98)
        {
            measureState = BusyMeasureSave;
        }
        count++;
        break;
    case BusyMeasureSave:
        saveMeasure();
        measureState = IdleFanOn;
        count = 0;
        break;
    case ErrorMeasure:
        measureState = IdleFanOn;
        break;
    default:;
    }
}

void fanOff()
{
    digitalWrite(FAN_PIN, LOW);
}

void fanON()
{
    digitalWrite(FAN_PIN, HIGH);
}

co2Measu_t readFirstMeasure()
{
    int origen = measuIndex - measuLength;
    if (origen >= 0)
    {
        return co2Measurements[origen];
    }
    else
    {
        return co2Measurements[(MEASU_BUFFER_SIZE + measuIndex) - (measuLength)];
    }
}

void eraseFirstMeasure()
{
    measuLength--;
}

void saveMeasure()
{
    co2Measu_t med = readSensor();
    if (measuLength < MEASU_BUFFER_SIZE - 1)
    {
        if (measuIndex < MEASU_BUFFER_SIZE)
        {
            co2Measurements[measuIndex] = med;
        }
        else
        {
            co2Measurements[0] = med;
        }
        measuIndex++;
        measuLength++;
    }
    else
    {
        displayPrint("Memoria llena");
    }
}

int measuSize()
{
    return measuLength;
}

boolean isMeasurenet()
{
    if (measuLength == 0)
        return false;
    return true;
}
