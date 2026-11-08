# 8-1 DMA 数据转运

> **章节** 8-1 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

存储器到存储器（M2M）的 DMA 搬运：把 `DataA[4]` 搬到 `DataB[4]`，CPU 全程不参与。
重点是 `MyDMA_Init()` 和 `MyDMA_Transfer()` 的分工。

## 现象

上电先显示 DataA 有值、DataB 全 0；延时 1 秒后 DataB 变成和 DataA 一样，OLED 两行一致。

## 关键代码

```c
void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);			// ① 先关通道
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);	// ② 补回传输次数
	DMA_Cmd(DMA1_Channel1, ENABLE);				// ③ 再开通道
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
}
```

## 备注

**为什么 Init 已经有地址和 Size，还要一个 Transfer？**
`CNDTR` 是**倒计时**寄存器，转一次减 1，到 0 通道自动停。想再转，必须"关通道 → 重写 CNDTR → 开通道"。

**为什么地址不用重写？** 通道关闭时 `CPAR/CMAR` 不会被复位，基地址一直保留；地址自增发生在硬件内部的"当前地址寄存器"里，重新使能时会自动从 `CPAR/CMAR` 重新装载。所以全局变量只存了 `Size`，没存地址。

**M2M 不能配循环模式**（RM0008 明说），所以这里必须是 Normal + 手动 Transfer。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。