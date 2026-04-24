#pragma once
#include <info.h>
#include <stddef.h>
#include <stdint.h>
#include "font/fRend.h"
#include "acpi/AcpiTable.h"
#include "screen/Console.h"
#include "firmware/UefiMemTypes.h"
#include "cpu/x86/gdt/gdt.h"
#include "cpu/x86/idt/idt.h"
#include "util/mem.h"
#define halt() while (1) { asm volatile("hlt"); }

extern FB_info *Pg_info;
