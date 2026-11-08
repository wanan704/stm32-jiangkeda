# 9-2 串口发送 + 接收

> **章节** 9-2 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

在 9-1 的基础上打开接收：`USART_IT_RXNE` 中断里把数据取走并置标志，主循环负责回传和显示。
这是"查询发送 + 中断接收"的经典组合。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| PA9 (TX) | → 模块 RXD | 复用推挽输出 |
| PA10 (RX) | ← 模块 TXD | 上拉输入 |
| GND | → 模块 GND | 共地 |

## 现象

串口助手发一个字节，单片机原样回传，OLED 上以十六进制显示收到的值。

## 关键代码

```c
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		Serial_RxData = USART_ReceiveData(USART1);	// 只做搬运
		Serial_RxFlag = 1;				// 插个旗子
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
```

## 备注

**为什么接收必须用中断**：9600 波特率下一个字节只有 **1.04 ms**，而 `RDR` 只有一个字节深，新字节来了旧的就被覆盖。主循环里刷一次 OLED（软件 I2C）就可能超过 1 ms，查询法必丢字节。

**中断里只搬数据、置标志**，不刷屏、不回传 —— 重活留给主循环，否则会堵住后面的字节。

**这套写法的天花板**：`Serial_RxData` 是单字节变量，不是队列。主循环处理慢于 1.04 ms/字节，照样丢 —— 这就是 9-3/9-4 要引入数据包的原因。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。