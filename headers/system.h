#include <stdint.h>


void idt_init(void);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

__attribute__((noreturn))
void exception_handler(void);

void gdt_init(void);
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

