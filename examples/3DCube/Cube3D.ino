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
        120
    };

    renderer3D.rotateY(
        pos,
        angle
    );

    renderer3D.drawCubeFilled(
        pos.x,
        pos.y,
        pos.z,
        40,
        Color::CYAN
    );

    renderer3D.drawCube(
        pos.x,
        pos.y,
        pos.z,
        40,
        Color::WHITE
    );

    framebuffer.push();

    angle += 0.03f;

    delay(16);
}