#include <stdint.h>
#include "efiMemory.h"
#include "basicGraphicsDriver.h"
#include "cstr.h"
#include "math.h"


struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	void* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
} ;


extern "C" void _start(BootInfo* bootInfo){

    basicGraphicsDriver::Console canvas = basicGraphicsDriver::Console(bootInfo->framebuffer, bootInfo->psf1_Font); 

    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    for (int i = 0; i < mMapEntries; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)bootInfo->mMap + (i * bootInfo->mMapDescSize));
        canvas.Print(EFI_MEMORY_TYPE_STRINGS[desc->type]);
        canvas.Colour = 0xffff00ff;
        canvas.Print(" ");
        canvas.Print(to_string(desc->numPages * 4096 / 1024));
        canvas.Print(" KB\r\n");
        canvas.Colour = 0xffffffff;
    }

    // 
    // canvas.WriteString("HELLO WORLD", math::Point(1600, 500));
    // canvas.WriteString("HELLO \r WORLD", math::Point(1600, 550));
    // canvas.WriteString("HELLO \n WORLD", math::Point(1600, 600));
    // canvas.WriteString("HELLO \r\n WORLD", math::Point(1600, 650));
    // canvas.Draw(math::Point(100, 100), math::Point(110, 200), 0xffffffff);
    // canvas.Draw(math::Point(100, 100), math::Point(200, 110), 0xffffffff);
    return ;
}
