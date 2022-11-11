#include "system.h"
#include "print.h"

void testing() {
    return;
}

int kernel_main() {
    //print_clear();
    //print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
    //print_str("hello world");
    
    gdt_init();
    //idt_init();




    return 0;
}