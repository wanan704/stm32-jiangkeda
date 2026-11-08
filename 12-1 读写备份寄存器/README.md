# 12-1 读写备份寄存器

> **章节** 12-1 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

操作 BKP 备份寄存器（DR1/DR2）：主电源掉电后，只要 VBAT 还在，数据就不丢。
用来做"掉电保存少量参数"。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 按键 K1 | PB1 | 上拉输入，按一下写入并自增 |
| 按键 K2 | PB11 | 上拉输入 |
| VBAT | 3V3 / 纽扣电池 | 备份域供电，没电池则主电断就丢 |

## 现象

按 K1 后 W 行数值 +1；复位后 R 行读到的还是刚才的值（前提是 VBAT 有电）。

## 关键代码

```c
RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
PWR_BackupAccessCmd(ENABLE);			// 解锁备份域，不解锁写不进去

BKP_WriteBackupRegister(BKP_DR1, ArrayWrite[0]);
ArrayRead[0] = BKP_ReadBackupRegister(BKP_DR1);
```

## 备注

**必须调 `PWR_BackupAccessCmd(ENABLE)`**，否则对 BKP 的写操作全部无效，读回来永远是 0。

BKP 只有 16 位 × 若干寄存器，适合存校准值、设备号这类小数据；大数据用内部 Flash（15-1）或外部 Flash（11-x）。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。