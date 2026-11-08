#include "stm32f10x.h"                  // Device header
//1、配置RCC 2、配置GPIO口为输入模式 3、配置AFIO， 4、配置EXTI，选择边沿触发方式， 
//5、选择触发响应方式， 6、配置NVIC，选择合适的中断优先级
//配置好之后跳转到中断函数，所以要开始写中断函数
uint16_t CountSensor_Count=0;
void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//看参考手册确定配置什么模式 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

uint16_t CountSensor_Count_Get(void)
{
	return CountSensor_Count;
}
void EXTI15_10_IRQHandler(void)
{
	if( EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		CountSensor_Count++;
	//中断程序结束后一定要调用清除中断标志位的函数，因为只要中断标志位置为1，程序就会跳到中断函数
	//不清除中断标志位他就会一直申请
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	
}