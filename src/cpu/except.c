#include "system.h"
#include "print.h"

char *exception_messages[] = {
	"Division by zero",				/* 0 */
	"Debug",
	"Non-maskable interrupt",
	"Breakpoint",
	"Detected overflow",
	"Out-of-bounds",				/* 5 */
	"Invalid opcode",
	"Device not avalible",
	"Double fault",
	"Coprocessor segment overrun",
	"Bad TSS",						/* 10 */
	"Segment not present",
	"Stack fault",
	"General protection fault",
	"Page fault",
	"Unknown interrupt",			/* 15 */
	"x87 Floating-Point Exception",
	"Alignment check",
	"Machine check",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved"
};

static irq_handler_t isr_handlers[32];
static irq_handler_t irq_handlers[16];

//the handler is a function pointer 
void install_isr_handler(unsigned int isr_num, void (*handler)(cpu_ctx)) {
    isr_handlers[isr_num] = handler;
}

void uninstall_isr_handler(unsigned int isr_num) {
    isr_handlers[isr_num] = 0;
}

void exception_handler(unsigned int interupt_number, cpu_ctx ctx) {

    irq_handler_t handler = isr_handlers[interupt_number];
    if(handler != 0) {
    	handler(ctx);
		return;
    }

    print_newline();
    print_set_color(PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
    print_str(exception_messages[interupt_number]);


    //asm volatile ("cli"); // Completely hangs the computer
    //asm volatile ("hlt");
}

//the handler is a function pointer 
void install_irq_handler(unsigned int irq_num, void (*handler)(cpu_ctx)) {
    irq_handlers[irq_num] = handler;    
}

void uninstall_irq_handler(unsigned int irq_num) {
    irq_handlers[irq_num];
}

void irq_handler(unsigned int interupt_number, cpu_ctx ctx) {
    irq_handler_t handler = isr_handlers[interupt_number];
    if(handler != 0) {
    	handler(ctx);
		return;
    }

    print_newline();
    print_set_color(PRINT_COLOR_LIGHT_RED, PRINT_COLOR_BLACK);
    print_str("no handler for irq ");
}
