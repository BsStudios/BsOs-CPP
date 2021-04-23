#include "panic.h"
#include "kernelUtil.h"

void Panic(const char* panicMessage){
    globalConsole->Clear(0x00ff0000);

    globalConsole->CursorPosition = {0, 0};

    globalConsole->Colour = 0;

    globalConsole->Print("Kernel Panic");

    globalConsole->Next();
    globalConsole->Next();

    globalConsole->Print(panicMessage);
}
