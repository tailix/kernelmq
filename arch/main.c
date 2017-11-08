#include "console.h"
#include "logger.h"
#include "memory.h"
#include "protected.h"
#include "paging.h"

#include <kernelmq/info.h>
#include <kernelmq/stdlib.h>
#include <kernelmq/module.h>

static struct KernelMQ_Info kinfo;

void main(const struct KernelMQ_Info *const kinfo_ptr)
{
    console_initialize();

    kmemset(&kinfo, 0, sizeof(struct KernelMQ_Info));

    if (!kernelmq_info_validate_and_copy(&kinfo, kinfo_ptr)) {
        logger_fail_from("main", "Invalid kernel information. Halt.");
        return;
    }

    memory_initialize(&kinfo);

    protected_initialize(&kinfo);

    // Set up a new post-relocate bootstrap pagetable so that
    // we can map in VM, and we no longer rely on pre-relocated
    // data.
    paging_clear();
    paging_identity(); // Still need 1:1 for lapic and video mem and such.
    paging_mapkernel(&kinfo);
    paging_load();
}
