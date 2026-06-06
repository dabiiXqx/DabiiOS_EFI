.section .text
.global tss_flush

tss_flush:
	ltr %di
	ret
