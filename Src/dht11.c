#define STM32F446xx

#include "stm32f4xx.h"
#include <stdint.h>

#define Frequency_APB1 90

typedef struct{

	uint8_t temperature;
	uint8_t humidity;
}DHT11_Data;

void DHT11_Init_Timer(void){

	RCC->APB1ENR |= (1<<0);

	TIM2->PSC = Frequency_APB1 -1;
    TIM2->ARR = 0XFFFFFFFF;
    TIM2->CR1 |= (1<<0);
}

void TIM2_Count_Reset(void){

	TIM2->CNT = 0;
}

uint32_t TIM2_Get_Micros(void){

     return TIM2->CNT;
}

void DHT11_Input(void){

	GPIOA->MODER &= ~(0b11<<0*2);
	GPIOA->MODER |= (0b00<<0*2);

}
void DHT11_Output(void){

	GPIOA->MODER &= ~(0b11<<0*2);
	GPIOA->MODER |= (0b01<<0*2);

}

uint8_t DHT11_Read(void){

	if(GPIOA->IDR &(1<<0)){

		return 1;
	}
	else{

		return 0;
	}
}

void DHT11_Write(uint8_t value){


     if(value==1){
    	 GPIOA->ODR |= (1<<0);
     }
     else{
    	 GPIOA->ODR &= ~(1<<0);
     }
}

void DHT11_Start(void){
	DHT11_Output(); // gpioa 0b01 mode output
	DHT11_Write(0); //pin gpioa gnd // 0 fermer
	TIM2_Count_Reset();
	while(TIM2_Get_Micros() < 18000);
	DHT11_Write(1); //pin gpioa 3v3 // 1 ouvert
	DHT11_Input(); // 0b00 mode input
	TIM2_Count_Reset();

}

uint8_t DHT11_Wait_Response(void){

	TIM2_Count_Reset();
	while(DHT11_Read() == 1 && TIM2_Get_Micros() < 100);
	if(TIM2_Get_Micros() > 100){
		return;
	  }
	TIM2_Count_Reset();
	while(DHT11_Read() == 0 && TIM2_Get_Micros() < 100);
    if(TIM2_Get_Micros() > 100){
		return;
	  }
	TIM2_Count_Reset();
	while(DHT11_Read() == 1 && TIM2_Get_Micros() < 100);
    if(TIM2_Get_Micros() > 100){
		return;
	  }
}

uint8_t DHT11_Parse(DHT11_Data *data){
uint8_t datas[5];
uint8_t check;

	for(uint8_t i = 0; i<5;i++){

		datas[i] = DHT11_Read_Byte();

	}

	check = datas[0]+datas[1]+datas[2]+datas[3];

	if(datas[4] == check){

	data->humidity = datas[0];
	data->temperature = datas[2];
	return 1;
	}
	else{
		return 0;
	}
}

uint8_t DHT11_Read_Byte(void){
	    uint8_t byte = 0;

	    for(uint8_t i = 0; i < 8; i++) {

	        while(DHT11_Read() == 0);


	        TIM2->CNT = 0;


	        while(DHT11_Read() == 1);


	        uint32_t duration = TIM2->CNT;


	        byte = byte << 1;

	        if(duration > 40) {
	            byte = byte | 1;
	        }
	    }

	    return byte;
	}
