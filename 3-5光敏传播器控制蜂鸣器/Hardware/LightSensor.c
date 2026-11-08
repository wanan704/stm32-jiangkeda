#include "stm32f10x.h"                  // Device header
void LightSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	//这里选择上下拉都可以，光敏电阻不遮挡默认输出低电平，选择上下拉在不遮挡情况下13口都是低电平，
	//选择上拉的话，拔掉13口输入线，13口就默认高电平了，
	//蜂鸣器就会一直响，所以只要13口有输入，上下拉都可以
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
uint8_t LightSensor_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}
