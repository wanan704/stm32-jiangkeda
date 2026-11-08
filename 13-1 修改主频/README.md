# 13-1 修改主频

> **章节** 13-1 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

改 `system_stm32f10x.c` 里的时钟树（HSE、PLL 倍频、AHB/APB 分频），让系统跑在非 72 MHz 的频率上。
`main` 里只负责把 `SystemCoreClock` 显示出来。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| OLED | PB8 / PB9 | 显示当前主频 |

## 现象

第一行显示 `SYSCLK:` 和当前频率；第二行 `Running` 闪烁，主频越低闪得越慢。

## 关键代码

```c
OLED_ShowString(1, 1, "SYSCLK:");
OLED_ShowNum(1, 8, SystemCoreClock, 8);		// 当前系统时钟，单位 Hz
```

## 备注

**改主频是牵一发动全身**：`Delay_ms` 靠 SysTick、串口波特率靠 PCLK2、定时器分频靠 PCLK1，全都得跟着重算。只改时钟树不改这些，现象就是"延时变短、串口乱码、PWM 频率不对"。

`SystemCoreClock` 这个变量由 `SystemInit()` 更新，直接显示它比自己算靠谱。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。