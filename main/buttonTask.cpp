#include "hardwareConfig.h"
#include "systemCO2.h"
#include "pantalla.h"
#include "buttonTask.h"
#include "sensor.h"

taskButonState_t ButtonState = ReleasedButtonState;

/**
 * Control periodico del estado del boton,
 * Esta tarea cambia de estado segun el tiempo quie se menatiene presionado el boton.
 * 
 * */
void checkButtonTask()
{
    static unsigned int buttonPressingCount = 0;
    if (digitalRead(BUTTON_PIN) == LOW)
    {
        buttonPressingCount++;
        if (buttonPressingCount > 2 && buttonPressingCount <= 10)
        {
            displaySetFont(u8g2_font_crox4tb_tf);
            displayClear();
            displayPrintXY(10,20,"Suelte para:\n\r");
            displayPrintXY(10,54,"Auto Cal...");
            ButtonState = AutoCalButtonState;
        }
        else if (buttonPressingCount > 10 && buttonPressingCount <= 20)
        {
            displaySetFont(u8g2_font_crox4tb_tf);
            displayClear();
            displayPrintXY(10,20,"Suelte para:\n\r");
            displayPrintXY(10,54,"Reset...");
            ButtonState = ResetButtonState;
        }
        else if (buttonPressingCount > 20 && buttonPressingCount <= 30)
        {
            displaySetFont(u8g2_font_crox4tb_tf);
            displayClear();
            displayPrintXY(5,20,"Suelte para:\n\r");
            displayPrint("Cancelar");
            ButtonState = ReleasedButtonState;
        }
    }
    else
    {
        buttonPressingCount = 0;
        switch (ButtonState)
        {
        case AutoCalButtonState:
            sensorAutocal();
            break;
        case ResetButtonState:
            resetSystem();
            break;
        default:;
        }
        ButtonState = ReleasedButtonState;
    }
}
