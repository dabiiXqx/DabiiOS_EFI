#include <info.h>
#include "bitmap/KFont.h"

#define GetIndex(c) ((c >= 'A' && c <= 'Z') ? c - 'A' : -1)

#define WHITE 0x00FFFFFF
#define BLACK 0x00000000

#define ATLAS_WIDTH 96
#define ATLAS_HEIGHT 192

#define GLYPH_WIDTH 16
#define GLYPH_HEIGHT 16
#define GLYPH_PER_ROW 6

int draw_glyph(int index, FB_info *framebuffer_info, int y, int x);
int draw_string(const char *text, FB_info *framebuffer_info ,int y, int x);
