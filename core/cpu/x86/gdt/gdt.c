#include "gdt.h"

GDT_ENTRY gdt[5];
TSS tss;
GDTR gdtr;
char ist1[4096]; //4KiB

void gdt_init(void){

	gdt[1].limit = 0xffff;
	gdt[1].base_low = 0x0000;
	gdt[1].base_mid = 0x00;
	gdt[1].access = 0x9a;
	gdt[1].attr = 0xaf;
	gdt[1].base_high = 0x00;

	gdt[2].limit = 0xffff;
	gdt[2].base_low = 0x0000;
	gdt[2].base_mid = 0x00;
	gdt[2].access = 0x92;
	gdt[2].attr = 0xcf;
	gdt[2].base_high = 0x00;

	tss.ist1 = (uint64_t)(ist1 + sizeof(ist1));

	uint8_t limit_4bit = ((sizeof(tss) - 1) >> 16) & 0xF;
	uint64_t base = (uint64_t)&tss;

	TSS_DESC *tss_desc = (TSS_DESC *)&gdt[3];

	tss_desc->limit = (sizeof(tss)-1) & 0xFFFF;
	tss_desc->base_low = base & 0xFFFF;
	tss_desc->base_mid = (base >> 16) & 0xFF;
	tss_desc->access = 0x89;
	tss_desc->attr = 0x00 | limit_4bit;
	tss_desc->base_high = (base >> 24) & 0xFF;
	tss_desc->base_address = (base >> 32) & 0xFFFFFFFF;
	tss_desc->reserved = 0;

	gdtr.limit = sizeof(gdt) - 1;
	gdtr.base = (uint64_t)gdt;

	gdt_flush(&gdtr, 0x08, 0x10);
	tss_flush(0x18);
}
