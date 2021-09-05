#include "typeDef.h"

#define VIDEO_MEM (char *)0xb8000
//#define VGA_WIDTH 80
//#define VGA_HEIGHT 50
#define VGA_WIDTH 320
#define VGA_HEIGHT 200

void setCursorPosRaw(uint16_t pos);
void setCursorPos(int x, int y);
void Print(const char* text);
void putCh(char Letter);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void drawPixel(uint8_t x, uint8_t y, uint8_t colour);
void clearScreen();
void colourScreen(uint8_t colour);
void graphicsClearScreen(uint8_t colour);
void drawPalette(uint8_t x, uint8_t y);