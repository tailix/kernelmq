#include "memory.h"

#include "config.h"

#include <kernelmq/stdlib.h>

#define FRAMES_COUNT (PAGE_DIR_SIZE * PAGE_TABLE_SIZE) // / sizeof(unsigned char))

static unsigned char frames[FRAMES_COUNT];

static void mark_used(unsigned long base, unsigned long limit);

void memory_initialize(const struct KernelMQ_Info *const kinfo)
{
    kmemset(frames, 0, sizeof(frames));

    mark_used(0, MEM_UPPER_BASE - 1);

    mark_used(kinfo->kernel_phys_base, kinfo->kernel_phys_limit);

    for (unsigned int i = 0; i < kinfo->modules_count; ++i) {
        const struct KernelMQ_Info_Module *const module = &kinfo->modules[i];

        mark_used(module->base, module->limit);
    }

    for (unsigned int i = 0; i < kinfo->areas_count; ++i) {
        const struct KernelMQ_Info_Area *const area = &kinfo->areas[i];

        if (!area->is_available) {
            mark_used(area->base, area->limit);
        }
    }
}

unsigned long memory_alloc_page()
{
    for (unsigned int i = 0; i < FRAMES_COUNT; ++i) {
        if (!frames[i]) {
            frames[i] = 0xFF;
            return i * PAGE_SIZE;
        }
    }

    return 0;
}

unsigned long memory_alloc_big_page()
{
    unsigned int start = 0;

    for (unsigned int i = 0; i < FRAMES_COUNT; ++i) {
        if (frames[i]) {
            start = i + 1;
            continue;
        }

        if (start % (PAGE_BIG_SIZE / PAGE_SIZE)) {
            continue;
        }

        if (i - start + 1 == PAGE_BIG_SIZE / PAGE_SIZE) {
            for (unsigned int j = start; j <= i; ++j) {
                frames[j] = 0xFF;
            }

            return start * PAGE_SIZE;
        }
    }

    return 0;
}

// TODO: panic if not aligned
void memory_free_page(const unsigned long addr)
{
    const unsigned long i = addr / PAGE_SIZE;

    if (i >= FRAMES_COUNT) {
        return;
    }

    frames[i] = 0;
}

// TODO: panic if not aligned
void memory_free_big_page(const unsigned long addr)
{
    const unsigned long start = addr / PAGE_SIZE;
    const unsigned long end   = start + PAGE_BIG_SIZE / PAGE_SIZE;

    for (unsigned int i = start; i <= end && i < FRAMES_COUNT; ++i) {
        frames[i] = 0;
    }
}

void mark_used(const unsigned long base, const unsigned long limit)
{
    const unsigned int start = base  / PAGE_SIZE;
    const unsigned int end   = limit / PAGE_SIZE;

    for (unsigned int i = start; i <= end; ++i) {
        frames[i] = 0xFF;
    }
}