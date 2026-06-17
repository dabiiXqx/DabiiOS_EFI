#include "memory.h"
#include "utils.h"
#include <firmware/UefiMem/memorymap.h>
#include <firmware/UefiMem/UefiMemTypes.h>
#include <info.h>

void *kmemset(void *dest, int c, size_t n){
	unsigned char *ptr = (unsigned char *)dest;
	
	while(n--){
		*ptr++ = (unsigned char)c;
	}

	return dest;
}

void *kmemcpy(void *dest, const void* src, size_t n) {
	uint8_t *pdest = (uint8_t *)dest;
	uint8_t *psrc = (uint8_t *)src;

	while(n--)
		*pdest++ = *psrc++;

	return dest;
}

void *pmm_init(Core *bInfo){
	//returns bitmap location in memory
	void *bitmap_alloc = (void *)0;
	uint64_t total_pages = uefi_memory_parser(bInfo);
	uint64_t bitmap_bytes = (total_pages + 7)/8; // total_pages + 7 is there for rounding
	
	uint64_t bitmap_pages = (bitmap_bytes + 4095) / 4096;
	
	uint8_t *ptr = (uint8_t *)bInfo->MemoryMap;
	uint8_t *end_ptr = ptr + bInfo->MemoryMapSize;

	MemoryDescriptor md;

	uint64_t copy_size = min(sizeof(md), bInfo->DescriptorSize);

	for(; ptr < end_ptr; ptr += bInfo->DescriptorSize){
		kmemset(&md, 0, sizeof(md));
		kmemcpy(&md, ptr, copy_size);

		if(md.Type == EfiConventionalMemory && md.NumberOfPages >= bitmap_pages) {
			bitmap_alloc = (void *)md.PhysicalStart;
			break;
		}
	}

	if(bitmap_alloc == (void *)0)
		return (void *)0;

	uint8_t* bitmap = (uint8_t *)bitmap_alloc;

	for(uint64_t i = 0; i < bitmap_bytes; i++)
		bitmap[i] = 0;

	return bitmap_alloc;
}

void *pmalloc(size_t size) {
	
}
