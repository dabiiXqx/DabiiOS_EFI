#include "mem.h"

void *kmemset(void *dest, int c, size_t n){
	unsigned char *ptr = (unsigned char *)dest;
	
	while(n--){
		*ptr++ = (unsigned char)c;
	}

	return dest;
}
