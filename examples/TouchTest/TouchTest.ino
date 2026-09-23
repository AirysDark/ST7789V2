#include <ESP32S3WatchEngine.h>

void setup()
{
    Serial.begin(115200);

    display.begin();

    framebuffer.begin();

    touch.begin();
}

void loop()
{
    TouchPoint p;

    if(touch.getPoint(p))
    {
        graphics.fillCircle(
            p.x,
            p.y,
            4,
            Color::GREEN
        );

        framebuffer.push();
    }
}