/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __SERIAL_UART8250_H__
#define __SERIAL_UART8250_H__

//#include <sbi/sbi_types.h>
#include <stdint.h>
typedef uint32_t u32;
typedef uint16_t u16;

#define VIRT_UART16550_INTERRUPT	10

#define VIRT_UART16550_ADDR		0x10000000
//#define VIRT_UART16550_ADDR		0x10000000
#define VIRT_UART_BAUDRATE		115200
#define VIRT_UART_SHIFTREG_ADDR		3686400

void uart8250_enable_rx_int();

void uart8250_putc(char ch);

int uart8250_getc(void);

int uart8250_init(unsigned long base, u32 in_freq, u32 baudrate, u32 reg_shift,
		  u32 reg_width);

#endif
