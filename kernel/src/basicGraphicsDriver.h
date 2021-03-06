#pragma once
#include "math.h"
#include "frameBuffer.h"
#include "simpleFonts.h"
#include <stdint.h>

class basicGraphicsDriver{
    public:
    class Canvas{
        public:
        Canvas(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
        Framebuffer* TargetFramebuffer;
        PSF1_FONT* PSF1_Font;
        unsigned int Colour;
        void WriteString(const char* str, math::Point position);
        void PutChar(char chr, unsigned int xOff, unsigned int yOff);
        void drawRectangle(math::Point p1, math::Point p2, unsigned int Colour);
        void drawPixel(math::Point p1, unsigned int Colour);
        void Clear(unsigned int Colour);
    };
    class Console{
        public:
        Console(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font);
        math::Point CursorPosition = math::Point();
        Framebuffer* TargetFramebuffer;
        PSF1_FONT* PSF1_Font;
        unsigned int Colour;
        void Print(const char* str);
        void PutChar(char chr, unsigned int xOff, unsigned int yOff);
        void Clear(uint32_t colour);
        void Next();
    };
};
