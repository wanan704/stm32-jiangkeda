# 7-1 AD 单通道

> **章节** 7-1 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

ADC1 的通道 0（PA0）做单次转换，读电位器的分压值。
包含完整的"复位校准 → 开启校准 → 软件触发 → 等 EOC → 读 DR"流程。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| 电位器 | PA0 | ADC1_IN0，模拟输入（GPIO_Mode_AIN） |
| 电位器两端 | 3V3 / GND | 中间抽头接 PA0 |

## 现象

OLED 显示 0~4095 的原始值，拧电位器数值跟着变。

## 关键代码

```c
ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
ADC_SoftwareStartConvCmd(ADC1, ENABLE);
while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
return ADC_GetConversionValue(ADC1);	// 读 DR 会自动清 EOC
```

## 备注

**校准两句话别写错**：

```c
ADC_ResetCalibration(ADC1);
while (ADC_GetResetCalibrationStatus(ADC1) == SET);	// 等复位校准完成
ADC_StartCalibration(ADC1);
while (ADC_GetCalibrationStatus(ADC1) == SET);		// 等校准完成
```

第一句等的是 `GetResetCalibrationStatus`，不是 `GetCalibrationStatus` —— 写错了通常不卡死（复位阶段 CAL 本来就是 0），但语义是错的。

ADC 时钟不能超过 14 MHz，`RCC_ADCCLKConfig(RCC_PCLK2_Div6)` 把 72 MHz 六分频成 12 MHz 正好。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。