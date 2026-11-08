# 15-2 读取芯片 ID

> **章节** 15-2 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

直接按地址读系统存储区的只读寄存器：`0x1FFFF7E0` 是 Flash 容量，`0x1FFFF7E8` 开始是 96 位唯一 ID。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| OLED | PB8 / PB9 | 显示容量和 UID |

## 现象

第一行 `F_SIZE:0080`，下面显示 96 位 UID（三行十六进制）。

## 关键代码

```c
OLED_ShowHexNum(1, 8, *(__IO uint16_t *)(0x1FFFF7E0), 4);	// Flash 容量
OLED_ShowHexNum(2, 6, *(__IO uint16_t *)(0x1FFFF7E8), 4);	// UID 低 16 位
OLED_ShowHexNum(2, 11, *(__IO uint16_t *)(0x1FFFF7E8 + 0x02), 4);
OLED_ShowHexNum(3, 1, *(__IO uint32_t *)(0x1FFFF7E8 + 0x04), 8);
```

## 备注

**C8T6 的容量寄存器常读到 `0x0080`（128 KB）**，但芯片标称 64 KB —— 这是 ST 当年的"隐藏容量"老梗，实际能用多少以官方数据手册为准。

**96 位 UID 每片唯一**，很适合做设备序列号、加密绑定的种子；但它不是密钥，别直接拿来当密码用。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。