#include <info.h>
#include "Console.h"

void clear_screen(FB_info *info, unsigned int color) {
	unsigned int *base = (unsigned int *)info->Base;

	int y, x;
	for(y = 0; y < info->Height; y++){
		for(x = 0; x < info->Width; x++){
			base[y * info->Pitch + x] = color;
		}
	}
}
