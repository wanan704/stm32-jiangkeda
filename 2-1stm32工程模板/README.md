# 2-1 工程模板

> **章节** 2-1 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

一个空工程：只有启动文件、标准外设库、延时函数和一个空的 `main()`，没有任何外设代码。
新建工程时以它为底子，把 `Start / Library / System / User` 四个目录拷过来即可。

## 现象

下载后板子上没有任何现象 —— LED 不闪、蜂鸣器不响，这是正常的，`main()` 里只有一个空的 `while(1)`。

## 关键代码

```c
int main(void)
{
	while (1)
	{
	}
}
```

## 备注

**工程结构**

| 目录 | 内容 |
| --- | --- |
| `Start/` | 启动文件 `startup_stm32f10x_md.s`、`stm32f10x.h`、`system_stm32f10x.c` |
| `Library/` | 标准外设库 `stm32f10x_gpio.c` 等 |
| `System/` | `Delay.c`（SysTick 延时） |
| `User/` | `main.c`、`stm32f10x_it.c` |
| `Hardware/` | 自己写的外设驱动（本模板为空） |

**新建工程要配的三处**：宏定义 `STM32F10X_MD, USE_STDPERIPH_DRIVER`；IncludePath 加上 `Start;Library;System;User;Hardware`；勾选 `Create HEX File`。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。