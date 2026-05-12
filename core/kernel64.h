#pragma once
#include <info.h>
#include <stddef.h>
#include <stdint.h>
#include "font/fRend.h"
#include "firmware/acpi/AcpiTable.h"
#include "screen/Console.h"
#include "cpu/x86/gdt/gdt.h"
#include "cpu/x86/idt/idt.h"
#include "util/mem.h"
#include "firmware/UefiMem/memorymap.h"

#define halt() while (1) { asm volatile("hlt"); }

extern FB_info *Pg_info;
