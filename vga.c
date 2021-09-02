#include "typeDef.h"

#define VIDEO_MEM (char *)0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 50

uint16_t CursorPos = 0;

void setCursorPosRaw(uint16_t pos) 
{
    if(pos >= 0 && pos < 2000) {
		outb(0x3d4, 0x0f);
		outb(0x3d5, (uint8_t)(pos & 0xff));
		outb(0x3d4, 0x0e);
		outb(0x3d5, (uint8_t)((pos >> 8) & 0xff));
		CursorPos = pos;
	}
	return;
}

void setCursorPos(int x, int y) 
{
    uint16_t pos;
    pos = y * VGA_WIDTH + x;
    setCursorPosRaw(pos);
}

void Print(const char* text)
{
    uint8_t* textPtr = (uint8_t*) text;
    uint16_t i = CursorPos;
    while(*textPtr!=0){
        switch(*textPtr){
            case 10:
                if(CursorPos < 1920){
                    i += VGA_WIDTH - i % VGA_WIDTH;
                }
                break;
            case 13:
                i -= i % VGA_WIDTH;
                break;
            default:
                *(VIDEO_MEM + i * 2) = *textPtr;
                i++;
        }
        textPtr++;
    }
    setCursorPosRaw(i);
    return;
}

void putCh(char Letter)
{
    switch(Letter)
    {
        case 10:
            if(CursorPos < 1920){
                CursorPos += VGA_WIDTH - CursorPos % VGA_WIDTH;
            }
            CursorPos -= CursorPos % VGA_WIDTH;
            break;
        default:
            *(VIDEO_MEM + CursorPos * 2) = Letter;
            CursorPos++;
    }
    return;
}