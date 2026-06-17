#pragma once
#include <stddef.h>
#include <stdint.h>

int strlen(char *string);
void reverse(char string[]);
uint64_t min(uint64_t a, uint64_t b);
char *itoa(uint64_t value, char string[]);
