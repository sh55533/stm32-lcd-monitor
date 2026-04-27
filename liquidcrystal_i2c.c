#include "liquidcrystal_i2c.h"
#include "i2c.h"
extern I2C_HandleTypeDef hi2c1;

#define LCD_BACKLIGHT    0x08
#define LCD_NOBACKLIGHT  0x00
#define EN  0x04
#define RS  0x01

#define LCD_CLEARDISPLAY  0x01
#define LCD_RETURNHOME    0x02
#define LCD_ENTRYMODESET  0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_FUNCTIONSET   0x20
#define LCD_SETDDRAMADDR  0x80
#define LCD_ENTRYLEFT     0x02
#define LCD_DISPLAYON     0x04
#define LCD_CURSOROFF     0x00
#define LCD_BLINKOFF      0x00
#define LCD_4BITMODE      0x00
#define LCD_2LINE         0x08
#define LCD_5x8DOTS       0x00

static uint8_t backlight = LCD_BACKLIGHT;

static void ExpanderWrite(uint8_t data) {
    uint8_t d = data | backlight;
    HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDR, &d, 1, 10);
}

static void PulseEnable(uint8_t data) {
    ExpanderWrite(data | EN);
    HAL_Delay(1);
    ExpanderWrite(data & ~EN);
    HAL_Delay(1);
}

static void Write4Bits(uint8_t value) {
    ExpanderWrite(value);
    PulseEnable(value);
}

static void SendCommand(uint8_t cmd) {
    Write4Bits(cmd & 0xF0);
    Write4Bits((cmd << 4) & 0xF0);
}

static void SendChar(uint8_t ch) {
    Write4Bits((ch & 0xF0) | RS);
    Write4Bits(((ch << 4) & 0xF0) | RS);
}

void HD44780_Init(uint8_t rows) {
    HAL_Delay(50);
    ExpanderWrite(backlight);
    HAL_Delay(1000);

    Write4Bits(0x30);
    HAL_Delay(5);
    Write4Bits(0x30);
    HAL_Delay(5);
    Write4Bits(0x30);
    HAL_Delay(1);
    Write4Bits(0x20);
    HAL_Delay(1);

    SendCommand(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS);
    SendCommand(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
    SendCommand(LCD_CLEARDISPLAY);
    HAL_Delay(2);
    SendCommand(LCD_ENTRYMODESET | LCD_ENTRYLEFT);
    HAL_Delay(1);
}

void HD44780_Clear(void) {
    SendCommand(LCD_CLEARDISPLAY);
    HAL_Delay(2);
}

void HD44780_SetCursor(uint8_t col, uint8_t row) {
    uint8_t offsets[] = {0x00, 0x40};
    SendCommand(LCD_SETDDRAMADDR | (col + offsets[row]));
}

void HD44780_PrintStr(const char* str) {
    while (*str) {
        SendChar((uint8_t)(*str));
        str++;
    }
}

void HD44780_Backlight(void) {
    backlight = LCD_BACKLIGHT;
    ExpanderWrite(0);
}

void HD44780_NoBacklight(void) {
    backlight = LCD_NOBACKLIGHT;
    ExpanderWrite(0);
}
