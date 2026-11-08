# 6-8 编码器接口测速

> **章节** 6-8 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

TIM3 工作在**编码器接口模式**，A/B 两相直接驱动 CNT（TI12：两相上下沿都计，四倍频）。
TIM2 做 1 Hz 闸门，每秒把 CNT 读走并清零，读到的数就是"每秒多少个边沿"，正比于转速。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 编码器 A 相 | PA6 | TIM3_CH1，上拉输入 |
| 编码器 B 相 | PA7 | TIM3_CH2，上拉输入 |
| 编码器 VCC/GND | 3V3 / GND | 模块型必须供电并共地 |

## 现象

电机转起来后，OLED 每秒刷新一次速度值；正转正数、反转负数。手拧只会闪一下就归零（闸门机制）。

## 关键代码

```c
TIM_TimeBaseInitStruct.TIM_Period    = 65536 - 1;
TIM_TimeBaseInitStruct.TIM_Prescaler = 1 - 1;		// 编码器模式必须不分频！

TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,
                           TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
TIM_Cmd(TIM3, ENABLE);
```

## 备注

**踩过的坑：`PSC` 写成 `720-1`，手拧编码器屏幕一动不动。**
编码器模式下 PSC **仍然生效** —— 编码器边沿作为 CK_PSC 进预分频器，要攒够 720 个边沿 CNT 才 +1。手拧一格才 4 个边沿，得拧 180 格才动一下，看起来就是"完全没反应"。官方例程是 `1-1`。

**另一个坑**：预分频器不区分方向，用了 PSC 之后正反转来回拧会出现怪值，所以编码器模式一律 `PSC=0`，要缩放就在软件里除。

**手拧只闪一秒**不是故障：TIM2 每秒读一次并清零，本来就是给连续转的电机设计的。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。