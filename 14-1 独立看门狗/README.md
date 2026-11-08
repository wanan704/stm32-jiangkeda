# 14-1 独立看门狗（IWDG）

> **章节** 14-1 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

IWDG 用内部 40 kHz LSI 独立计时，超时（本工程 1 s）没喂狗就复位。
`Key_GetNum()` 是阻塞式读键，按住不放就能模拟"主循环卡死"。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 按键 K1 | PB1 | 按住 >1s 模拟程序卡死 |
| 按键 K2 | PB11 | 上拉输入 |

## 现象

正常时 `FEED` 闪烁；按住 K1 超过 1 秒 → 复位，OLED 闪 `IWDGRST`，之后恢复正常。

## 关键代码

```c
IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
IWDG_SetPrescaler(IWDG_Prescaler_16);	// 40kHz / 16 = 2.5kHz
IWDG_SetReload(2499);			// 2500 / 2.5kHz = 1s
IWDG_ReloadCounter();			// 喂狗
IWDG_Enable();
```

## 备注

**IWDG 一旦开启就关不掉**，只能复位。调试时在 `IWDG_Enable()` 前打个断点，否则程序停住 1 秒板子就重启。

超时时间按 LSI 40 kHz 估算，实际 LSI 在 30~60 kHz 之间漂，所以 1 s 的看门狗可能 0.9 s 就咬 —— 喂狗周期要留足余量（这里 800 ms 喂一次）。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。