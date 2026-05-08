#include <info.h>
#include "kernel64.h"

extern uint8_t BSS_START[];
extern uint8_t BSS_END[];

FB_info *Pg_info;

__attribute__ ((section (".kernel_main")))
void kernel_main(FB_info *info, Core *bInfo) {
	kmemset(BSS_START, 0, BSS_END - BSS_START);

	Pg_info = info;

	gdt_init();
	idt_init();
	
	clear_screen(info, 0x00000000);
	RSDP *rsdp = (RSDP *)bInfo->RSDP;
	XSDT *xsdt = (XSDT *)rsdp->XsdtAddr;
	
	int validRsdp = valid_rsdp(rsdp);
	int validXsdt = valid_xsdt(xsdt);

	if((validXsdt && validRsdp)) draw_string("VALID TABLES", info, 0, 0);
	else halt();

	ACPISDTHeader *madt = find_table(xsdt, "APIC");
	
	if(madt == NULL) {
		draw_string("INVALIDMADT", info, 16, 0);
		halt();
	}
	
	MADT* Madt = (MADT*)madt;
	IOAPIC *ioapic = find_ioapic(Madt);
	if(ioapic == NULL) draw_string("IOAPIC NOT FOUND", info, 16, 0);
	else draw_string("IOAPIC FOUND", info, 16, 0);

	draw_string("WELCOME TO DABIIOS", info, 48, 0);

	halt();
}
