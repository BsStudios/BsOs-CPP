#include "basicGraphicsDriver.h"

basicGraphicsDriver::Canvas::Canvas(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    Colour = 0xffffffff;
}

void basicGraphicsDriver::Canvas::WriteString(const char* str, math::Point position)
{
    math::Point CursorPosition = position;
    char* chr = (char*)str;
    while(*chr != 0){
        if(*chr == 13){
            CursorPosition.X = position.X;
        }
        else if(*chr == 10){
            CursorPosition.Y += 16;
        }
        else {
            PutChar(*chr, CursorPosition.X, CursorPosition.Y);
            CursorPosition.X+=8;
            if(CursorPosition.X + 8 > TargetFramebuffer->Width)
            {
                break;
            }
        }
        chr++;
    }
}

void basicGraphicsDriver::Canvas::PutChar(char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = Colour;
                }

        }
        fontPtr++;
    }
}

void basicGraphicsDriver::Canvas::drawRectangle(math::Point p1, math::Point p2, unsigned int Colour){

    for (unsigned long y = p1.Y; y < p2.Y; y++){
        for (unsigned long x = p1.X; x < p2.X; x++){
            drawPixel(math::Point(x, y), Colour);
        }
    }
}

void basicGraphicsDriver::Canvas::drawPixel(math::Point p1, unsigned int Colour){
    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    *(unsigned int*)(pixPtr + p1.X + (p1.Y * TargetFramebuffer->PixelsPerScanLine)) = Colour;
}

void basicGraphicsDriver::Canvas::clear(unsigned int Colour){
    for (unsigned long y = 0; y < TargetFramebuffer->Height; y++){
        for (unsigned long x = 0; x < TargetFramebuffer->Width; x++){
            drawPixel(math::Point(x, y), Colour);
        }
    }
}

void basicGraphicsDriver::Canvas::Clear(unsigned int colour){
    uint64_t fbBase = (uint64_t)TargetFramebuffer->BaseAddress;
    uint64_t bytesPerScanline = TargetFramebuffer->PixelsPerScanLine * 4;
    uint64_t fbHeight = TargetFramebuffer->Height;
    uint64_t fbSize = TargetFramebuffer->BufferSize;

    for (int verticalScanline = 0; verticalScanline < fbHeight; verticalScanline ++){
        uint64_t pixPtrBase = fbBase + (bytesPerScanline * verticalScanline);
        for (uint32_t* pixPtr = (uint32_t*)pixPtrBase; pixPtr < (uint32_t*)(pixPtrBase + bytesPerScanline); pixPtr ++){
            *pixPtr = colour;
        }
    }
}



basicGraphicsDriver::Console::Console(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    Colour = 0xffffffff;
    CursorPosition = math::Point();
}

void basicGraphicsDriver::Console::Print(const char* str)
{
    char* chr = (char*)str;
    while(*chr != 0){
        if(*chr == 13){
            CursorPosition.X = 0;
        }
        else if(*chr == 10){
            CursorPosition.Y += 16;
        }
        else {
            PutChar(*chr, CursorPosition.X, CursorPosition.Y);
            CursorPosition.X+=8;
            if(CursorPosition.X + 8 > TargetFramebuffer->Width)
            {
                CursorPosition.X = 0;
                CursorPosition.Y += 16;
            }
        }
        chr++;
    }
}

void basicGraphicsDriver::Console::PutChar(char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = Colour;
                }

        }
        fontPtr++;
    }
}

void basicGraphicsDriver::Console::Clear(uint32_t colour){
    uint64_t fbBase = (uint64_t)TargetFramebuffer->BaseAddress;
    uint64_t bytesPerScanline = TargetFramebuffer->PixelsPerScanLine * 4;
    uint64_t fbHeight = TargetFramebuffer->Height;
    uint64_t fbSize = TargetFramebuffer->BufferSize;

    for (int verticalScanline = 0; verticalScanline < fbHeight; verticalScanline ++){
        uint64_t pixPtrBase = fbBase + (bytesPerScanline * verticalScanline);
        for (uint32_t* pixPtr = (uint32_t*)pixPtrBase; pixPtr < (uint32_t*)(pixPtrBase + bytesPerScanline); pixPtr ++){
            *pixPtr = colour;
        }
    }
}

void BasicRenderer::Next(){
    CursorPosition.X = 0;
    CursorPosition.Y += 16;
}