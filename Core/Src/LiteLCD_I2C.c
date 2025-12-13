//
// Created by domin on 1.12.2025.
//
#include "../Src/LiteLCD_I2C.h"
#include <stdint.h>

// HAL header file for STM32F4 family
// Replace with correct header for other STM32 families
#include "stm32f4xx_hal.h"

static uint8_t _backlight = LCD_BL;
extern I2C_HandleTypeDef hi2c1;

static void _sendBits(uint8_t data) {
    HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR, &data, 1, 100);
}

static void _pulseEnable(uint8_t data) {
    _sendBits(data | LCD_ENABLE);
    _sendBits(data & ~LCD_ENABLE);
}

static void _send4Bits(uint8_t nibble, uint8_t rs) {
    uint8_t data = nibble | _backlight | rs;
    _sendBits(data);
    _pulseEnable(data);
}

// Public functions
void LCD_SendCmd(uint8_t data) {
    _send4Bits(data & 0xF0, 0);
    _send4Bits((data<<4) & 0xF0, 0);
}

// Send a character or a custom char (by CGRAM location)
void LCD_SendData(uint8_t data) {
    _send4Bits(data & 0xF0, 1);
    _send4Bits((data<<4) & 0xF0, 1);
}

// Send string
void LCD_SendStr(const char* str) {
    while (*str != '\0') {
        LCD_SendData(*str);
        str++;
    }
}

// Initializes LCD in 4-bit mode
void LCD_Init(void) {
    // Wait for LCD power-up
    HAL_Delay(50);

    // Wake-up commend
    _send4Bits(0x30, 0);
    HAL_Delay(5);

    _send4Bits(0x30, 0);
    HAL_Delay(5);

    _send4Bits(0x30, 0);
    HAL_Delay(5);

    // Set to 4-bit mode
    _send4Bits(0x20, 0);
    HAL_Delay(5);

    // LCD configuration
    LCD_SendCmd(LCD_FUNCTION_SET | LCD_STATE_4BITS_MODE | LCD_STATE_2LINE | LCD_STATE_5x8_DOTS);
    LCD_SendCmd(LCD_DISPLAY_CONTROL);

    LCD_SendCmd(LCD_CMD_CLEAR_DISPLAY);
    // Delay for CLEAR_DISPLAY command
    HAL_Delay(3);

    LCD_SendCmd(LCD_ENTRY_MODE_SET | LCD_STATE_CURSOR_LEFT | LCD_STATE_SHIFT_OFF);
    LCD_SendCmd(LCD_DISPLAY_CONTROL | LCD_STATE_BLINK_CURSOR_OFF | LCD_STATE_CURSOR_OFF | LCD_STATE_DISPLAY_ON);
}

uint8_t LCD_Cmd_DisplayControl(uint8_t state_cursorMode, uint8_t state_blinkMode, uint8_t state_displayMode) {
    return (LCD_DISPLAY_CONTROL | state_cursorMode | state_blinkMode | state_displayMode);
}

uint8_t LCD_Cmd_FunctionSet(uint8_t state_bitsMode, uint8_t state_line, uint8_t state_dotsMode) {
    return (LCD_FUNCTION_SET | state_bitsMode | state_line) | state_dotsMode;
}

uint8_t LCD_Cmd_SetCursorPosition(uint8_t state_row, uint8_t column) {
    return state_row | column;
}

uint8_t LCD_Cmd_EntryModeSet(uint8_t state_cursorDirection, uint8_t state_displayShift) {
    return (LCD_ENTRY_MODE_SET | state_cursorDirection | state_displayShift);
}

void LCD_SetBacklightControl(uint8_t state_backlightMode) {
    _backlight = state_backlightMode;
}

// Location must be a number between 0 and 7
void LCD_SetCustomChar(uint8_t location, const uint8_t bits[8]) {
    location &= 0x07;
    LCD_SendCmd(LCD_SET_CGRAM_ADDR | (location << 3));
    for (uint8_t i = 0; i < 8; i++) {
        LCD_SendData(bits[i]);
    }
    LCD_SendCmd(0x80);
}