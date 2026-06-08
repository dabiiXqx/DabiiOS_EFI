#pragma once
#include <stddef.h>

void* kmemset(void* dest, int c, size_t n);
int strlen(char *string);
void reverse(char string[]);
char *itoa(int value, char string[]);
