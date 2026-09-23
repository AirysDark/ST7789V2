#pragma once

#include <Arduino.h>

class Color
{
public:

    // =====================================================
    // BASIC
    // =====================================================

    static const uint16_t BLACK;
    static const uint16_t WHITE;

    static const uint16_t RED;
    static const uint16_t GREEN;
    static const uint16_t BLUE;

    static const uint16_t CYAN;
    static const uint16_t MAGENTA;
    static const uint16_t YELLOW;

    // =====================================================
    // EXTENDED
    // =====================================================

    static const uint16_t ORANGE;
    static const uint16_t PURPLE;
    static const uint16_t PINK;

    static const uint16_t BROWN;
    static const uint16_t MAROON;

    static const uint16_t NAVY;
    static const uint16_t SKYBLUE;

    static const uint16_t LIME;
    static const uint16_t OLIVE;

    static const uint16_t GOLD;
    static const uint16_t SILVER;

    static const uint16_t GREY;
    static const uint16_t DARKGREY;
    static const uint16_t LIGHTGREY;

    static const uint16_t DARKRED;
    static const uint16_t DARKGREEN;
    static const uint16_t DARKBLUE;

    static const uint16_t TEAL;
    static const uint16_t AQUA;

    static const uint16_t VIOLET;
    static const uint16_t INDIGO;

    static const uint16_t BEIGE;
    static const uint16_t TAN;

    static const uint16_t CORAL;
    static const uint16_t SALMON;

    // =====================================================
    // RGB CONVERSION
    // =====================================================

    static uint16_t rgb565(
        uint8_t r,
        uint8_t g,
        uint8_t b
    );

    static void rgb888(
        uint16_t color,
        uint8_t& r,
        uint8_t& g,
        uint8_t& b
    );

    // =====================================================
    // COLOR EFFECTS
    // =====================================================

    static uint16_t lighten(
        uint16_t color,
        uint8_t amount
    );

    static uint16_t darken(
        uint16_t color,
        uint8_t amount
    );

    static uint16_t blend(
        uint16_t color1,
        uint16_t color2,
        uint8_t percent
    );

    static uint16_t invert(
        uint16_t color
    );

    static uint16_t grayscale(
        uint16_t color
    );

    // =====================================================
    // RANDOM COLORS
    // =====================================================

    static uint16_t randomColor();

    static uint16_t randomBright();

    static uint16_t randomDark();

    // =====================================================
    // 3D ENGINE HELPERS
    // =====================================================

    static uint16_t shade(
        uint16_t color,
        float intensity
    );

    static uint16_t fog(
        uint16_t color,
        uint16_t fogColor,
        float distance
    );

    // =====================================================
    // COMMON UI COLORS
    // =====================================================

    static const uint16_t WINDOW_BG;
    static const uint16_t PANEL_BG;
    static const uint16_t BUTTON_BG;

    static const uint16_t BUTTON_HIGHLIGHT;
    static const uint16_t BUTTON_SHADOW;

    static const uint16_t SUCCESS;
    static const uint16_t WARNING;
    static const uint16_t ERROR;

    static const uint16_t TEXT_PRIMARY;
    static const uint16_t TEXT_SECONDARY;
};