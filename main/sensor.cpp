#include "hardwareConfig.h"
#include "sensor.h"
#include "pantalla.h"
#include "reloj.h"

MHZ19 sensor;

SoftwareSerial uartSensor(RX_PIN, TX_PIN);

void sensorInit()
{
  uartSensor.begin(SENSOR_BAUDRATE);
  sensor.begin(uartSensor);
}

void sensorAutocal()
{
  sensor.autoCalibration();
}

co2Measu_t readSensor()
{
  co2Measu_t ret;
  ret.valorCo2 = sensor.getCO2();
  ret.valorTemp = sensor.getTemperature();
  ret.fecha = timeNow();

  return ret;
}
