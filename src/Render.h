#pragma once

#include <Arduino.h>

#include "Color.h"

class Renderer
{
public:

    // =====================================================
    // BITMAPS
    // =====================================================

    void drawBitmap(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        const uint16_t* bitmap,
        bool transparent = false,
        uint16_t transparentColor = Color::BLACK
    );

    void drawBitmapScaled(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        const uint16_t* bitmap,
        uint8_t scale,
        bool transparent = false,
        uint16_t transparentColor = Color::BLACK
    );

    void drawBitmapRotated90(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        const uint16_t* bitmap,
        bool transparent = false,
        uint16_t transparentColor = Color::BLACK
    );

    // =====================================================
    // SPRITES
    // =====================================================

    void drawSprite(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        const uint16_t* sprite
    );

    // =====================================================
    // ICONS
    // =====================================================

    void drawIcon(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        const uint16_t* icon
    );

    // =====================================================
    // TEXT
    // =====================================================

    void drawChar(
        int16_t x,
        int16_t y,
        char c,
        uint16_t color = Color::WHITE,
        uint8_t scale = 1
    );

    void drawText(
        int16_t x,
        int16_t y,
        const char* text,
        uint16_t color = Color::WHITE,
        uint8_t scale = 1
    );

    // =====================================================
    // TEXT HELPERS
    // =====================================================

    void drawTextCentered(
        int16_t centerX,
        int16_t y,
        const char* text,
        uint16_t color = Color::WHITE,
        uint8_t scale = 1
    );

    void drawTextRight(
        int16_t rightX,
        int16_t y,
        const char* text,
        uint16_t color = Color::WHITE,
        uint8_t scale = 1
    );

    void drawTextBox(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        const char* text,
        uint16_t textColor = Color::WHITE,
        uint16_t borderColor = Color::WHITE,
        uint8_t scale = 1
    );

    // =====================================================
    // ROTATED TEXT
    // =====================================================

    void drawCharRotated90(
        int16_t x,
        int16_t y,
        char c,
        uint16_t color = Color::WHITE,
        uint8_t scale = 1
    );

    void drawTextRotated90(
        int16_t x,
        int16_t y,
        const char* text,
        uint16_t color = Color::WHITE,
        uint8_t scale = 1
    );
};

extern Renderer renderer;