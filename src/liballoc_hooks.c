#include "liballoc.h"

extern int liballoc_lock();
extern int liballoc_unlock();
extern void* liballoc_alloc(int);
extern int liballoc_free(void*,int);