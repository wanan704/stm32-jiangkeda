# 6-4 PWM 驱动舵机（实际是舵机）

> **章节** 6-4 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

TIM2_CH2 输出 50 Hz PWM，用 0.5~2.5 ms 的高电平宽度控制舵机角度。
按 K1 让角度在 0°/30°/…/180° 之间循环。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 舵机信号线 | PA1 | TIM2_CH2，50 Hz，0.5–2.5 ms 对应 0–180° |
| 舵机电源 | 5V / GND | **独立 5V 供电**，与单片机共地，别从 3.3V 取电 |
| 按键 K1 | PA6 | 上拉输入 |

## 现象

OLED 显示当前角度；每按一次 K1，舵机转到下一个 30° 位置。

## 关键代码

```c
TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1;		// 72MHz/72 = 1MHz → 1us 一个数
TIM_TimeBaseInitStruct.TIM_Period    = 20000 - 1;	// 20ms 周期 = 50Hz
TIM_OCInitStructure.TIM_Pulse = Angle / 180.0 * 2000 + 500;	// 0.5ms ~ 2.5ms
```

## 备注

**目录名和内容对不上**：这里才是舵机，6-3 才是呼吸灯，两个目录名互换了。

`PSC=71` 让计数周期正好 1 μs，于是 CCR 直接就是微秒数，算角度非常直观：0° → 500，180° → 2500。

舵机堵转电流能到几百 mA，从 ST-Link 的 3.3V 取电必掉压复位，一定要单独 5V 供电并共地。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。