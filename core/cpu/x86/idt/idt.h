#pragma once
#include <stdint.h>

#define INT_GATE 1
#define TRAP_GATE 0
typedef struct {
	uint16_t offset_low;
	uint16_t seg_selector;
	uint8_t ist;

	uint8_t type;
	uint16_t offset_mid;
	uint32_t offset_high;

	uint32_t reserved;
}__attribute__((packed)) idt_gate;

typedef struct {
	uint16_t limit;
	uint64_t base;
}__attribute__((packed)) IDTR;

void idt_init(void);

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);
