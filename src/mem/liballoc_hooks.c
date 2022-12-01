#include "liballoc.h"

extern int liballoc_lock() {
    asm volatile ("cli");
}
extern int liballoc_unlock() {
    asm volatile ("sti");
}
extern void* liballoc_alloc(int);
extern int liballoc_free(void*,int);