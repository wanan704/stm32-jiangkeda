# 6-2 定时器外部时钟

> **章节** 6-2 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

TIM2 的时钟源从内部 72 MHz 换成**外部脉冲**（ETR，固定引脚 PA0），每来一个脉冲 CNT 加 1。
用来数"外部事件发生了多少次"，CPU 不参与计数。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 外部脉冲输入 | PA0 | TIM2_ETR，硬件固定，不能改到别的脚 |

## 现象

每来一个脉冲 CNT +1；CNT 数到 ARR 溢出时进中断，NUM +1。

## 关键代码

```c
TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF,
                        TIM_ExtTRGPolarity_NonInverted, 0x0F);

TIM_TimeBaseInitStruct.TIM_Prescaler = 1 - 1;	// 官方值：不分频，一个脉冲 +1
TIM_TimeBaseInitStruct.TIM_Period    = 10 - 1;	// 官方值：10 个脉冲溢出一次
```

## 备注

**这份代码目前还跑不出效果，有三处要修：**

1. 第 7 行 `TIM_ETRClockMode2Config(...)` **末尾缺分号**，编译直接报错；
2. `PSC=7200-1`、`ARR=10000-1` 是从 6-1 抄过来的 —— 外部脉冲得攒够 7200×10000 = **7200 万个**才溢出一次，手戳挡光片根本看不到 NUM 变。应改成 `1-1` 和 `10-1`；
3. 少了对 PA0 的 GPIO 初始化（官方是上拉输入），悬空脚容易捡噪声。

**优点**：硬件计数，MHz 级也不丢数、零 CPU 开销。**代价**：引脚焊死在 PA0，而且只知道总数，感知不到"哪一下来了"。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。