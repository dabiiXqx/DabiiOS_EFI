#pragma once
#include <stdint.h>

typedef struct {
	uint16_t limit;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t attr;
	uint8_t base_high;
}__attribute__((packed)) GDT_ENTRY;

typedef struct {
	uint16_t limit;
	uint64_t base;
}__attribute__((packed)) GDTR;

typedef struct {
	uint16_t limit;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t attr;
	uint8_t base_high;
	
	uint32_t base_address;
	
	uint32_t reserved;
}__attribute__((packed)) TSS_DESC;

typedef struct {
	uint32_t reserved0;

	uint64_t rsp0;
	uint64_t rsp1;
	uint64_t rsp2;

	uint64_t reserved1;

	uint64_t ist1;
	uint64_t ist2;
	uint64_t ist3;
	uint64_t ist4;
	uint64_t ist5;
	uint64_t ist6;
	uint64_t ist7;

	uint64_t reserved2;
	uint16_t reserved3;

	uint16_t iomap_base;
}__attribute__((packed)) TSS;

//task switching is NOT available on x86_64, so there's not going to be a task gate descriptor



extern void gdt_flush(GDTR* gdtr, uint64_t code_segment, uint64_t data_segment);
extern void tss_flush(uint16_t TSS_selector);
void gdt_init(void);
