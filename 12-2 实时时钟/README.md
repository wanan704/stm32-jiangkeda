# 12-2 实时时钟（RTC）

> **章节** 12-2 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

RTC 用 LSE 32.768 kHz 晶振走时，OLED 显示年月日时分秒，同时显示 32 位秒计数器 CNT 和余数寄存器 DIV。
掉电后靠 VBAT 继续走。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| LSE 晶振 | PC14 / PC15 | 32.768 kHz，板载 |
| VBAT | 3V3 / 纽扣电池 | 掉电走时靠它 |
| OLED | PB8 / PB9 | 软件 I2C 显示 |

## 现象

OLED 四行：`Date:2026-xx-xx`、`Time:xx:xx:xx`、`CNT:`、`DIV:`，秒位每秒跳一次。

## 关键代码

```c
RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
PWR_BackupAccessCmd(ENABLE);

RCC_LSEConfig(RCC_LSE_ON);
while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
RCC_RTCCLKCmd(ENABLE);
RTC_WaitForSynchro();

RTC_SetPrescaler(32768 - 1);		// 32.768kHz / 32768 = 1Hz
RTC_SetCounter(0);
```

## 备注

**初始化只做一次**：RTC 配置完要在 BKP 里写个标志（比如 `BKP_DR1 = 0xA5A5`），下次上电先查标志，已配置过就不要再 `RTC_SetCounter`，否则每次复位时间都被重置。

**LSE 起振慢**（尤其劣质晶振），`while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)` 可能等几秒，别以为死机了。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。