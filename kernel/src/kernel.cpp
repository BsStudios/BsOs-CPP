#include <stdint.h>
#include "kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo){

    basicGraphicsDriver::Console con = basicGraphicsDriver::Console(bootInfo->framebuffer, bootInfo->psf1_Font);
    globalConsole = &con;

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

    globalConsole->CursorPosition = {0, 0};
    globalConsole->Print("BsOs  Version Alpha 10");
    globalConsole->CursorPosition = {0, 32};

    globalConsole->CursorPosition = {0, globalConsole->CursorPosition->Y + 16};
    globalConsole->Print("Free RAM: ");
    globalConsole->Print(to_string(GlobalAllocator.GetFreeRAM() / 1048576));
    globalConsole->Print(" MB ");
    globalConsole->CursorPosition = {0, globalConsole->CursorPosition->Y + 16};

    globalConsole->Print("Used RAM: ");
    globalConsole->Print(to_string(GlobalAllocator.GetUsedRAM() / 1048576));
    globalConsole->Print(" MB ");
    globalConsole.CursorPosition = {0, globalConsole->CursorPosition->Y + 16};

    globalConsole->Print("Reserved RAM: ");
    globalConsole->Print(to_string(GlobalAllocator.GetReservedRAM() / 1048576));
    globalConsole->Print(" MB ");
    globalConsole->CursorPosition = {0, globalConsole->CursorPosition->Y + 16};

    for (int t = 0; t < 20; t++){
        void* address = GlobalAllocator.RequestPage();
        globalConsole->Print(to_hstring((uint64_t)address));
        globalConsole->CursorPosition = {0, globalConsole->CursorPosition->Y + 16};
    }

    while(true);
}
