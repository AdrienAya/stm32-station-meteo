

#include "stm32f4xx.h"
#include <stdint.h>

#define addr_lcd (0x3C << 1) | 0

void I2C_Init(void);
void I2C_Start(void);
void I2C_Write_Data(uint8_t data);
void I2C_Write_Addr(uint8_t addr);
void I2C_Stop(void);


