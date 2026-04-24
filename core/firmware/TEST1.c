#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/LoadedImage.h>
#include <Guid/Acpi.h>
#include <Guid/FileInfo.h>
#include <Library/BaseMemoryLib.h>
#include "info.h"

#define halt() while(1) {asm volatile ("hlt");}

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE* SystemTable) {
	
	SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_WHITE | EFI_BACKGROUND_BLUE);
	SystemTable->ConOut->ClearScreen(SystemTable->ConOut);

	EFI_GRAPHICS_OUTPUT_PROTOCOL *gop = NULL;
	EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	EFI_STATUS status;

	status = gBS->LocateProtocol(&gopGuid, NULL, (VOID **)&gop);
	if(EFI_ERROR(status)){
		Print(L"Failure in calling LocateProtocol()\n");
		return status;
	}
	Print(L"GOP successfully initialized!\n");
	
	FB_info gopinfo;
	FB_info *gInfo = &gopinfo;

	Core bootinfo;
	Core *bInfo = &bootinfo;


	EFI_LOADED_IMAGE_PROTOCOL *img = NULL;

	status = gBS->OpenProtocol(
			ImageHandle,
			&gEfiLoadedImageProtocolGuid,
			(VOID **)&img,
			ImageHandle,
			NULL,
			EFI_OPEN_PROTOCOL_GET_PROTOCOL
		);
	if(EFI_ERROR(status)){
		Print(L"Failure in OpenProtocol() Loaded Image: %r\n", status);
		return status;
	}

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs = NULL;
	EFI_FILE_PROTOCOL *root = NULL;
	EFI_FILE_PROTOCOL *kernel = NULL;

	status = gBS->OpenProtocol(
		img->DeviceHandle,
		&gEfiSimpleFileSystemProtocolGuid,
		(VOID **)&fs,
		ImageHandle,
		NULL,
		EFI_OPEN_PROTOCOL_GET_PROTOCOL
	);

	if(EFI_ERROR(status)){
		Print(L"Failure in OpenProtocol() Simple file system protocol: %r\n", status);
		return status;
	}

	status = fs->OpenVolume(fs, &root);

	if(EFI_ERROR(status)){
		Print(L"Failure in OpenVolume(): %r\n");
		return status;
	}

	status = root->Open(root, &kernel, L"OS\\kernel64.bin", EFI_FILE_MODE_READ, 0);

	if(EFI_ERROR(status)){
		Print(L"Failure in Open(): %r\n", status);
		return status;
	}

	Print(L"Kernel found! allocating pages ...\n");

	EFI_FILE_INFO *info = NULL;
	UINTN info_size = sizeof(EFI_FILE_INFO) + 512;
	status = gBS->AllocatePool(EfiLoaderData, info_size, (VOID **)&info);

	if(EFI_ERROR(status)){
		Print(L"Failure in AllocatePool(): %r\n", status);
		return status;
	}
	status = kernel->GetInfo(kernel, &gEfiFileInfoGuid, &info_size, (VOID *)info);

	if(EFI_ERROR(status)){
		Print(L"Failure in GetInfo(): %r\n", status);
		return status;
	}	
	
	EFI_PHYSICAL_ADDRESS kernel_address = 0x80000000;
	UINTN kSize = info->FileSize;
	gBS->FreePool(info);
	status = gBS->AllocatePages(
		AllocateAddress,
		EfiLoaderData,
		EFI_SIZE_TO_PAGES(kSize),
		&kernel_address
	);

	if(EFI_ERROR(status)){
		Print(L"Error, address 0x80000000 is reserved.\n");
		return status;
	}

	Print(L"Allocated successfully! Loading DabiiOS ...\n");

	gInfo->Base = gop->Mode->FrameBufferBase;
	gInfo->Width = gop->Mode->Info->HorizontalResolution;
	gInfo->Height = gop->Mode->Info->VerticalResolution;
	gInfo->Pitch = gop->Mode->Info->PixelsPerScanLine;
	gInfo->Size = (unsigned long long)gop->Mode->FrameBufferSize;

	status = kernel->Read(kernel, &kSize, (VOID *)kernel_address);
	if(EFI_ERROR(status)){
		Print(L"Failed to read kernel: %r\n", status);
		return status;
	}

	void *RSDP = NULL;
	UINTN i;
	EFI_CONFIGURATION_TABLE *entry;
	for(i = 0; i < SystemTable->NumberOfTableEntries; i++){
		entry = &SystemTable->ConfigurationTable[i];
		if(CompareGuid(&entry->VendorGuid, &gEfiAcpiTableGuid)){
			RSDP = entry->VendorTable;
			break;
		}
	}

	if(RSDP == NULL){
		for(i = 0; i < SystemTable->NumberOfTableEntries; i++){
			entry = &SystemTable->ConfigurationTable[i];
			if(CompareGuid(&entry->VendorGuid, &gEfiAcpi10TableGuid)){
				RSDP = entry->VendorTable;
				break;
			}
		}
	}

	bInfo->RSDP = (uintptr_t)RSDP;
	UINTN map_size = 0;
	UINTN map_key = 0;
	UINTN descriptor_size = 0;
	UINT32 descriptor_version = 0;

	gBS->GetMemoryMap(&map_size, NULL, &map_key, &descriptor_size, &descriptor_version);

	map_size += descriptor_size * 2;
	EFI_MEMORY_DESCRIPTOR *map = NULL;
	gBS->AllocatePool(EfiLoaderData, map_size, (VOID **)&map);

	gBS->GetMemoryMap(&map_size, map, &map_key, &descriptor_size, &descriptor_version);
	bInfo->MemoryMap = (void *)map;
	bInfo->MemoryMapSize = (unsigned long long)map_size;
	bInfo->DescriptorSize = (unsigned long long)descriptor_size;
	status = gBS->ExitBootServices(ImageHandle, map_key);
	
	if(EFI_ERROR(status)){
		Print(L"Failure in ExitBootServices: %r\n", status);
		halt();
	}
	
	asm volatile("cli");
	typedef void (*kernelmain)(FB_info *, Core *);
	kernelmain jump = (kernelmain)kernel_address;
	jump(gInfo, bInfo);
	halt();
	return EFI_SUCCESS;
}
