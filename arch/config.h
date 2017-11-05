#ifndef KERNELMQ_INCLUDED_CONFIG
#define KERNELMQ_INCLUDED_CONFIG 1

#define MEM_UPPER_BASE ((unsigned long)(1 * 1024 * 1024)) // 1 MB

#define PAGE_DIR_SIZE   1024
#define PAGE_TABLE_SIZE 1024

#define PAGE_SIZE     4096
#define PAGE_BIG_SIZE (PAGE_SIZE * PAGE_TABLE_SIZE)

#define IDT_SIZE 256 // maximal size

#define GDT_NULL_INDEX      0
#define GDT_KERNEL_CS_INDEX 1
#define GDT_KERNEL_DS_INDEX 2
#define GDT_USER_CS_INDEX   3
#define GDT_USER_DS_INDEX   4
#define GDT_SIZE            5

#define GDT_DESCRIPTOR_SIZE 8 // bytes

#define GDT_SEGMENT_SELECTOR(n) ((n) * GDT_DESCRIPTOR_SIZE)

#define GDT_NULL_SELECTOR      GDT_SEGMENT_SELECTOR(GDT_NULL_INDEX)
#define GDT_KERNEL_CS_SELECTOR GDT_SEGMENT_SELECTOR(GDT_KERNEL_CS_INDEX)
#define GDT_KERNEL_DS_SELECTOR GDT_SEGMENT_SELECTOR(GDT_KERNEL_DS_INDEX)
#define GDT_USER_CS_SELECTOR   GDT_SEGMENT_SELECTOR(GDT_USER_CS_INDEX)
#define GDT_USER_DS_SELECTOR   GDT_SEGMENT_SELECTOR(GDT_USER_DS_INDEX)

#define INT_EXCEPTION_COUNT 32
#define INT_HWINT_COUNT     16
#define INT_TOTAL_COUNT     (INT_EXCEPTION_COUNT + INT_HWINT_COUNT)

#define INT_EXCEPTION_FIRST 0
#define INT_EXCEPTION_LAST (INT_EXCEPTION_FIRST + INT_EXCEPTION_COUNT - 1)

#define INT_HWINT_FIRST (INT_EXCEPTION_LAST + 1)
#define INT_HWINT_LAST  (INT_HWINT_FIRST + INT_HWINT_COUNT - 1)

#endif
