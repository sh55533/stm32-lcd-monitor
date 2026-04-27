#ifndef LIQUIDCRYSTAL_I2C_H
#define LIQUIDCRYSTAL_I2C_H

#include "stm32f4xx_hal.h"

#define DEVICE_ADDR  (0x27 << 1)

void HD44780_Init(uint8_t rows);
void HD44780_Clear(void);
void HD44780_SetCursor(uint8_t col, uint8_t row);
void HD44780_PrintStr(const char* str);
void HD44780_Backlight(void);
void HD44780_NoBacklight(void);

#endif
