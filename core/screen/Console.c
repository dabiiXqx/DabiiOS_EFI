#include <info.h>
#include "Console.h"

void clear_screen(unsigned int color) {
	unsigned int *base = (unsigned int *)Pg_info->Base;

	int y, x;
	for(y = 0; y < Pg_info->Height; y++){
		for(x = 0; x < Pg_info->Width; x++){
			base[y * Pg_info->Pitch + x] = color;
		}
	}
}
