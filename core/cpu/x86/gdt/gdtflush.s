.section .text
.global gdt_flush

gdt_flush:
	lgdt (%rdi)

	pushq %rsi
	leaq .reload(%rip), %rax
	pushq %rax
	lretq
.reload:
	movw %dx, %ds
	movw %dx, %es
	movw %dx, %fs
	movw %dx, %gs
	movw %dx, %ss
	ret
