# 6-7 PWMI 模式测频率占空比

> **章节** 6-7 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

用 `TIM_PWMIConfig()` 一次配置两个通道：CH1 测周期（TI1FP1），CH2 自动映射到另一相测高电平时间（TI2FP2）。
理论上可以同时算出频率和占空比。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 被测信号 | PA6 | TIM3_CH1 / CH2 复用同一引脚（PWMI 模式） |
| 信号源（自测） | PA15 | TIM2_CH1 PWM 输出 |

## 现象

OLED 只显示 Freq（约 1 kHz），**没有显示占空比** —— 这份 `main.c` 和 6-6 完全一样。

## 关键代码

```c
TIM_PWMIConfig(TIM3, &TIM_ICInitStructure);	// 一次配好 CH1 + CH2

// 频率：1MHz / (CCR1 + 1)
// 占空比：CCR2 / (CCR1 + 1)
```

## 备注

**这个工程还没做完**：`IC.c` 只实现了 `IC_GetFreq()`，没有 `IC_GetDuty()`，`main.c` 里也只显示频率。

想补完的话，在 `IC.h` 加 `uint32_t IC_GetDuty(void);`，实现为：

```c
uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1);
}
```

注意 `+1`：CNT 是从 0 数到 CCR，实际周期是 CCR1+1 个计数。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。