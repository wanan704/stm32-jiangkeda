# 6-5 PWM 驱动直流电机

> **章节** 6-5 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

TIM2_CH3 输出 PWM 调速，PA4/PA5 两个 GPIO 控制方向（类似 TB6612 的 AIN1/AIN2）。
按键切换速度档位，正负号代表方向。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 电机 PWM | PA2 | TIM2_CH3，1 kHz |
| 方向 IN1 | PA4 | 高/低组合决定正反转 |
| 方向 IN2 | PA5 | 与 IN1 相反 |
| 电机电源 | 5V / GND | 独立供电，共地 |

## 现象

每按一次 K1，速度 +20；超过 100 后跳到 -100 反转，再逐步回到 0 再变正。

## 关键代码

```c
void Motor_SetSpeed(int16_t Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		Speed = -Speed;
	}
	PWM_SetCompare3(Speed);
}
```

## 备注

**这份 `main.c` 现在编译不过**：第 6 行 `uint8_t KeyNum`、第 7 行 `int16_t speed` 末尾都少了分号，Keil 报 2 个 error、不生成 axf。补上 `;` 就好。

调速时 PWM 频率别太低（<1 kHz 电机会啸叫、抖动），也别太高（开关损耗大），1~10 kHz 比较合适。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。