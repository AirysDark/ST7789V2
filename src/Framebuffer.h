#pragma once

#include <Arduino.h>
#include "esp_heap_caps.h"
#include "DisplayDriver.h"

#define FB_WIDTH   280
#define FB_HEIGHT  240

class Framebuffer
{
public:

    // =====================================================
    // MAIN FRAMEBUFFER
    // =====================================================

    uint16_t* buffer = nullptr;

    // =====================================================
    // OPTIONAL BACK BUFFER
    // =====================================================

    uint16_t* backBuffer = nullptr;

    // =====================================================
    // Z BUFFER
    // =====================================================

    float* zBuffer = nullptr;

    // =====================================================
    // INITIALIZATION
    // =====================================================

    bool begin();

    bool enableDoubleBuffer();

    bool enableZBuffer();

    void clearZBuffer(
        float value = 999999.0f
    );

    bool createSpriteBuffer(
        uint16_t** sprite,
        int16_t w,
        int16_t h
    );

    void freeSpriteBuffer(
        uint16_t** sprite
    );

    // =====================================================
    // BUFFER INFO
    // =====================================================

    bool isDoubleBuffered();

    uint16_t* getBuffer();

    uint16_t* getBackBuffer();

    // =====================================================
    // DRAWING
    // =====================================================

    void clear(
        uint16_t color
    );

    void clearBack(
        uint16_t color
    );

    void drawPixel(
        int16_t x,
        int16_t y,
        uint16_t color
    );

    void drawPixelFast(
        int16_t x,
        int16_t y,
        uint16_t color
    );

    void drawPixelBack(
        int16_t x,
        int16_t y,
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
    // BUFFER MANAGEMENT
    // =====================================================

    void swapBuffers();

    // =====================================================
    // DISPLAY PUSH
    // =====================================================

    void push();

    void pushRect(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h
    );

    void pushDirty(
        int16_t oldX,
        int16_t oldY,
        int16_t oldW,
        int16_t oldH,

        int16_t newX,
        int16_t newY,
        int16_t newW,
        int16_t newH
    );
};

extern Framebuffer framebuffer;