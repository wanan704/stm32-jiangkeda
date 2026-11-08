# 6-1 定时器定时中断

> **章节** 6-1 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

TIM2 用内部时钟做 1 Hz 更新中断，中断里让 `NUM++`，OLED 显示这个数。
这是"用硬件定时器替代 `Delay_ms`"的标准写法。

## 现象

OLED 上的 NUM 每 1 秒加 1。

## 关键代码

```c
TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;	// 72MHz / 7200 = 10kHz
TIM_TimeBaseInitStruct.TIM_Period    = 10000 - 1;	// 10kHz / 10000 = 1Hz

TIM_ClearFlag(TIM2, TIM_FLAG_Update);			// 先清标志，避免初始化完立刻误进中断
TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
TIM_Cmd(TIM2, ENABLE);					// 真正启动计数
```

## 备注

**最容易漏的是最后那句 `TIM_Cmd(TIM2, ENABLE)`** —— 前面配时基、配中断、配 NVIC 都只是设参数，不开这一句 CNT 永远不会走，NUM 一直显示 00000。

另一个细节：`TIM_ClearFlag` 要放在 `TIM_ITConfig` **之前**，否则刚初始化就可能立刻进一次中断。

`TIM2_IRQHandler` 写在 `main.c` 里完全合法，函数名是启动文件定死的，链接器在全工程里找。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。