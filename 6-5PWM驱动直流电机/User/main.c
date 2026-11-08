#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Motor.h"
uint8_t KeyNum
int16_t speed
int main(void)
{
	OLED_Init();
	Motor_Init();
	Key_Init();
	//Motor_SetSpeed(20);
	OLED_ShowString(1,1,"Speed:");
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			speed+=20;
			if(speed>100)
				speed=-100;
		}
		Motor_SetSpeed(speed);
		OLED_ShowNum(1,7,speed,3);//先是参数，后是长度
	}
}
