
#include "pantalla.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void displyInit()
{
    u8g2.begin();
    u8g2.clearBuffer();
    displaySetFont(u8g2_font_crox3tb_tf);
}

void displayPrint(char *str)
{
    u8g2.print(str);
    u8g2.sendBuffer();
}

void displayClear()
{
  u8g2.clearBuffer();
}

void displayPrintXY(int x, int y, char *str)
{
    u8g2.drawStr(x, y, str);
    u8g2.sendBuffer();
}

void displaySetFont(const uint8_t *fuente)
{
    u8g2.setFont(fuente);
}
