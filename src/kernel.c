#include "system.h"
#include "print.h"


int main() {
    print_clear();
    print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
    print_str("hello world");
}

int kernel_main() {

    gdt_init();
    idt_init();

    PIC_remap(PIC1, PIC2);


    print_clear();
    print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
    print_str("hello world");
    
    while(1) {
    print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
    print_str("hello world");
    }
    for(;;) asm("hlt");
}