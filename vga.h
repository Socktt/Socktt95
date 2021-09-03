#include "typeDef.h"

#define VIDEO_MEM (char *)0xb8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 50

void setCursorPosRaw(uint16_t pos);
void setCursorPos(int x, int y);
void Print(const char* text);
void putCh(char Letter);
