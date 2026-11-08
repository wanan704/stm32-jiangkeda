#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"
int16_t speed;
int main(void)
{
	OLED_Init();
	Timer_Init();
	Encoder_Init();
	OLED_ShowString(1,1,"speed:");
	while(1)
	{
		OLED_ShowSignedNum(1,7,speed,5);
		OLED_ShowSignedNum(2, 1, TIM_GetCounter(TIM3), 5);   // 第 2 行直接显示 CNT 实时值

	}
}
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		speed=Encoder_Get();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
 