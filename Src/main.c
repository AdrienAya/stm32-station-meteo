

#include "stm32f4xx.h"
#include "gpio.h"
#include "i2c.h"
#include <stdint.h>


int main(void){

	I2C_Init();
	GPIO_init_clocks();
	GPIO_init_i2c_pins();

	while(1){
	}
  return 0;
}


