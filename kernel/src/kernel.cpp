#include <stdint.h>
#include "efiMemory.h"
#include "basicGraphicsDriver.h"
#include "cstr.h"
#include "math.h"
#include "memory.h"
#include "bitmap.h"
#include "pageFrameAllocator.h"


struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	void* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
} ;

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

extern "C" void _start(BootInfo* bootInfo){

    basicGraphicsDriver::Console canvas = basicGraphicsDriver::Console(bootInfo->framebuffer, bootInfo->psf1_Font); 
    
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    PageFrameAllocator newAllocator;
    newAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    newAllocator.LockPages(&_KernelStart, kernelPages);

    canvas.CursorPosition = {0, canvas.CursorPosition.Y + 16};
    canvas.Print("Free RAM: ");
    canvas.Print(to_string(newAllocator.GetFreeRAM() / 1024));
    canvas.Print(" KB ");
    canvas.CursorPosition = {0, canvas.CursorPosition.Y + 16};

    canvas.Print("Used RAM: ");
    canvas.Print(to_string(newAllocator.GetUsedRAM() / 1024));
    canvas.Print(" KB ");
    canvas.CursorPosition = {0, canvas.CursorPosition.Y + 16};

    canvas.Print("Reserved RAM: ");
    canvas.Print(to_string(newAllocator.GetReservedRAM() / 1024));
    canvas.Print(" KB ");
    canvas.CursorPosition = {0, canvas.CursorPosition.Y + 16};

    for (int t = 0; t < 20; t++){
        void* address = newAllocator.RequestPage();
        canvas.Print(to_hstring((uint64_t)address));
        canvas.CursorPosition = {0, canvas.CursorPosition.Y + 16};
    }


    // basicGraphicsDriver::Console canvas = basicGraphicsDriver::Console(bootInfo->framebuffer, bootInfo->psf1_Font); 

    // uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    // for (int i = 0; i < mMapEntries; i++){
    //     EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)bootInfo->mMap + (i * bootInfo->mMapDescSize));
    //     canvas.Print(EFI_MEMORY_TYPE_STRINGS[desc->type]);
    //     canvas.Colour = 0xffff00ff;
    //     canvas.Print(" ");
    //     canvas.Print(to_string(desc->numPages * 4096 / 1024));
    //     canvas.Print(" KB\r\n");
    //     canvas.Colour = 0xffffffff;
    // }
    

    // 
    // canvas.WriteString("HELLO WORLD", math::Point(1600, 500));
    // canvas.WriteString("HELLO \r WORLD", math::Point(1600, 550));
    // canvas.WriteString("HELLO \n WORLD", math::Point(1600, 600));
    // canvas.WriteString("HELLO \r\n WORLD", math::Point(1600, 650));
    // canvas.Draw(math::Point(100, 100), math::Point(110, 200), 0xffffffff);
    // canvas.Draw(math::Point(100, 100), math::Point(200, 110), 0xffffffff);
    return ;
}
