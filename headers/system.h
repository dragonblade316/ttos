#include <stdint.h>

typedef struct {
    unsigned int EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI;
} cpu_ctx;

typedef void (*irq_handler_t) (cpu_ctx);


void idt_init(void);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

__attribute__((noreturn))
void exception_handler(unsigned int interupt_number, cpu_ctx ctx);

void gdt_init(void);
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

void install_isr_handler(unsigned int isr_num, void (*handler)(cpu_ctx));
void uninstall_isr_handler(unsigned int isr_num);

void install_irq_handler(unsigned int irq_num, void (*handler)(cpu_ctx));
void uninstall_irq_handler(unsigned int irq_num);


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