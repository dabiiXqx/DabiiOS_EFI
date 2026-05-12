#include <info.h>
#include <stdint.h>
#include "UefiMemTypes.h"

int uefi_memory_parser(Core *bInfo){
	/* experimental parser, parses uefi memory map and returns, saves total usable memory */
	uint8_t *ptr = (uint8_t *)bInfo->MemoryMap;
	uint8_t *end_ptr = ptr + bInfo->MemoryMapSize;

	uint64_t count = 0;
	for(; ptr < end_ptr; ptr += bInfo->DescriptorSize){
		MemoryDescriptor *memdesc = (MemoryDescriptor *)ptr;
		if(memdesc->Type == EfiConventionalMemory)
			count += memdesc->NumberOfPages;
	}
	return count
}
