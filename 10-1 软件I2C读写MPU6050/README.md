# 10-1 软件 I2C 读写 MPU6050

> **章节** 10-1 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

用两个 GPIO 模拟 I2C 时序（起始、停止、发送字节、接收字节、应答），读写六轴传感器 MPU6050。
不依赖硬件 I2C 外设，引脚可以随便挑。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| SCL | PB10 | 开漏输出（Out_OD），依赖模块板载上拉 |
| SDA | PB11 | 开漏输出，读时切输入 |
| MPU6050 VCC/GND | 3V3 / GND | 模块板载 LDO 和上拉 |

## 现象

OLED 显示加速度 X/Y/Z、角速度 X/Y/Z 和温度；晃动模块数值实时变化。

## 关键代码

```c
MyI2C_Start();
MyI2C_SendByte(MPU6050_ADDRESS);	// 0x68 << 1，写
MyI2C_ReceiveAck();
MyI2C_SendByte(RegAddress);
MyI2C_Start();				// 重复起始
MyI2C_SendByte(MPU6050_ADDRESS | 0x01);	// 读
MyI2C_ReceiveAck();
Data = MyI2C_ReceiveByte();
MyI2C_SendAck(1);			// 非应答，告诉从机别再发了
MyI2C_Stop();
```

## 备注

**开漏必须配上拉电阻**：I2C 靠"拉低"通信，高电平是上拉电阻拉出来的。模块板载一般有 4.7k，裸芯片就得自己加。

**读最后一个字节前要先给非应答**（`SendAck(1)`），否则从机会一直占着 SDA。

**软件 I2C 的好处**：时序完全可控，出问题能用逻辑分析仪一眼看出错在第几个时钟；缺点是占 CPU、速率上不去（一般 100 kHz 左右）。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。