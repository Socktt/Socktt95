#define DEFAULT_WINDOW_COLOUR 0x01;

struct Box
{
    struct Point tl;
    struct Point tr;
    struct Point bl;
    struct Point br;
    uint8_t colour;
};

void SetBoxSizeAndPos(struct Box box, uint8_t posX, uint8_t posY, uint8_t sizeX, uint8_t sizeY);
void DrawBox(struct Box box);