# 11-2 硬件 SPI 读写 W25Q64

> **章节** 11-2 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

改用 SPI1 外设（PA5/PA6/PA7 复用），片选仍用软件控制 PA4。
功能和 11-1 一样，速率高得多。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| SS (CS) | PA4 | 软件控制的普通 GPIO |
| SCK | PA5 | SPI1_SCK，复用推挽 |
| MISO | PA6 | SPI1_MISO，上拉输入 |
| MOSI | PA7 | SPI1_MOSI，复用推挽 |

## 现象

现象同 11-1：读到 `EF 4017`，写入的数据能读回来。

## 关键代码

```c
SPI_I2S_SendData(SPI1, ByteSend);
while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
return SPI_I2S_ReceiveData(SPI1);
```

## 备注

**SPI 是全双工**：发一个字节的同时也在收一个字节，所以"读"也要先发一个 dummy（`0xFF`）把时钟打出来。

**片选为什么还用软件**：SPI1 的 NSS 硬件引脚（PA4）功能比较别扭，一个主机还好，多从机就容易乱，工程上几乎都用普通 GPIO 手动拉。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。