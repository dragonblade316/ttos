#pragma once
#include <stdint.h>
extern void* isr_stub_table[];

#define IDT_MAX_DESCRIPTORS 256
#define GDT_OFFSET_KERNEL_CODE 0x08


typedef struct {
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
   uint32_t offset_3;        // offset bits 32..63
   uint32_t zero;            // reserved
} idt_entry_t;



typedef struct {
	uint16_t	limit;
	uint64_t	base;
} __attribute__((packed)) idtr_t;

void IDT_init(void);

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);