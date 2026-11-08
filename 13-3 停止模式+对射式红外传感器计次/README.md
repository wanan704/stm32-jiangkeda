# 13-3 停止模式 + 对射式红外传感器计次

> **章节** 13-3 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

主循环计次后进入 STOP 模式（1.8V 域断电、时钟全停），靠 PB14 的 EXTI 中断唤醒。
唤醒后必须重新 `SystemInit()` 恢复 72 MHz。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 对射传感器 DO | PB14 | 上拉输入，EXTI14 下降沿唤醒 |
| OLED | PB8 / PB9 | 显示计数 |

## 现象

平时闪 `Running` 并显示 Count；进 STOP 后屏幕内容冻结（不再刷新）；挡一下光路 → 唤醒 → 计数 +1，继续。

## 关键代码

```c
PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
SystemInit();		// 唤醒后时钟回到 HSI 8MHz，必须重新配时钟
```

## 备注

**最容易忘的就是 `SystemInit()`**。STOP 唤醒后系统时钟自动切回内部 HSI 8 MHz，不重新初始化的话：延时变长 9 倍、串口波特率全错、定时器频率不对。

`PWR_Regulator_ON` 是保持稳压器供电（唤醒快、电流略大）；换成 `PWR_Regulator_LowPower` 更省电但唤醒慢。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。