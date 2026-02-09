#define STM32F446xx

#include "stm32f4xx.h"
#include "gpio.h"
#include "i2c.h"
#include <stdint.h>


int main(void){


	GPIO_init_clocks();
	GPIO_init_i2c_pins();
	GPIO_init_dht11_pin();
	I2C_Init();
	SSD1306_Init();

	while(1){
	}
  return 0;
}


