# ST7789V2 — ESP32-S3-LCD-1.69 Graphics Engine

A framebuffer-based 2D/3D graphics engine for the **ESP32-S3-LCD-1.69 Touch Screen Version**.

## Arduino core requirement

**Target and compatibility baseline: Arduino-ESP32 Core 2.0.17.**

Development, testing and optimization of this repository must preserve compatibility with **Espressif Arduino-ESP32 2.0.17**. Do not assume APIs, SPI behavior, memory APIs, build flags or features introduced only in Arduino-ESP32 3.x.

## Target hardware

- MCU: ESP32-S3R8, dual-core Xtensa LX7 up to 240 MHz
- Memory: 8 MB PSRAM, 16 MB flash
- Display: 1.69-inch IPS, 240 x 280, RGB565 / 262K colour
- LCD controller: ST7789V2 over SPI
- Touch controller: CST816 over I2C
- IMU: QMI8658 6-axis accelerometer/gyroscope
- RTC: PCF85063
- Battery: 3.7 V lithium battery connector with ETA6098 charging circuitry
- Wireless: 2.4 GHz Wi-Fi and Bluetooth 5 LE
- USB: USB-C
- Other onboard hardware: buzzer, BOOT, RST and programmable power/function button

> This library currently implements the display, CST816 touch, framebuffer, 2D graphics and software 3D engine. The onboard QMI8658, PCF85063, battery/power functions and buzzer are hardware capabilities of the target board; dedicated high-level drivers for all of them are not yet part of this library.

## Current board pin configuration

### ST7789V2 display

| Function | GPIO |
|---|---:|
| TFT CS | 5 |
| TFT DC | 4 |
| TFT RST | 8 |
| TFT BL | 15 |
| TFT SCLK | 6 |
| TFT MOSI | 7 |

Display dimensions used by the engine are **280 x 240** in landscape orientation, with an X offset of 20 pixels.

### CST816 touch

| Function | GPIO |
|---|---:|
| SDA | 11 |
| SCL | 10 |
| RST | 13 |
| INT | 14 |
| I2C address | 0x15 |

The touch driver maps the controller's measured coordinates into the engine's 280 x 240 landscape coordinate system.

### Exposed expansion pins

The board listing identifies GPIO18, GPIO17, GPIO16, GPIO3, GPIO2, SDA/GPIO11, SCL/GPIO10, UART TX/RX, 3.3 V, GND and 5 V on the expansion header. Verify the exact header order against the silkscreen for your board revision before wiring external hardware.

## Engine architecture

```text
ESP32-S3 application
        |
ESP32S3WatchEngine.h
        |
        +-- DisplayDriver ---- ST7789V2 / SPI
        +-- TouchDriver ------ CST816 / I2C
        +-- Framebuffer ------ PSRAM, double buffer, Z-buffer
        +-- Graphics --------- 2D primitives, polygons, textures, widgets
        +-- Renderer --------- bitmap/font/text rendering
        +-- Renderer3D ------- software 3D, meshes and primitives
        +-- Color ------------ RGB565 colour utilities
```

## Initialization

```cpp
#include <ESP32S3WatchEngine.h>

void setup()
{
    Serial.begin(115200);

    display.begin();
    touch.begin();

    if (!framebuffer.begin())
        return;

    framebuffer.enableDoubleBuffer();
    framebuffer.enableZBuffer();
}

void loop()
{
    graphics.clear(Color::BLACK);
    framebuffer.clearZBuffer();

    // Draw scene here.

    framebuffer.swapBuffers();
    framebuffer.push();
}
```

Double buffering and the Z-buffer are optional. Both consume additional PSRAM.

## Framebuffer

```cpp
framebuffer.begin();
framebuffer.enableDoubleBuffer();
framebuffer.enableZBuffer();

framebuffer.clear(Color::BLACK);
framebuffer.clearZBuffer();

framebuffer.push();
framebuffer.pushRect(x, y, w, h);
framebuffer.swapBuffers();
```

A full RGB565 framebuffer is 280 x 240 x 2 = **134,400 bytes**. A second colour buffer requires another 134,400 bytes. The float Z-buffer requires 268,800 bytes.

## 2D graphics

Supported operations include pixels, lines, rectangles, circles, ellipses, arcs, triangles, filled polygons, textured primitives, alpha blending and UI-style widgets.

```cpp
graphics.drawPixel(x, y, Color::WHITE);
graphics.drawLine(x1, y1, x2, y2, Color::RED);
graphics.drawRect(x, y, w, h, Color::GREEN);
graphics.fillRect(x, y, w, h, Color::BLUE);
graphics.drawCircle(x, y, radius, Color::WHITE);
graphics.fillCircle(x, y, radius, Color::CYAN);
```

## Text

The built-in renderer uses the bundled 5x7 bitmap font.

```cpp
renderer.drawText(10, 10, "Hello", Color::WHITE, 1);
renderer.drawTextCentered(140, 20, "ST7789V2", Color::WHITE, 2);
renderer.drawTextRight(275, 40, "ESP32-S3", Color::GREEN, 1);
```

## 3D engine

The software renderer provides camera projection, wireframe and filled geometry, meshes, textured triangles, cubes, spheres, axes and grids.

```cpp
renderer3D.setCamera(0, 0, -100);
renderer3D.drawCube(0, 0, 20, 30, Color::WHITE);
renderer3D.drawCubeFilled(0, 0, 20, 30, Color::BLUE);
renderer3D.drawSphere(0, 0, 20, 20, 16, 12, Color::WHITE);
```

## Touch

```cpp
if (touch.update())
{
    uint16_t x = touch.getX();
    uint16_t y = touch.getY();
}
```

The driver polls at a maximum rate of approximately 100 Hz and uses the CST816 interrupt line to avoid unnecessary I2C reads.

## Examples

- `BasicGraphics`
- `3DCube`
- `FullEngineDemo`
- `PokeBallDemo`
- `TextureDemo`
- `TouchTest`

## Performance notes

The engine renders into PSRAM-backed RGB565 buffers and then transfers the requested region to the ST7789V2. Use `pushRect()` or `pushDirty()` when only part of the screen changed. Avoid enabling the second framebuffer or Z-buffer unless the application needs them.

Version 1.1 adds safer clipping and faster framebuffer rectangle fills, and fixes sphere tessellation so the requested slice/stack counts are actually used.

## Version

**1.1.0**
