#include "system.h"
#include "vga.h"
#include "typeDef.h"
#include "port_io.h"
#include "mouse.h"
#include "gui.h"

uint8_t mouseCycle;
uint8_t mousePacket[4];
uint8_t MousePacketReady = 0;
struct Point MousePosition;

void ProcessMousePacket()
{
    if (!MousePacketReady) return;
    MousePacketReady = 0;

    uint8_t xNegative, yNegative, xOverflow, yOverflow;
    
    if (mousePacket[0] & PS2XSign)
    {
        xNegative = 1;
    } else xNegative = 0;

    if (mousePacket[0] & PS2YSign)
    {
        yNegative = 1;
    } else yNegative = 0;

    if (mousePacket[0] & PS2XOverflow)
    {
        xOverflow = 1;
    } else xOverflow = 0;

    if (mousePacket[0] & PS2YOverflow)
    {
        yOverflow = 1;
    } else yOverflow = 0;

    if (!xNegative)
    {
        MousePosition.x += mousePacket[1];
        if (xOverflow)
        {
            MousePosition.x += 255;
        }
    } else
    {
        mousePacket[1] = 256 - mousePacket[1];
        MousePosition.x -= mousePacket[1];
        if (xOverflow)
        {
            MousePosition.x -= 255;
        }
    }

    if (!yNegative)
    {
        MousePosition.y -= mousePacket[2];
        if (yOverflow)
        {
            MousePosition.y -= 255;
        }
    } else
    {
        mousePacket[2] = 256 - mousePacket[2];
        MousePosition.y += mousePacket[2];
        if (yOverflow)
        {
            MousePosition.y += 255;
        }
    }

    if (MousePosition.x < 0) MousePosition.x = 0;
    if (MousePosition.x > VGA_WIDTH-1) MousePosition.x = VGA_WIDTH-2;

    if (MousePosition.y < 0) MousePosition.y = 0;
    if (MousePosition.y > VGA_HEIGHT-1) MousePosition.y = VGA_HEIGHT-2;
    //setCursorPos(MousePosition.x, MousePosition.y);

    //struct Box testBox;
    //testBox.colour = 0x01;

    //SetBoxSizeAndPos(testBox, 10, 10, 50, 20);

    graphicsClearScreen(0x3f);
    //DrawBox(testBox);
    drawPalette(MousePosition.x, MousePosition.y);
    while ((inb(0x3DA) & 0x08));
    while (!(inb(0x3DA) & 0x08)); // vsync
}

void parseMouseData(uint8_t data)
{
    switch(mouseCycle){
        case 0:
            if (MousePacketReady) break;
            if (data & 0b00001000 == 0) break;
            mousePacket[0] = data;
            mouseCycle++;
            break;
        case 1:
            if (MousePacketReady) break;
            mousePacket[1] = data;
            mouseCycle++;
            break;
        case 2:
            if (MousePacketReady) break;
            mousePacket[2] = data;
            MousePacketReady = 1;
            mouseCycle = 0;
            break;
    }
}

void mouse_handler(struct regs *r)
{
    uint8_t mouseData = inb(0x60);
    parseMouseData(mouseData);
}

void mouseWait()
{
    uint32_t timeout = 100000;
    while(timeout--)
    {
        if ((inb(0x64) & 0b10) == 0)
        {
            return;
        }
    }
}

void mouseWaitInput()
{
    uint32_t timeout = 100000;
    while(timeout--)
    {
        if (inb(0x64) & 0b1)
        {
            return;
        }
    }
}

void mouseWrite(uint8_t value)
{
    mouseWait();
    outb(0x64, 0xd4);
    mouseWait();
    outb(0x60, value);
}

uint8_t mouseRead()
{
    mouseWaitInput();
    return inb(0x60);
}

void mouse_install()
{
    irq_install_handler(12, mouse_handler);
    outb(0x64, 0xa8);
    mouseWait();
    outb(0x64, 0x20);
    mouseWaitInput();
    uint8_t status = inb(0x60);
    status |= 0b10;
    mouseWait();
    outb(0x64, 0x60);
    mouseWait();
    outb(0x60, status);

    mouseWrite(0xf6);
    mouseRead();

    mouseWrite(0xf4);
    mouseRead();
    
}