# 14-2 窗口看门狗（WWDG）

> **章节** 14-2 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

WWDG 由 APB1 时钟驱动，除了"太晚喂"，"太早喂"也会复位 —— 它卡的是程序的执行节奏。
本工程窗口 30 ms、超时 50 ms，正常 40 ms 喂一次。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 按键 K1 | PB1 | 按住模拟卡死 |
| 按键 K2 | PB11 | 上拉输入 |

## 现象

正常时 `FEED` 闪烁；按住 K1（喂晚了）或把延时改短（喂早了）都会复位，OLED 闪 `WWDGRST`。

## 关键代码

```c
RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
WWDG_SetPrescaler(WWDG_Prescaler_8);
WWDG_SetWindowValue(0x40 | 21);		// 窗口值：早于 30ms 喂狗 → 复位
WWDG_Enable(0x40 | 54);			// 初值：超时 50ms
WWDG_SetCounter(0x40 | 54);		// 喂狗
```

## 备注

**窗口看门狗比独立看门狗严格**：它要求你在"窗口打开之后、超时之前"喂。喂早了说明程序跑飞得太快（比如某个循环被跳过），一样判死。

那个 `0x40` 是 WWDG 的固定有效位（T6 必须为 1），计数器实际只有低 6 位可用。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。