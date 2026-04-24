#include "idt.h"

idt_gate idt[256];
IDTR idtr;

void (*isr_stubs[])(void) = {
    isr0,  isr1,  isr2,  isr3,
    isr4,  isr5,  isr6,  isr7,
    isr8,  isr9,  isr10, isr11,
    isr12, isr13, isr14, isr15,
    isr16, isr17, isr18, isr19,
    isr20, isr21, isr22, isr23,
    isr24, isr25, isr26, isr27,
    isr28, isr29, isr30, isr31,
};

void set_idt_gate(void (*isr)(void), uint8_t index, int gate){
	uint64_t routine = (uint64_t)(uintptr_t)isr;

	idt[index].offset_low = routine & 0xFFFF;
	idt[index].seg_selector = 0x08;
	idt[index].ist = 0;
	idt[index].type = (gate) ? 0x8E : 0x8F;
	idt[index].offset_mid = (routine >> 16) & 0xFFFF;
	idt[index].offset_high = (routine >> 32) & 0xFFFFFFFF;

	return;
}

void idt_flush(IDTR *idtr) {
	asm volatile("lidt (%0)" : : "r"(idtr) : "memory");
	return;
}

void idt_init(void){
	for(int i = 0; i < 32; i++)
		set_idt_gate(isr_stubs[i], i, INT_GATE);

	idtr.limit = sizeof(idt) - 1;
	idtr.base = (uint64_t)idt;

	idt_flush(&idtr);
}
