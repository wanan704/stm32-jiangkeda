# 9-4 串口收发文本数据包

> **章节** 9-4 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

用状态机收"`@` 开头、`\r\n` 结尾"的文本包，内容按 ASCII 存，方便人在串口助手里直接敲。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| PA9 / PA10 | TX / RX | 9600-8-N-1，交叉接 USB 转串口模块 |

## 现象

串口助手发 `@LED_ON` 再回车，单片机识别整包并回传，OLED 显示包内容。

## 关键代码

```c
case 0: if (RxData == '@') RxState = 1; break;			// 等 '@'
case 1: if (RxData == '\r') RxState = 2;			// 等回车
        else Serial_RxPacket[Len++] = RxData;
        break;
case 2: if (RxData == '\n') { Serial_RxFlag = 1; RxState = 0; }	// 等换行
        break;
```

## 备注

文本包适合**人手动输入**调试（比如发 `@LED_ON`），HEX 包适合机器之间传二进制。
注意 `\r\n` 的顺序：串口助手勾选"发送新行"时自动加，手敲的话别忘了回车。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。