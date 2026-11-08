#include "stm32f10x.h"                  // Device header
//打开时钟，配置端口模式
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);
}
void LED1_ON()
{	
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
void LED1_Off()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}
void LED2_ON()
{	
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
void LED2_Off()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}
/**
  * @brief  翻转LED1的状态（操作PA1，低电平点亮）
  */
void LED1_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	else
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
/**
  * @brief  翻转LED2的状态（操作PA2，低电平点亮）
  */
void LED2_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	else
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

