ESP32-S3 Watch Graphics Engine

Overview

This project is a custom graphics and 3D rendering engine for the ESP32-S3 platform. It provides a framebuffer-based rendering pipeline with 2D graphics, UI widgets, texture mapping, software 3D rendering, mesh support, and optional Z-buffering.

Target display:

- Resolution: 280x240
- Color Format: RGB565
- Platform: ESP32-S3
- PSRAM Supported

---

Initialization

Display

display.begin();

Initializes the TFT display driver.

---

Touch

touch.begin();

Initializes touch controller.

---

Framebuffer

framebuffer.begin();

Creates the primary framebuffer.

Enable double buffering:

framebuffer.enableDoubleBuffer();

Enable Z-buffer:

framebuffer.enableZBuffer();

Clear framebuffer:

framebuffer.clear(
    Color::BLACK
);

Clear Z-buffer:

framebuffer.clearZBuffer();

Push framebuffer to display:

framebuffer.push();

Swap front/back buffers:

framebuffer.swapBuffers();

---

Graphics Engine

Pixel

graphics.drawPixel(
    x,
    y,
    color
);

Line

graphics.drawLine(
    x1,
    y1,
    x2,
    y2,
    color
);

Rectangle

graphics.drawRect(
    x,
    y,
    width,
    height,
    color
);

Filled rectangle:

graphics.fillRect(
    x,
    y,
    width,
    height,
    color
);

Circle

graphics.drawCircle(
    x,
    y,
    radius,
    color
);

Filled circle:

graphics.fillCircle(
    x,
    y,
    radius,
    color
);

---

Polygon Functions

Filled Triangle

graphics.fillTriangle(
    x1,y1,
    x2,y2,
    x3,y3,
    color
);

Filled Polygon

graphics.fillPolygon(
    xArray,
    yArray,
    pointCount,
    color
);

Textured Triangle

graphics.drawTextureTriangle(
    x1,y1,
    x2,y2,
    x3,y3,
    texture,
    texWidth,
    texHeight
);

Textured Polygon

graphics.drawTexturedPolygon(
    xArray,
    yArray,
    pointCount,
    texture,
    texWidth,
    texHeight
);

---

Texture Functions

Texture Rectangle

graphics.drawTextureRect(
    x,
    y,
    width,
    height,
    texture,
    texWidth,
    texHeight
);

Alpha Blend

uint16_t result =
graphics.alphaBlend(
    color1,
    color2,
    alpha
);

Alpha:

- 0 = color1
- 255 = color2

---

UI Widgets

Panel

graphics.drawPanel(
    x,
    y,
    width,
    height,
    fillColor,
    borderColor,
    shadowColor
);

Button

graphics.drawButton(
    x,
    y,
    width,
    height,
    fillColor,
    textColor
);

Slider

graphics.drawSlider(
    x,
    y,
    width,
    value,
    maxValue,
    fillColor,
    borderColor
);

Progress Bar

graphics.drawProgressBar(
    x,
    y,
    width,
    height,
    value,
    maxValue,
    fillColor,
    borderColor
);

Check Box

graphics.drawCheckBox(
    x,
    y,
    checked,
    borderColor,
    checkColor
);

LED Indicator

graphics.drawLED(
    x,
    y,
    radius,
    state,
    onColor,
    offColor
);

Meter

graphics.drawMeter(
    x,
    y,
    radius,
    value,
    maxValue,
    color
);

Crosshair

graphics.drawCrosshair(
    x,
    y,
    size,
    color
);

---

Text Renderer

Centered text:

renderer.drawTextCentered(
    x,
    y,
    "Hello",
    Color::WHITE,
    scale
);

---

3D Engine

Camera

renderer3D.setCamera(
    x,
    y,
    z
);

---

3D Line

renderer3D.drawLine3D(
    start,
    end,
    color
);

---

Grid

renderer3D.drawGrid(
    size,
    spacing,
    color
);

---

Axis

renderer3D.drawAxis(
    length
);

X = Red

Y = Green

Z = Blue

---

Cube

Wireframe:

renderer3D.drawCube(
    x,
    y,
    z,
    size,
    color
);

Filled:

renderer3D.drawCubeFilled(
    x,
    y,
    z,
    size,
    color
);

---

Sphere

renderer3D.drawSphere(
    x,
    y,
    z,
    radius,
    slices,
    stacks,
    color
);

---

Pokeball

renderer3D.drawPokeball(
    x,
    y,
    z,
    radius
);

---

Mesh Rendering

renderer3D.drawMesh(
    mesh,
    color
);

Mesh format:

struct Mesh3D
{
    Vertex3D* vertices;

    uint16_t vertexCount;

    Face3D* faces;

    uint16_t faceCount;
};

---

Vertex Operations

Rotate:

renderer3D.rotateX(
    vertex,
    angle
);

renderer3D.rotateY(
    vertex,
    angle
);

renderer3D.rotateZ(
    vertex,
    angle
);

Translate:

renderer3D.translate(
    vertex,
    x,
    y,
    z
);

Scale:

renderer3D.scale(
    vertex,
    amount
);

---

Rendering Loop

Typical frame:

graphics.clear(
    Color::BLACK
);

framebuffer.clearZBuffer();

renderScene();

framebuffer.swapBuffers();

framebuffer.push();

---

Current Engine Features

? Framebuffer Rendering

? Double Buffering

? Z Buffer

? RGB565 Color

? UI Widgets

? Texture Mapping

? Alpha Blending

? Polygon Filling

? Textured Polygons

? 3D Wireframe

? 3D Filled Primitives

? Mesh Rendering

? Camera System

? Software Rasterizer

? ESP32-S3 Optimized

? PSRAM Support