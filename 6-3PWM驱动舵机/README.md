# 6-3 PWM 驱动（实际是呼吸灯）

> **章节** 6-3 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

TIM2_CH1 输出 PWM，CCR 从 0 扫到 100 再扫回来，做出呼吸灯效果。
PWM 频率 1 kHz，占空比 = CCR / (ARR+1)。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| LED | PA15 | TIM2_CH1 重映射到 PA15，需 `GPIO_PartialRemap1_TIM2` |
| 调试口 | — | PA15 默认是 JTDI，需 `GPIO_Remap_SWJ_JTAGDisable` 释放 |

## 现象

外接 LED 由暗逐渐变亮，再逐渐变暗，循环往复。

## 关键代码

```c
TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1;		// 72MHz/720 = 100kHz
TIM_TimeBaseInitStruct.TIM_Period    = 100 - 1;		// 100kHz/100 = 1kHz
TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
TIM_OCInitStructure.TIM_Pulse       = 0;		// CCR
TIM_OC1Init(TIM2, &TIM_OCInitStructure);
TIM_Cmd(TIM2, ENABLE);
```

## 备注

**目录名和内容对不上**：这个目录叫"驱动舵机"，`main.c` 实际做的是呼吸灯（0~100 占空比扫描）；真正的舵机程序在 **6-4** 目录里，两个正好互换了，看代码时别被目录名带偏。

PA15 是 JTAG 的 JTDI 脚，必须调 `GPIO_Remap_SWJ_JTAGDisable` 才能当普通 IO 用；这一步只关 JTAG、保留 SWD，所以下载不受影响。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。