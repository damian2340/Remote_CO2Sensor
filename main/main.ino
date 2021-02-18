#include "hardwareConfig.h"
#include "pantalla.h"
#include "wificonfig.h"
#include "reloj.h"
#include "buttonTask.h"
#include "measureTask.h"
#include "systemCO2.h"

/*** variables globales ***/
//stateMachine_t stateMachine = ErrorSM;
extern taskButonState_t ButtonState;
extern taskMeasureState_t measureState;

const char *server = "http://co2.df.uba.ar";
//const char *server = "http://sensors-api-uba.herokuapp.com";

char data[64];

extern MHZ19 sensor;
static esp8266::polledTimeout::periodicMs taskPeriod(600);

void setup()
{

    pinMode(FAN_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);

    Serial.begin(115200);

    displyInit();
    displaySetFont(u8g2_font_crox3tb_tf);
    displayPrintXY(0, 20, "Pantalla ok\n\r");
    delay(1200);

    timeZoneConfig();
    displayPrintXY(0, 40, "Reloj ok\n\r");
    delay(1200);

    sensorInit();
    displayPrintXY(0, 60, "Sensor ok\n\r");
    delay(2000);
    
    wifiInit();
}

void loop()
{
    // Las tareas actualizan los estados para la maquina
    if (taskPeriod)
    {
        checkButtonTask();
        measureTask();
        if(isMeasurenet())
        {
            if (WiFi.status() == WL_CONNECTED)
            {
                displaySetFont(u8g2_font_t0_18_tn);
                displayPrintXY(5, 64, "Conectado y enviando");
                co2Measu_t datosSensor = readFirstMeasure();
                //formato de la fecha a mandar es yyyyMMddhhmmss o sea 14 caracteres y con el caracter de fin necesito 15 bytes
                char fechaMedicion[15];
                //No tengo ganas de pensar un nombre mejor para formatear la fecha.
                timeFormat4y2M2d2h2m2s(datosSensor.fecha, fechaMedicion);
                WiFiClient client;
                HTTPClient http;
                Serial.print("[HTTP] begin...\n");
                sprintf(data, "%s/save?sensorid=%03d&time=%s&value=%d", server, SENSOR_ID, fechaMedicion, datosSensor.valorCo2);
                Serial.println(data);
                if (http.begin(client, data))
                { // HTTP
                    Serial.print("[HTTP] GET...\n");
                    // start connection and send HTTP header
                    int httpCode = http.GET();
                    Serial.print("HTTPCODE: ");
                    Serial.println(httpCode);
                    // httpCode will be negative on error
                    if (httpCode > 0)
                    {
                        // file found at server
                        if (httpCode == 200)
                        {
                            eraseFirstMeasure();
                            Serial.println("Recepcion OK");
                        }
                    }
                    else
                    {
                        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
                    }
                    http.end();
                }
                else
                {
                    Serial.printf("[HTTP] Unable to connect\n");
                }
            }
            else
            {
                wifiInit();
                displaySetFont(u8g2_font_t0_18_tn);
                displayPrintXY(5, 48, "Desconectado");
            }
        }
    }
}

void taskError()
{
    displayPrintXY(0, 20, "Error\n\rReinicie");
}

void resetSystem()
{
    ButtonState = ReleasedButtonState;
    measureState = ErrorMeasure;
    setup();
}
