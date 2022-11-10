#include "print.h"
#include "PIC.h"
#include "IDT.h"

int kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("Welcome to our 64-bit kernel!");

    PIC_remap(PIC1, PIC2); //A common choice is to move them to the beginning of the available range (IRQs 0..0xF -> INT 0x20..0x2F). For that, we need to set the master PIC's offset to 0x20 and the slave's to 0x28
    PIC_init();

    IDT_init();

    return 0;
}