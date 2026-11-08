# 8-2 DMA + AD 多通道

> **章节** 8-2 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

ADC1 扫描 4 个通道 + 连续转换，DMA1_Channel1 循环搬运到 `AD_Value[4]`。
CPU 只管读数组，搬运全自动 —— 这是 ADC 采样的标准做法。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| AD0~AD3 | PA0~PA3 | ADC1_IN0 ~ IN3，模拟输入 |

## 现象

OLED 四行数值同时刷新，CPU 不参与搬运，刷新率比 7-2 高很多。

## 关键代码

```c
ADC_InitStructure.ADC_ScanConvMode       = ENABLE;		// 扫描 4 个通道
ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;		// 连续转换
ADC_InitStructure.ADC_NbrOfChannel       = 4;

DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)AD_Value;
DMA_InitStructure.DMA_BufferSize         = 4;
DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;	// 循环，转完自动重装
DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;	// 由 ADC 硬件触发

ADC_DMACmd(ADC1, ENABLE);
```

## 备注

**三个必须配对的地方**：

1. 数据宽度：ADC 是 12 位，外设和存储器都选 `HalfWord`（16 位）；
2. 外设地址**不自增**（永远是 `ADC1->DR`），存储器地址**自增**（数组依次往后放）；
3. `DMA_Mode_Circular` —— 用 Normal 的话转完 4 个就停了，屏幕数值会冻住。

`DMA1_Channel1` 是 ADC1 的固定映射通道，不能随便换。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。