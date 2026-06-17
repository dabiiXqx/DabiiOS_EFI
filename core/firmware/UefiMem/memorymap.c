#include <info.h>
#include <stdint.h>
#include <util/memory.h>
#include <util/utils.h>
#include "UefiMemTypes.h"

uint64_t uefi_memory_parser(Core *bInfo){
	uint8_t *ptr = (uint8_t *)bInfo->MemoryMap;
	uint8_t *end_ptr = ptr + bInfo->MemoryMapSize;

	MemoryDescriptor md;
	uint64_t copy_size = min(sizeof(md), bInfo->DescriptorSize);

	uint64_t count = 0;
	for(; ptr < end_ptr; ptr += bInfo->DescriptorSize){
		kmemset(&md, 0, sizeof(md));
		kmemcpy(&md, ptr, copy_size);

		count += md.NumberOfPages;
	}
	return count;
}
