# 7-2 DMA+AD 多通道（副本）

> **章节** 7-2（附） ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

**这个目录是 7-2 的副本**：`AD.c` 里没有任何 DMA 代码，`main.c` 的 md5 也和 7-2 完全一样，属于复制目录时多出来的一份。
真正用 DMA 搬运 ADC 数据的是 **8-2**。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| AD0~AD3 | PA0~PA3 | ADC1_IN0 ~ IN3 |

## 现象

现象与 7-2 完全相同：四行 AD0~AD3 数值。

## 关键代码

```c
// 与 7-2 相同，逐个通道软件触发
AD0 = AD_GetValue(ADC_Channel_0);
AD1 = AD_GetValue(ADC_Channel_1);
AD2 = AD_GetValue(ADC_Channel_2);
AD3 = AD_GetValue(ADC_Channel_3);
```

## 备注

留着做对照可以，但别拿它当"DMA 版"参考 —— 名字里的 DMA 是假的。看 8-2 的 `AD.c` 才知道 DMA 怎么配：
`DMA_PeripheralBaseAddr = &ADC1->DR`、`DMA_Mode_Circular`、`ADC_DMACmd(ADC1, ENABLE)`。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。