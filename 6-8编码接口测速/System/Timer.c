#include "stm32f10x.h"                  // Device header

void Timer_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 10000-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	//使能更新中断
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//避免刚初始化完就进中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn;      // TIM2 中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  // 抢占优先级 2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         // 响应优先级 1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);  
}
//中断函数
//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
//	{
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//}
