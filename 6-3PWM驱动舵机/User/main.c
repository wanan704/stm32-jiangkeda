#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "PWM.h"
int main(void)
{
	OLED_Init();
	PWM_Init();
	while(1)
	{
		//占空比影响的是灯的亮度。占空比等于CCR/ARR+1.占空比最大是1，此时ARR+1=100。所以CCR直接等于占空比
		for(int i=0;i<=100;i++)
		{
			PWM_SetComparel(i);
			Delay_ms(10);
		}
		for(int i=100;i>=0;i--)
		{
			PWM_SetComparel(i);
			Delay_ms(10);
		}
	}
}
