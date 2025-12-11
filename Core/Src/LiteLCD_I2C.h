//
// Created by domin on 1.12.2025.
//

#ifndef LiteLCD_I2C_LCD_H
#define LiteLCD_I2C_LCD_H
#include <stdint.h>

#define I2C_ADDR (0x27 << 1)
#define LCD_ENABLE 0x04
#define BL 0x08

#define LCD_DELAY 3

// commends
#define LCD_CMD_CLEAR_DISPLAY 0x01
#define LCD_CMD_RETURN_HOME 0x02

#define LCD_STATE_BACKLIGHT_ON BL
#define LCD_STATE_BACKLIGHT_OFF 0x00
// display control
#define LCD_STATE_BLINK_CURSOR_ON 0x01
#define LCD_STATE_BLINK_CURSOR_OFF 0x00

#define LCD_STATE_CURSOR_ON 0x02
#define LCD_STATE_CURSOR_OFF 0x00

#define LCD_STATE_DISPLAY_ON 0x04
#define LCD_STATE_DISPLAY_OFF 0x00

#define LCD_DISPLAY_CONTROL 0x08

// function set
#define LCD_STATE_4BITS_MODE 0x00
#define LCD_STATE_8BITS_MODE 0x10

#define LCD_STATE_2LINE 0x08
#define LCD_STATE_1LINE 0x00

#define LCD_STATE_5x10_DOTS 0x04
#define LCD_STATE_5x8_DOTS 0x00

#define LCD_FUNCTION_SET 0x20

// cursor position set
#define LCD_STATE_ROW1 0x80
#define LCD_STATE_ROW2 0xC0

// entry mode set
#define LCD_STATE_CURSOR_RIGHT 0x02
#define LCD_STATE_CURSOR_LEFT 0x00

#define LCD_STATE_SHIFT_ON 0x01
#define LCD_STATE_SHIFT_OFF 0x00

#define LCD_ENTRY_MODE_SET 0x04

// #define LCD_SET_DDRAM_ADDR 0x80
#define LCD_SET_CGRAM_ADDR 0x40

#define LCD_STATE_CGRAM_SLOT_0 0
#define LCD_STATE_CGRAM_SLOT_1 1
#define LCD_STATE_CGRAM_SLOT_2 2
#define LCD_STATE_CGRAM_SLOT_3 3
#define LCD_STATE_CGRAM_SLOT_4 4
#define LCD_STATE_CGRAM_SLOT_5 5
#define LCD_STATE_CGRAM_SLOT_6 6
#define LCD_STATE_CGRAM_SLOT_7 7

void LCD_init(void);
void LCD_SendData(uint8_t data);
void LCD_SendCmd(uint8_t cmd);
void LCD_SendStr(const char* str);

uint8_t LCD_Cmd_DisplayControl(uint8_t state_cursorMode, uint8_t state_blinkMode, uint8_t state_displayMode);
uint8_t LCD_Cmd_FunctionSet(uint8_t state_bitsMode, uint8_t state_line, uint8_t state_dotsMode);
uint8_t LCD_Cmd_SetCursorPosition(uint8_t state_row, uint8_t column);
uint8_t LCD_Cmd_EntryModeSet(uint8_t state_cursorDirection, uint8_t state_displayShift);

void LCD_SetBacklightControl(uint8_t state_backlightMode);void LCD_SetBacklightControl(uint8_t state_backlightMode);
void LCD_SetCustomChar(uint8_t state_location, const uint8_t bits[8]);
#endif //LiteLCD_I2C_LCD_H