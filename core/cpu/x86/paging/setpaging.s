.section .text
.global setup_paging

setup_paging:
	movq %cr0, %rax
	orl $0x80000000, %eax
	movq %rax, %cr0
	ret
