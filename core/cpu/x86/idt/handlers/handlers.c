#include "handlers.h"

const char *emsg[] = {
	"DIVIDE ERROR",
	"DEBUG EXCEPTION",
	"NMI",
	"BREAKPOINT",
	"OVERFLOW",
	"BOUND RANGE",
	"INVALID OPCODE",
	"DEVICE NOT AVAILABLE",
	"DOUBLE FAULT",
	"CSO",
	"INVALID TSS",
	"SEGMENT NOT PRESENT",
	"STACK SEGMENT FAULT",
	"GENERAL PROTECTION",
	"PAGEFAULT",
	"RESERVED",
	"FLOATING POINT ERROR",
	"ALIGNMENT CHECK",
	"MACHINE CHECK",
	"FLOATING POINT EXCEPTION",
	"VIRTUALIZATION EXCEPTION",
	"CONTROL PROTECTION EXCEPTION",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED"
};

void DE_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[0], Pg_info, 0, 0);
    halt();
}
void DB_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[1], Pg_info, 0, 0);
    halt();
}
void NMI_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[2], Pg_info, 0, 0);
    halt();
}
void BP_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[3], Pg_info, 0, 0);
    halt();
}
void OF_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[4], Pg_info, 0, 0);
    halt();
}
void BR_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[5], Pg_info, 0, 0);
    halt();
}
void UD_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[6], Pg_info, 0, 0);
    halt();
}
void NM_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[7], Pg_info, 0, 0);
    halt();
}
void DF_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[8], Pg_info, 0, 0);
    halt();
}
void CSO_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[9], Pg_info, 0, 0);
    halt();
}
void TS_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[10], Pg_info, 0, 0);
    halt();
}
void NP_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[11], Pg_info, 0, 0);
    halt();
}
void SS_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[12], Pg_info, 0, 0);
    halt();
}
void GP_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[13], Pg_info, 0, 0);
    halt();
}
void PF_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[14], Pg_info, 0, 0);
    halt();
}
void res15_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[15], Pg_info, 0, 0);
    halt();
}
void MF_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[16], Pg_info, 0, 0);
    halt();
}
void AC_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[17], Pg_info, 0, 0);
    halt();
}
void MC_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[18], Pg_info, 0, 0);
    halt();
}
void XM_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[19], Pg_info, 0, 0);
    halt();
}
void VE_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[20], Pg_info, 0, 0);
    halt();
}
void CP_exception(void) { // CP doesn't mean CSAM material here, it's an exception mnemonic.
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[21], Pg_info, 0, 0);
    halt();
}
void res22_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[22], Pg_info, 0, 0);
    halt();
}
void res23_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[23], Pg_info, 0, 0);
    halt();
}
void res24_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[24], Pg_info, 0, 0);
    halt();
}
void res25_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[25], Pg_info, 0, 0);
    halt();
}
void res26_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[26], Pg_info, 0, 0);
    halt();
}
void res27_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[27], Pg_info, 0, 0);
    halt();
}
void res28_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[28], Pg_info, 0, 0);
    halt();
}
void res29_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[29], Pg_info, 0, 0);
    halt();
}
void res30_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[30], Pg_info, 0, 0);
    halt();
}
void res31_exception(void) {
    clear_screen(Pg_info, 0x00AAAAAA);
    draw_string(emsg[31], Pg_info, 0, 0);
    halt();
}

Handlers func_table[32] = {
	DE_exception,
	DB_exception,
	NMI_exception,
	BP_exception,
	OF_exception,
	BR_exception,
	UD_exception,
	NM_exception,
	DF_exception,
	CSO_exception,
	TS_exception,
	NP_exception,
	SS_exception,
	GP_exception,
	PF_exception,
	res15_exception,
	MF_exception,
	AC_exception,
	MC_exception,
	XM_exception,
	VE_exception,
	CP_exception,
	res22_exception,
	res23_exception,
	res24_exception,
	res25_exception,
	res26_exception,
	res27_exception,
	res28_exception,
	res29_exception,
	res30_exception,
	res31_exception
};
