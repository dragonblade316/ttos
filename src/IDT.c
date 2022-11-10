#include "IDT.h"

__attribute__((aligned(0x10)))
static idt_entry_t idt[IDT_MAX_DESCRIPTORS];


void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->offset_1       = (uint64_t)isr & 0xFFFF;
    descriptor->selector       = GDT_OFFSET_KERNEL_CODE;
    descriptor->ist            = 0;
    descriptor->type_attributes     = flags;
    descriptor->offset_2       = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->offset_3       = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->zero           = 0;
}

void IDT_init() {
    idtr_t idtr;

    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    
    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        //vectors[vector] = true; Im not sure why this is here
    }


    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}