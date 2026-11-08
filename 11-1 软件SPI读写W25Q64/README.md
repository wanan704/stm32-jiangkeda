# 11-1 软件 SPI 读写 W25Q64

> **章节** 11-1 ｜ **芯片** STM32F103C8T6（72 MHz）｜ **库** STM32 标准外设库 ｜ **IDE** Keil MDK 5
> [← 返回总目录](../README.md)

## 这个工程做什么

用 GPIO 模拟 SPI 模式 0（空闲低、上升沿采样），读写 SPI Flash W25Q64（8 MB）。
演示读 JEDEC ID、写使能、页编程、扇区擦除、读数据。

## 硬件连接

| 外设 | 引脚 | 说明 |
| --- | --- | --- |
| SS (CS) | PA4 | 推挽输出，低电平选中 |
| SCK | PA5 | 推挽输出 |
| MISO | PA6 | 上拉输入 |
| MOSI | PA7 | 推挽输出 |
| W25Q64 VCC/GND | 3V3 / GND | 3.3V 供电 |

## 现象

OLED 显示厂商 ID `EF`、设备 ID `4017`；按键触发写入/读取，数据能对得上。

## 关键代码

```c
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t ByteReceive = 0x00;
	for (i = 0; i < 8; i++)
	{
		MySPI_W_MOSI(!!(ByteSend & (0x80 >> i)));	// 高位先出
		MySPI_W_SCK(1);					// 上升沿，从机采样
		if (MySPI_R_MISO()) ByteReceive |= (0x80 >> i);
		MySPI_W_SCK(0);
	}
	return ByteReceive;
}
```

## 备注

**写 Flash 的三步缺一不可**：写使能（`0x06`）→ 页编程（`0x02`）→ 轮询状态寄存器等忙位清零。少一步数据写不进去。

**擦除的最小单位是扇区（4 KB）**，写之前必须先擦；擦完整片变 `0xFF`。

SPI 有 4 种模式，W25Q64 支持模式 0 和 3，这里用模式 0（`SCK` 空闲低、上升沿采样）。

---

用 Keil 打开本目录下的 `Project.uvprojx`，Build 后下载即可。