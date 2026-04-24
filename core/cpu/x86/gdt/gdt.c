#include "gdt.h"

GDT_ENTRY gdt[3];
GDTR gdtr;

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

	gdtr.limit = sizeof(gdt) - 1;
	gdtr.base = (uint64_t)gdt;

	gdt_flush(&gdtr, 0x08, 0x10);
}
