# 6-6 输入捕获模式测频率

> **章节** 6-6 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

TIM3_CH1 做输入捕获，配合从模式复位：每次上升沿把 CNT 清零并把值锁进 CCR1，
相邻两个上升沿之间的计数值就是**一个周期**，频率 = 计数时钟 / CCR1。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 被测信号 | PA6 | TIM3_CH1，上升沿捕获 |
| 信号源（自测） | PA15 | TIM2_CH1 PWM 输出，接到 PA6 即可自测 |

## 现象

OLED 显示 Freq，默认约 1 kHz（PWM 输出 1 kHz、占空比 50%）。

## 关键代码

```c
TIM_ICInitStructure.TIM_Channel     = TIM_Channel_1;
TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
TIM_ICInitStructure.TIM_ICFilter    = 0xF;
TIM_ICInit(TIM3, &TIM_ICInitStructure);

TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);		// 每次捕获自动清零 CNT

// 计数时钟 = 72MHz / 720 = 1MHz
return 1000000 / TIM_GetCapture1(TIM3);
```

## 备注

测频公式成立的前提是**计数时钟 1 MHz**（`PSC=720-1`）。被测频率越高，CCR1 越小、误差越大；测几十 kHz 以上要把 PSC 调小（比如 `72-1` → 10 MHz），公式里的除数也跟着换。

`TIM_SlaveMode_Reset` 是关键：捕获的瞬间硬件自动把 CNT 清零，所以 CCR1 直接就是周期，不用自己做减法。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。