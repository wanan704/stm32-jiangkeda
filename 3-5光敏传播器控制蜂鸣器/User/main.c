#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "LightSensor.h"
#include "Buzzer.h"

int main(void)
{
	Buzzer_Init();
	LightSensor_Init();
	
	while(1)
	{
		if(LightSensor_Get()==1)//默认1是暗环境下的高电平
			
		{
			Buzzer_ON();
		}
		else
		{
			Buzzer_Off();
		}
	}
}
