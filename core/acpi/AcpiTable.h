#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct {

    uint8_t sig[8];
    uint8_t checksum;
    uint8_t OEM[6];
    uint8_t Revision;
    uint32_t RsdtAddr;

    /* Here comes v2 specific acpi shit */

    uint32_t Length;
    uint64_t XsdtAddr;
    uint8_t ExtendedChecksum;
    uint8_t Reserved[3];

} __attribute__((packed)) RSDP;

typedef struct {

    uint8_t sig[4];
    uint32_t Length;
    uint8_t Revision;
    uint8_t Checksum;

    uint8_t OEM[6];
    uint8_t OemTable[8];
    uint32_t OemRevision;
    uint32_t CreatorID;

    uint32_t CreatorRevision;

} __attribute__((packed)) ACPISDTHeader;

typedef struct {

    ACPISDTHeader header;
    uint64_t Entry[];

} __attribute__((packed)) XSDT;

typedef struct {

    ACPISDTHeader header;
    uint32_t LICA; //Local Interrupt Controller Address
    uint32_t flags;

} __attribute__((packed)) MADT;

typedef struct {

    uint8_t type;
    uint8_t length;

} __attribute__((packed)) ICS;

typedef struct {

    ICS header;
    uint8_t IOAPIC_ID;
    uint8_t RESERVED;
    uint32_t IOAPIC_REG_ADDR;
    uint32_t GSI_BASE;

} __attribute__((packed)) IOAPIC;

typedef struct {

    ICS header;
    uint8_t processor_id;
    uint8_t apic_id;
    uint32_t flags;

} __attribute__((packed)) LAPIC;

int checksig(void *table, unsigned int len, const char *sig);
int checksum_table(void *table, unsigned int length);
int valid_rsdp(RSDP *rsdp);
int valid_xsdt(XSDT *xsdt);
ACPISDTHeader *find_table(XSDT *xsdt, char *table);
IOAPIC* find_ioapic(MADT *madt);
