#pragma once
#include <stddef.h>
#include <info.h>

void *kmemset(void* dest, int c, size_t n);
void *kmemcpy(void *dest, const void* src, size_t n);
void *pmm_init(Core *bInfo);
