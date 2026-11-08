# 3-1 LED 闪烁

> **章节** 3-1 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

GPIO 输出第一个实验：把 PA0 配成推挽输出，让 LED 以 500 ms 的节奏亮灭。
文件里同时保留了 `GPIO_WriteBit`、`GPIO_SetBits/ResetBits` 三种写法，取消注释可以对比。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| LED | PA0 | 阳极接 3V3，阴极串限流电阻到 PA0 —— **低电平点亮**（灌电流） |

## 现象

LED 亮 500 ms、灭 500 ms，一直循环。

## 关键代码

```c
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA, &GPIO_InitStructure);

while (1)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);	// 低电平 → 亮
	Delay_ms(500);
	GPIO_SetBits(GPIOA, GPIO_Pin_0);	// 高电平 → 灭
	Delay_ms(500);
}
```

## 备注

为什么低电平点亮：LED 阳极固定接 3V3，引脚输出低时才有电流从 3V3 经 LED 灌进引脚（sink），所以 `ResetBits` 是亮。
如果哪天把 LED 反过来接（阴极接地、阳极接引脚），逻辑就要整个反一遍 —— 3-2 的 PA8/PA9 就是栽在这个反差上。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。