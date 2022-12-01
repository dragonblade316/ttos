#include "system.h"
#include "print.h"

#define IDT_MAX_DESCRIPTORS 256


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


__attribute__((aligned(0x10)))
static idt_entry_t idt[IDT_MAX_DESCRIPTORS];


void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->offset_1       = (uint64_t)isr & 0xFFFF;
    descriptor->selector       = 0x08;
    descriptor->ist            = 0;
    descriptor->type_attributes     = flags;
    descriptor->offset_2       = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->offset_3       = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->zero           = 0;
}

static idt_entry_t idt[256];
idtr_t idtr;


extern void* isr_stub_table[];
extern void* irq_entry_table[];
extern void idt_load();

void idt_init() {

    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    //ISR init
    for (uint8_t vector = 0; vector <= 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    }
    //IRQ init
    for (uint8_t vector = 33; vector < 47; vector++) {
        idt_set_descriptor(vector, irq_entry_table[vector-32], 0x8E);
    }


    idt_load();
    //__asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    asm volatile ("sti"); // set the interrupt flag
}

