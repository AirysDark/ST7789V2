#include <ESP32S3WatchEngine.h>

float angle = 0.0f;

void setup()
{
    display.begin();

    framebuffer.begin();

    framebuffer.enableZBuffer();
}

void loop()
{
    graphics.clear(
        Color::BLACK
    );

    framebuffer.clearZBuffer();

    renderer3D.setCamera(
        0,
        0,
        -120
    );

    Vec3 pos =
    {
        0,
        0,
        150
    };

    renderer3D.rotateY(
        pos,
        angle
    );

    renderer3D.drawPokeball(
        pos.x,
        pos.y,
        pos.z,
        30
    );

    framebuffer.push();

    angle += 0.02f;

    delay(16);
}