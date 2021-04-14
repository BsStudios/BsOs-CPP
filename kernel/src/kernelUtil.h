#pragma once

#include <stdint.h>
#include "basicGraphicsDriver.h"
#include "cstr.h"
#include "efiMemory.h"
#include "memory.h"
#include "bitmap.h"
#include "paging/pageFrameAllocator.h"
#include "paging/pageMapIndexer.h"
#include "paging/paging.h"
#include "paging/pageTableManager.h"

struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
} ;

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo {
    PageTableManager* pageTableManager;
};

KernelInfo InitializeKernel(BootInfo* BootInfo);
