#include <ESP32S3WatchEngine.h>

void setup()
{
    display.begin();

    framebuffer.begin();

    graphics.clear(Color::BLACK);

    graphics.drawRect(
        20,
        20,
        100,
        60,
        Color::WHITE
    );

    graphics.fillRect(
        140,
        20,
        100,
        60,
        Color::BLUE
    );

    graphics.drawCircle(
        70,
        140,
        40,
        Color::GREEN
    );

    graphics.fillCircle(
        210,
        140,
        40,
        Color::RED
    );

    framebuffer.push();
}

void loop()
{
}