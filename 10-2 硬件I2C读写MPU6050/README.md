# 10-2 硬件 I2C 读写 MPU6050

> **章节** 10-2 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

改用 STM32 内置的 I2C2 外设读写 MPU6050，代码靠 `I2C_CheckEvent()` 等事件位推进时序。
和 10-1 功能完全一样，用来对比软硬两种实现。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| SCL | PB10 | I2C2_SCL，复用开漏 |
| SDA | PB11 | I2C2_SDA，复用开漏 |
| MPU6050 VCC/GND | 3V3 / GND | 模块板载上拉 |

## 现象

现象同 10-1：OLED 显示六轴数据和温度。

## 关键代码

```c
I2C_GenerateSTART(I2C2, ENABLE);
MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);		// EV5
I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	// EV6
I2C_SendData(I2C2, RegAddress);
MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);	// EV8_2
I2C_GenerateSTOP(I2C2, ENABLE);
```

## 备注

**硬件 I2C 的坑**：STM32F1 的 I2C 外设有已知 errata，总线被干扰时可能卡在 `WaitEvent` 的死循环里（所以官方例程都加了超时）。

**接收最后一个字节的顺序很讲究**：先 `I2C_AcknowledgeConfig(DISABLE)` 再 `I2C_GenerateSTOP(ENABLE)`，最后才读 DR —— 顺序错了会多读一个字节或者总线锁死。

实际项目里 F1 系列很多人宁可软件模拟，就是为了绕开这个坑。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。