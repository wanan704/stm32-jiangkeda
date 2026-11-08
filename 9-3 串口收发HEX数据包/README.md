# 9-3 串口收发 HEX 数据包

> **章节** 9-3 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

用状态机收"固定包头 + 数据 + 固定包尾"的十六进制包：`0xFF` 开头、`0xFE` 结尾，中间是数据。
收到完整一包才置标志，主循环统一处理。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| PA9 / PA10 | TX / RX | 9600-8-N-1，交叉接 USB 转串口模块 |

## 现象

串口助手发 `FF 01 02 FE`，单片机回传同样的包，OLED 显示 `01 02`。

## 关键代码

```c
switch (RxState)
{
case 0: if (RxData == 0xFF) RxState = 1; break;			// 等包头
case 1: Serial_RxPacket[Serial_RxPacketLen++] = RxData;
        RxState = 2; break;					// 收数据
case 2: if (RxData == 0xFE) { Serial_RxFlag = 1; RxState = 0; }	// 等包尾
        break;
}
```

## 备注

**HEX 包的代价**：数据本身不能出现 `0xFF` / `0xFE`，否则会被误认为包头包尾。要传任意二进制，得加长度字段或转义。

**好处**：定长、解析快，适合单片机和上位机之间传传感器数据、控制指令。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。