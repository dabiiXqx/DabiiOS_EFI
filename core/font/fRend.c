#include "fRend.h"
#include <stdint.h>

int draw_glyph(int i, FB_info *info, int y, int x){
	if(i == ' ')
		return 0; //makes space instead of writing weird characters
	int iAB = GetAlphaIndex(i);
	int iNB = GetNumIndex(i);

	uint32_t dx, dy;
	uint32_t *base = (uint32_t *)info->Base;

	if(iNB <= -1){

		uint32_t glyph_px = (iAB % GLYPH_PER_ROW) * GLYPH_WIDTH;
		uint32_t glyph_py = (iAB / GLYPH_PER_ROW) * GLYPH_HEIGHT;

		for(dy = 0; dy < GLYPH_HEIGHT; dy++){
			for(dx = 0; dx < GLYPH_WIDTH; dx++){
				unsigned int pixel = (bitmap[(glyph_py + dy) * ATLAS_WIDTH + (glyph_px + dx)]) == 0xFF ? WHITE : BLACK;
				base[(y + dy) * info->Pitch + (x + dx)] = pixel;
			}
		}
	}
	else {
		uint32_t glyph_px = (iNB % GLYPH_PER_ROW) * GLYPH_WIDTH;
                uint32_t glyph_py = (iNB / GLYPH_PER_ROW) * GLYPH_HEIGHT;


                for(dy = 0; dy < GLYPH_HEIGHT; dy++){
                        for(dx = 0; dx < GLYPH_WIDTH; dx++){
                                unsigned int pixel = (bitmap[(glyph_py + dy) * ATLAS_WIDTH + (glyph_px + dx)]) == 0xFF ? WHITE : BLACK;
                                base[(y + dy) * info->Pitch + (x + dx)] = pixel;
                        }
                }
		
	}

	return 0;
}

int draw_string(const char *s, FB_info *info, int y, int x){
	
	int i;
	for(i = 0; s[i] != '\0'; i++){
		if(x > info->Width){
			x = 0;
			y += GLYPH_HEIGHT;
		}
		draw_glyph(s[i], info, y, x);
		x += GLYPH_WIDTH;
	}

	return 0;

}
