#ifndef KERNELMQ_INCLUDED_TSS
#define KERNELMQ_INCLUDED_TSS 1

#include "info.h"

void tss_write_to_gdt(const struct KernelMQ_Info *kinfo, void *gdt_entry);

void tss_flush();

#endif
