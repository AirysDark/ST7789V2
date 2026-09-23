#include <ESP32S3WatchEngine.h>

uint16_t texture[16 * 16];

void setup()
{
    display.begin();

    framebuffer.begin();

    for(int y = 0; y < 16; y++)
    {
        for(int x = 0; x < 16; x++)
        {
            texture[y * 16 + x] =
                ((x + y) & 1)
                ? Color::WHITE
                : Color::RED;
        }
    }

    graphics.clear(
        Color::BLACK
    );

    graphics.drawTextureRect(
        40,
        40,
        200,
        160,
        texture,
        16,
        16
    );

    framebuffer.push();
}

void loop()
{
}