#pragma once
#include <fb.h>
#include <screen/Console.h>
#include <font/fRend.h>

#define halt() while(1) {asm volatile("hlt");}
typedef void (*Handlers)(void);
