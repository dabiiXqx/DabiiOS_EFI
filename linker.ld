OUTPUT_FORMAT("binary")
ENTRY(kernel_main)

SECTIONS
{
	. = 0x80000000;
	.kernelmain :
	{
		KEEP(*(.kernel_main))
	}

	.text :
	{
		*(.text)
	}

	.rodata :
	{
		*(.rodata)
	}

	.data :
	{
		*(.data)
	}

	.bss :
	{
		BSS_START = .;
		*(.bss) *(COMMON)
		BSS_END = .;
	}

	EOK = .;
}
