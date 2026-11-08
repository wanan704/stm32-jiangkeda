# 13-4 待机模式 + 实时时钟

> **章节** 13-4 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

进入 STANDBY 模式（最省电，SRAM 和寄存器全丢），靠 RTC 闹钟或 WKUP（PA0）上升沿唤醒。
唤醒等同于一次复位，程序从头开始跑。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| WKUP | PA0 | 上升沿可唤醒待机 |
| RTC 闹钟 | — | 本工程设为当前时间 +10 s |
| OLED | PB8 / PB9 | 显示 CNT / ALR / ALRF |

## 现象

显示秒计数器和闹钟值，约 1 秒后进待机（屏幕清空）；10 秒后闹钟到点，整机复位重启，CNT 从 RTC 继续走。

## 关键代码

```c
uint32_t Alarm = RTC_GetCounter() + 10;
RTC_SetAlarm(Alarm);

PWR_WakeUpPinCmd(ENABLE);		// 使能 PA0 的 WKUP 功能
PWR_EnterSTANDBYMode();			// 进去就等复位
```

## 备注

**待机 ≠ 停止**：待机唤醒是一条复位向量重新开始，所有变量回到初始值，SRAM 内容丢失；只有备份域（RTC、BKP）还在。

所以"待机 + RTC"的典型用法是：醒来读一下 RTC 时间，做完事再睡，靠 RTC 维持长时间计时。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。