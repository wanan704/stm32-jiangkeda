# 3-4 按键控制 LED

> **章节** 3-4 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

第一个输入实验：读两个按键，按一下翻转对应的 LED。
`Key.c` 负责读键（带松手等待，属于阻塞式），`LED.c` 负责亮灭和翻转，`main.c` 只做分发。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 按键 K1 | PA6 | 上拉输入（IPU），按下为低 |
| 按键 K2 | PA7 | 上拉输入（IPU），按下为低 |
| LED1 | PA1 | 低电平点亮 |
| LED2 | PA2 | 低电平点亮 |

## 现象

按一下 K1，LED1 亮；再按一下，LED1 灭。K2 控制 LED2，互不影响。

## 关键代码

```c
// Key.c：读键，返回 1 / 2 / 0
if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)
{
	while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0);	// 等松手
	return 1;
}

// main.c：分发
KeyNum = Key_GetNum();
if (KeyNum == 1) LED1_Turn();
if (KeyNum == 2) LED2_Turn();
```

## 备注

**踩过的坑**：`LED1_Turn()` / `LED2_Turn()` 一度被写在 `Key.c` 里，而且翻转的是 **PA6/PA7（按键自己的引脚）**。
PA6/PA7 是上拉输入，输入模式下写 ODR 根本不影响引脚电平，真正的 LED 引脚 PA1/PA2 从头到尾没人动 → 按了没反应。
现在这两个函数已经移回 `LED.c`，操作 PA1/PA2。

**硬件提醒**：PA6/PA7 如果还挂着 3-2 流水灯的 LED，按键松开时会被 LED 并联拉低，读数可能不稳，建议把这两个灯拆掉。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。