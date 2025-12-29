# LiteLCD_I2C
Dedicated to the STM32 microcontroller family. This library was created to simplify working with an HD44780 LCD display equipped with a PCF8574 I2C module. It allows you to operate the display easily while maintaining control and optimization.

This library is **not recommended for commercial use**.

## Supported Hardware
- STM32 microcontrollers (any family using HAL)
- HD44780 - compatible LCD displays
- PCF8574 I2C I/O expander

## Requirements
- STM32 HAL library
- Configured I2C peripheral

## Installation
1. Clone or copy this repository into your project  
2. Include the header file in your source code:  
   `#include "LiteLCD_I2C.h"`  
3. Open LiteLCD_I2C.c and replace:  
  `#include "stm32f4xx_hal.h`  
  with the correct HAL header for your MCU:  
  `#include "stm32yyxx_hal.h"`  
  Where:  
  yy - STM32 family (e.g. f1, f4, g0, h7)  
4. Set the correct I2C slave address in LiteLCD_I2C.h:  
  `#define I2C_ADDR (0x27 << 1)`  
  where:  
  `0x27` - PCF8574 device address  
  `<< 1` -  is required by STM32 HAL.  

## Initialization
`void LCD_Init(void);` - Initializes the LCD controller and performs the required startup delays.  

## Public Functions
`void LCD_SendData(uint8_t data);` - Sends a single character or a custom CGRAM character.  
`void LCD_SendCmd(uint8_t cmd);` - Sends a raw LCD command.  
`void LCD_SendStr(const char* str);` - High-level function for sending strings (terminated with `\0`) to the display.  

## Command Helper Functions
`uint8_t LCD_Cmd_Xxx(y);` - High-level helper function that modified internal macro states and returns a command byte to be sent.  
`void LCD_SetXxx(y);` - High-level function that modifies LCD configuration states internally.  
Where:  
`Xxx` - command name,  
`y` - command argument/s.  

## Notes
Blocking delays are used only during LCD initialization.  
No dynamic memory allocation is used.  
I2C communication is master-only.  
The API is intentionally minimal.  
