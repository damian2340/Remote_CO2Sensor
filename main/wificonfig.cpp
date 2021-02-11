#include "wificonfig.h"
#include "pantalla.h"
#include "reloj.h"

ESP8266WiFiMulti WiFiMulti;

void wifiInit()
{

    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(STASSID, STAPSK);
    unsigned long timeout = millis() + 10000;

    displayClear();
    displayPrintXY(0, 20, "Conectando\n\r");
    while (WiFi.status() != WL_CONNECTED)
    {
        if (timeout < millis())
        {
            break;
        }
        displayPrint(".");
        delay(600);
    }
    displayClear();
    if (WiFi.status() == WL_CONNECTED)
    {
        displayPrintXY(0, 20, "Conectado");
    }
    else
    {
        displayPrintXY(0, 20, "Desconectado");
    }
}
