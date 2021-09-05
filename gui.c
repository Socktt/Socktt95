#include "typeDef.h"
#include "vga.h"
#include "system.h"
#include "math.h"
#include "gui.h"

void SetBoxSizeAndPos(struct Box box, uint8_t posX, uint8_t posY, uint8_t sizeX, uint8_t sizeY)
{
    box.tl.x = posX;
    box.tl.y = posY;
    box.tr.x = box.tl.x + sizeX;
    box.tr.y = box.tl.y;
    box.bl.x = posX;
    box.bl.y = posY + sizeY;
    box.br.x = posX + sizeX;
    box.br.y = posY + sizeY;
    return;
}

void DrawBox(struct Box box)
{
    uint8_t drawX = box.tl.x;
    uint8_t drawY = box.tl.y;
    for (drawX; drawX<box.tr.x;drawX++)
    {
        drawPixel(drawX, drawY, box.colour);
    }
    return;
}