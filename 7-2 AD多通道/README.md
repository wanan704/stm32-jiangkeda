# 7-2 AD 多通道

> **章节** 7-2 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

同一路 ADC 轮流采 4 个通道（PA0~PA3），每次转换前用 `ADC_RegularChannelConfig()` 换通道。
非扫描、单次转换，四路依次读。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| AD0 | PA0 | ADC1_IN0 |
| AD1 | PA1 | ADC1_IN1 |
| AD2 | PA2 | ADC1_IN2 |
| AD3 | PA3 | ADC1_IN3 |

## 现象

OLED 四行分别显示 AD0~AD3 的数值，拧哪个电位器哪一行变。

## 关键代码

```c
uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}
```

## 备注

**踩过的坑：`AD.h` 第 4 行声明末尾少分号，报错却指向 `OLED.h(4): expected a "{"`。**
`#include` 是纯文本展开，缺分号后编译器继续往下读，把账算到了下一个头文件头上。**看到"某个 .h 报错但那个 .h 没问题"，就去查它前一个被 include 的头文件末尾。**

另外 `while(ADC_GetCalibrationStatus(ADC1) == SET)` 等复位校准也是错的，应为 `ADC_GetResetCalibrationStatus`。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。