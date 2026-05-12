#include "AcpiTable.h"

int checksig(void *table, unsigned int len, const char *sig){
	char *Table = (char *)table;
	int i;
	for(i = 0; i < len; i++)
		if(Table[i] != sig[i]) return 0;
	return 1;
}
int checksum_table(void *table, unsigned int len){
	uint8_t sum = 0;
	uint8_t *bytes = (uint8_t *)table;
	int i;
	for(i = 0; i < len; i++){
		sum += bytes[i];
	}
	if (sum != 0) return 0;
	return 1;
}

int valid_rsdp(RSDP *rsdp){
	int ValSig = checksig((void *)rsdp, 8, "RSD PTR ");
	int len = (rsdp->Revision >= 2) ? rsdp->Length : 20;
	int ValCheck = checksum_table((void*)rsdp, len);
	if(!ValSig || !ValCheck) return 0;
	return 1;

}

int valid_xsdt(XSDT *xsdt){
	int ValSig = checksig((void *)xsdt, 4, "XSDT");
	int ValCheck = checksum_table((void *)xsdt, xsdt->header.Length);
	
	if(!ValSig || !ValCheck) return 0;

	return 1;
}

ACPISDTHeader *find_table(XSDT *xsdt, char *table){

	int count = ((xsdt->header.Length - sizeof(ACPISDTHeader)) / 8);
	uint64_t *Entries = (uint64_t *)((uint8_t *)xsdt + sizeof(ACPISDTHeader));

	ACPISDTHeader *Table = NULL;
	for(int i = 0; i < count; i++){
		Table = (ACPISDTHeader *)(uintptr_t)Entries[i];
		if((checksig(Table, 4, table)) == 1 && (checksum_table(Table, Table->Length)) == 1) return Table;
	}

	return NULL;
}

IOAPIC *find_ioapic(MADT *madt){

	uint8_t *Entry_ptr = (uint8_t*)madt + sizeof(ACPISDTHeader) + 8;
	uint8_t *end = (uint8_t*)madt + madt->header.Length;
	ICS *Entry = NULL;

	while(Entry_ptr < end){
		Entry = (ICS*)Entry_ptr;
		if(Entry->type == 1)
			return (IOAPIC*)Entry_ptr;

		Entry_ptr += Entry->length;
	}

	return NULL;

}
