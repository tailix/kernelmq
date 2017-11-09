#ifndef KERNELMQ_INCLUDED_PAGEDIR
#define KERNELMQ_INCLUDED_PAGEDIR 1

#include "config.h"

#define PAGE_DIR_ALIGN 4096

struct PageDir_Entry {
    unsigned int present        : 1;
    unsigned int writable       : 1;
    unsigned int user           : 1;
    unsigned int write_through  : 1;
    unsigned int cache_disabled : 1;
    unsigned int accessed       : 1;
    unsigned int always_0       : 1;
    unsigned int page_size      : 1;
    unsigned int ignored        : 1;
    unsigned int unused         : 3;
    unsigned int addr           : 20;
}
__attribute__((packed));

typedef struct PageDir_Entry PageDir[PAGE_DIR_LENGTH] __attribute__((aligned((PAGE_DIR_ALIGN))));

#endif
