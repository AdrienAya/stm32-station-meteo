#include "stm32f4xx.h"
#include <stdint.h>

void DHT11_Init_Timer(void);
void TIM2_Count_reset(void);
uint32_t TIM2_Get_Micros(void);
void DHT11_Input(void);
void DHT11_Output(void);
void DHT11_Start(void);
void DHT11_Wait_Response(void);
uint16_t DHT11_Parse(void);
uint8_t DHT11_Read_Byte(void)
#define Frequency_APB1 90


typedef struct{

	uint8_t temperature;
	uint8_t humidity;
}DHT11_Data;

