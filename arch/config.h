#ifndef KERNELMQ_INCLUDED_CONFIG
#define KERNELMQ_INCLUDED_CONFIG 1

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

#endif
