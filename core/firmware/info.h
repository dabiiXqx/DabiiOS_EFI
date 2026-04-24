#pragma once
#include <stdint.h>
typedef struct {
	uintptr_t Base;
	unsigned Width;
	unsigned Height;
	unsigned Pitch;
	unsigned long long Size;
} FB_info;

typedef struct {
	uintptr_t RSDP;
	void *MemoryMap;
	unsigned long long MemoryMapSize;
	unsigned long long DescriptorSize;
} Core;

typedef struct {
	unsigned int Type;
	unsigned int Pad;
	unsigned long long PhysicalStart;
	unsigned long long VirtualStart;
	unsigned long long NumberOfPages;
	unsigned long long Attribute;
} MemoryDescriptor;
