#include <stdint.h>

struct tss_entry
{
	uint32_t prev_tss;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldt;
	uint16_t trap;
	uint16_t iomap_base;
};

struct tss_entry tss =
{
	.ss0 = 0x10 /* Kernel Data Segment */,
	.esp0 = 0,
	.es = 0x10 /* Kernel Data Segment */,
	.cs = 0x08 /* Kernel Code Segment */,
	.ds = 0x13 /* Kernel Data Segment */,
	.fs = 0x13 /* Kernel Data Segment */,
	.gs = 0x13 /* Kernel Data Segment */,
};

// TODO: Magic values ohoy! Fix that.

#define GRAN_64_BIT_MODE (1 << 5)
#define GRAN_32_BIT_MODE (1 << 6)
#define GRAN_4KIB_BLOCKS (1 << 7)

struct gdt_entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
};

#define GDT_ENTRY(base, limit, access, granularity) \
	{ (limit) & 0xFFFF,                                /* limit_low */ \
	  (base) >> 0 & 0xFFFF,                            /* base_low */ \
	  (base) >> 16 & 0xFF,                             /* base_middle */ \
	  (access) & 0xFF,                                 /* access */ \
	  ((limit) >> 16 & 0x0F) | ((granularity) & 0xF0), /* granularity */ \
	  (base) >> 24 & 0xFF,                             /* base_high */ }

struct gdt_entry gdt[] =
{
	/* 0x00: Null segment */
	GDT_ENTRY(0, 0, 0, 0),

	/* 0x08: Kernel Code Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0x9A, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x10: Kernel Data Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0x92, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x18: User Code Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0xFA, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x20: User Data Segment. */
	GDT_ENTRY(0, 0xFFFFFFFF, 0xF2, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	/* 0x28: Task Switch Segment. */
	GDT_ENTRY(0 /*((uintptr_t) &tss)*/, sizeof(tss) - 1, 0xE9, 0x00),
};

uint16_t gdt_size_minus_one = sizeof(gdt) - 1;
