# 5-1 对射式红外传感器计次

> **章节** 5-1 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

第一个外部中断实验：红外对射传感器的 DO 接 PB14，用 **EXTI 下降沿中断** 数遮挡次数。
中断里只做 `Count++`，主循环负责刷 OLED。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 红外传感器 DO | PB14 | 上拉输入（IPU），遮挡时输出低 → 下降沿 |
| 红外传感器 VCC/GND | 3V3 / GND | 必须共地 |

## 现象

挡一次光路，OLED 上的 Count 加 1；挡得越快加得越快。

## 关键代码

```c
GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

EXTI_InitStructure.EXTI_Line    = EXTI_Line14;
EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
EXTI_Init(&EXTI_InitStructure);

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		CountSensor_Count++;
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}
```

## 备注

**中断计数是 CPU 一个一个数**：每个脉冲都要进一次中断。挡光片这种低频场合完全够用，但脉冲一密（电机测速几十 kHz）就会排队、丢数 —— 那种场合要换定时器外部时钟（6-2）或编码器接口（6-8）。

**别忘了** `RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE)`，外部中断必须开 AFIO 时钟。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。