#pragma once

#include <Arduino.h>

class Graphics
{
public:

    // =====================================================
    // SCREEN
    // =====================================================

    void clear(uint16_t color);

    // =====================================================
    // PIXELS
    // =====================================================

    void drawPixel(
        int16_t x,
        int16_t y,
        uint16_t color
    );

    // =====================================================
    // LINES
    // =====================================================

    void drawLine(
        int16_t x0,
        int16_t y0,
        int16_t x1,
        int16_t y1,
        uint16_t color
    );

    // =====================================================
    // RECTANGLES
    // =====================================================

    void drawRect(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t color
    );

    void fillRect(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t color
    );

    // =====================================================
    // CIRCLES
    // =====================================================

    void drawCircle(
        int16_t x0,
        int16_t y0,
        int16_t radius,
        uint16_t color
    );

    void fillCircle(
        int16_t x0,
        int16_t y0,
        int16_t radius,
        uint16_t color
    );

    // =====================================================
    // ELLIPSES
    // =====================================================

    void drawEllipse(
        int16_t x0,
        int16_t y0,
        int16_t rx,
        int16_t ry,
        uint16_t color
    );

    void fillEllipse(
        int16_t x0,
        int16_t y0,
        int16_t rx,
        int16_t ry,
        uint16_t color
    );

    // =====================================================
    // ARCS
    // =====================================================

    void drawArc(
        int16_t x0,
        int16_t y0,
        int16_t radius,
        float startAngle,
        float endAngle,
        uint16_t color
    );

    // =====================================================
    // TRIANGLES
    // =====================================================

    void drawTriangle(
        int16_t x1,
        int16_t y1,
        int16_t x2,
        int16_t y2,
        int16_t x3,
        int16_t y3,
        uint16_t color
    );

    void fillTriangle(
        int16_t x1,
        int16_t y1,
        int16_t x2,
        int16_t y2,
        int16_t x3,
        int16_t y3,
        uint16_t color
    );

    // =====================================================
    // POLYGONS
    // =====================================================

    void drawPolygon(
        const int16_t* px,
        const int16_t* py,
        uint8_t count,
        uint16_t color
    );

    void fillPolygon(
        const int16_t* px,
        const int16_t* py,
        uint8_t count,
        uint16_t color
    );

    // =====================================================
    // ROUNDED RECTANGLES
    // =====================================================

    void drawRoundRect(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        int16_t radius,
        uint16_t color
    );

    void fillRoundRect(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        int16_t radius,
        uint16_t color
    );

    // =====================================================
    // GRADIENTS
    // =====================================================

    void drawGradientRect(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t colorTop,
        uint16_t colorBottom
    );

    // =====================================================
    // PANELS
    // =====================================================

    void drawPanel(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t fillColor,
        uint16_t lightColor,
        uint16_t darkColor
    );

    // =====================================================
    // GRID
    // =====================================================

    void drawGrid(
        int16_t spacing,
        uint16_t color
    );

    // =====================================================
    // CROSSHAIR
    // =====================================================

    void drawCrosshair(
        int16_t x,
        int16_t y,
        int16_t size,
        uint16_t color
    );

    // =====================================================
    // UI
    // =====================================================

    void drawFrame(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t color
    );

    void drawWindow(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t fillColor,
        uint16_t borderColor
    );

    void drawButton(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t fillColor,
        uint16_t borderColor
    );

    void drawPressedButton(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t fillColor,
        uint16_t borderColor
    );

    void drawBevelButton(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        bool pressed,
        uint16_t fillColor,
        uint16_t lightColor,
        uint16_t darkColor
    );

    void drawCheckBox(
        int16_t x,
        int16_t y,
        bool checked,
        uint16_t borderColor,
        uint16_t checkColor
    );

    void drawSlider(
        int16_t x,
        int16_t y,
        int16_t w,
        uint16_t value,
        uint16_t maxValue,
        uint16_t fillColor,
        uint16_t borderColor
    );

    void drawTab(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        bool active,
        uint16_t fillColor,
        uint16_t borderColor
    );

    void drawProgressBar(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        uint16_t value,
        uint16_t maxValue,
        uint16_t fillColor,
        uint16_t borderColor
    );

// =====================================================
// STATUS / INDICATORS
// =====================================================

void drawLED(
    int16_t x,
    int16_t y,
    int16_t radius,
    bool on,
    uint16_t onColor,
    uint16_t offColor
);

void drawMeter(
    int16_t x,
    int16_t y,
    int16_t radius,
    uint16_t value,
    uint16_t maxValue,
    uint16_t color
);

// =====================================================
// IMAGES
// =====================================================

void drawImage(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    const uint16_t* image
);

void drawSprite(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    const uint16_t* sprite,
    uint16_t transparentColor
);

// =====================================================
// COLOR BLENDING
// =====================================================

uint16_t alphaBlend(
    uint16_t src,
    uint16_t dst,
    uint8_t alpha
);

// =====================================================
// TEXTURES
// =====================================================

void drawTextureRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    const uint16_t* texture,
    int16_t texW,
    int16_t texH
);

void drawTextureTriangle(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    int16_t x3,
    int16_t y3,
    const uint16_t* texture,
    int16_t texW,
    int16_t texH
);

void drawTexturedPolygon(
    const int16_t* px,
    const int16_t* py,
    uint8_t count,
    const uint16_t* texture,
    int16_t texW,
    int16_t texH
);

}; // class Graphics

extern Graphics graphics;