#define STM32F446xx
#include "stm32f4xx.h"
#include "gpio.h"
#include <stdint.h>

#define sda 7 //
#define scl 6 //
#define dht11 0 //
#define led 13 //


void GPIO_init_clocks(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

}

void GPIO_init_i2c_pins(void){

	GPIOB->MODER &= ~((0b11<<scl*2) | (0b11<<sda*2));
	GPIOC->MODER &= ~ (0b11<<led*2);

	GPIOB->PUPDR &= ~((0b11<<sda*2)| (0b11<<scl*2));
    GPIOB->PUPDR |= ((0b01<<sda*2) | (0b01<<scl*2));

	GPIOB->OTYPER |= ((1<<sda) | (1<<scl));

	GPIOB->OSPEEDR |= ((0b10<<scl*2) | (0b10<<sda*2));

    GPIOB->AFR[0] &= ~((0xF<<scl*4) | (0xF<<sda*4));
	GPIOB->AFR[0] |= ((4<<scl*4) | (4<<sda*4));

	GPIOC->MODER |= (0b01<<led*2);
	GPIOB->MODER |= ((0b10<<scl*2) | (0b10<<sda*2));

}

void GPIO_init_dht11_pin(void){

	GPIOA->MODER &= ~(0b11<<dht11*2);
	GPIOA->PUPDR &= ~(0b11<<dht11*2);
	GPIOA->PUPDR |= (0b01<<dht11*2);
    GPIOA->OTYPER |= (1<<dht11);
	GPIOA->MODER |= (0b01<<dht11*2);

}
