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

extern void gdt_flush(GDTR* gdtr, uint64_t code_segment, uint64_t data_segment);
void gdt_init(void);
