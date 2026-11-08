#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "OLED.h"
#include "Servo.h"
uint8_t KeyMum;
float angle;
int main(void)
{
	OLED_Init();
	Servo_Init();
	OLED_ShowString(1,1,"Angle:");
	while(1)
	{
		KeyMum=Key_GetNum();
		if(KeyMum==1)
		{
			angle+=30;
			if(angle>180)
				angle=0;
		}
		Servo_SetAngle(angle);
		OLED_ShowNum(1,7,angle,3);
	}
}
