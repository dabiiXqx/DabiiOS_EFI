VERSION=4.0.3

CC=x86_64-elf-gcc
LD=x86_64-elf-ld
ASM=x86_64-elf-as

CFLAGS= -mno-sse \
	-mno-sse2 \
	-mno-mmx \
	-msoft-float \
	-I ../edk2/MdeModulePkg/Application/TEST1 \
	-I core \
	-ffreestanding \
	-nostdlib \
	-fno-stack-protector \
	-c \
	-fno-pie \
	-mcmodel=large

C_SOURCES := $(shell find core -name "*.c")

ASMP_SOURCES := $(shell find core -name "*.S")

ASM_SOURCES :=$(shell find core -name "*.s*")

OBJ := $(C_SOURCES:.c=.o) $(ASMP_SOURCES:.S=.o) $(ASM_SOURCES:.s=.o)

default: all

all: kernel64.bin

.PHONY: all clean

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) $< -o $@

%.o: %.s
	$(ASM) $< -o $@

kernel64.bin: $(OBJ)
	$(LD) -T linker.ld -o $@ $^

clean:
	find core -name "*.o" -delete
