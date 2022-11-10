#pragma once
#include "IO.h"

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

void PIC_sendEOI(unsigned char irq);

void PIC_remap(int offset1, int offset2);

void IRQ_set_mask(unsigned char IRQline);

void IRQ_clear_mask(unsigned char IRQline);