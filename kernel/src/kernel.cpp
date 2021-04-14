#include <stdint.h>
#include "kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo){

    basicGraphicsDriver::Console canvas = basicGraphicsDriver::Console(bootInfo->framebuffer, bootInfo->psf1_Font); 

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    canvas.CursorPosition = {0, 0};
    canvas.Print("BsOs  Version Alpha 10");
    canvas.CursorPosition = {0, 32};

    canvas.CursorPosition = {0, canvas.CursorPosition.Y + 16};
    canvas.Print("Free RAM: ");
    canvas.Print(to_string(GlobalAllocator.GetFreeRAM() / 1048576));
    canvas.Print(" MB ");
    canvas.CursorPosition = {0, canvas.CursorPosition.Y + 16};

    canvas.Print("Used RAM: ");
    canvas.Print(to_string(GlobalAllocator.GetUsedRAM() / 1048576));
    canvas.Print(" MB ");
    canvas.CursorPosition = {0, canvas.CursorPosition.Y + 16};

    canvas.Print("Reserved RAM: ");
    canvas.Print(to_string(GlobalAllocator.GetReservedRAM() / 1048576));
    canvas.Print(" MB ");
    canvas.CursorPosition = {0, canvas.CursorPosition.Y + 16};

    for (int t = 0; t < 20; t++){
        void* address = GlobalAllocator.RequestPage();
        canvas.Print(to_hstring((uint64_t)address));
        canvas.CursorPosition = {0, canvas.CursorPosition.Y + 16};
    }

    while(true);

    return ;
}
