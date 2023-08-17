/*
 * main.h
 *
 *  Created on: 2023Äê5ÔÂ12ÈÕ
 *      Author: LMTX
 */

#ifndef USER_MAIN_H_
#define USER_MAIN_H_

#include "inc/hw_memmap.h"

#include "eusci_b_i2c.h"
#include "ctsd16.h"
#include "battbak.h"
#include "timer_b.h"
#include "timer_d.h"
#include "eusci_a_spi.h"
#include "eusci_a_uart.h"
#include "comp_b.h"
#include "tlv.h"
#include "dac12_a.h"
#include "timer_a.h"
#include "usci_a_uart.h"
#include "pmm.h"
#include "sysctl.h"
#include "adc10_a.h"
#include "sfr.h"
#include "mpy32.h"
#include "wdt_a.h"
#include "ucs.h"
#include "pmap.h"
#include "rtc_a.h"
#include "usci_b_i2c.h"
#include "usci_b_spi.h"
#include "ldopwr.h"
#include "lcd_c.h"
#include "tec.h"
#include "rtc_c.h"
#include "gpio.h"
#include "adc12_a.h"
#include "aes.h"
#include "oa.h"
#include "rtc_b.h"
#include "sd24_b.h"
#include "ram.h"
#include "dma.h"
#include "ref.h"
#include "eusci_b_spi.h"
#include "usci_a_spi.h"
#include "lcd_b.h"
#include "flashctl.h"
#include "crc.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define CPU_F ((double)40000000)
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))


/*!< Signed integer types  */
#define  s8  signed char
#define  s16 signed short
#define  s32 signed long

/*!< Unsigned integer types  */
#define  u8  unsigned char
#define  u16 unsigned short
#define  u32 unsigned long

#define  uchar  unsigned char
#define  uint unsigned short
#define  ulong unsigned long


#endif /* USER_MAIN_H_ */
