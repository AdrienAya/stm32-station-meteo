#define STM32F446xx

#include "stm32f4xx.h"
#include "i2c.h"
#include <stdint.h>

#define addr_lcd (0x3C << 1) | 0

void I2C_Init(void){

	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	I2C1->CR2 = 45;
	I2C1->CR1 = 225;
	I2C1->TRISE = 46;
	I2C1->CR1 |= I2C_CR1_PE;
	I2C1->CR1 |= I2C_CR1_ACK;
}

void I2C_Start(void){

	while (I2C1->SR2 & I2C_SR2_BUSY);

	I2C1->CR1 |= I2C_CR1_START;

	while(!(I2C1->SR1 & I2C_SR1_SB));

}

void I2C_Write_Addr(uint8_t addr){

	while (I2C1->SR2 & I2C_SR2_BUSY);

	I2C1->DR = addr;

	while (!(I2C1->SR1 & I2C_SR1_ADDR));

	(void)I2C1->SR1;
    (void)I2C1->SR2;

}

void I2C_Stop(void){

	I2C1->CR1 |= I2C_CR1_STOP;

}


void I2C_Write_Data(uint8_t data){

	while(!(I2C1->SR1 & I2C_SR1_TXE));
	I2C1->DR = data;

}

