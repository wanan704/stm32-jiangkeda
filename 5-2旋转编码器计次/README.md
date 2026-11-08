# 5-2 旋转编码器计次

> **章节** 5-2 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

EC11 旋转编码器计数：A/B 两相分别接 PB0、PB1，两路都配下降沿中断。
中断里读另一相的电平来判断方向 —— 另一相为低说明它先变，是左转；为高说明本相先变，是右转。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 编码器 A 相 | PB0 | 上拉输入，EXTI0 下降沿 |
| 编码器 B 相 | PB1 | 上拉输入，EXTI1 下降沿 |
| 编码器 VCC/GND | 3V3 / GND | 模块型必须接，只接 A/B 没信号 |

## 现象

右转数字 +1，左转数字 -1，OLED 用带符号方式显示。

## 关键代码

```c
void EXTI0_IRQHandler(void)			// A 相下降沿
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)	// B 为低 → 左转
			Encoder_Count--;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
```

## 备注

**踩过的坑：从 0 左转不显示 -1，而是 +65535。**
计数器全链路都是 `uint16_t`，无符号数 0-1 会按模 2^16 回绕成 65535；传到 `OLED_ShowSignedNum(int32_t)` 时它已经是正数了，所以显示 `+65535`。

要改的 5 处必须一起改成 `int16_t`：`main.c` 的 `Num`、`Encoder.c` 的 `Encoder_Count`、`Encoder_Get` 返回值、`temp` 局部变量、`Encoder.h` 的声明。只改 `main.c` 的话负号在中途就被洗掉了。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。