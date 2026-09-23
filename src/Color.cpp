#include "Color.h"

// =====================================================
// BASIC
// =====================================================

const uint16_t Color::BLACK     = 0x0000;
const uint16_t Color::WHITE     = 0xFFFF;

const uint16_t Color::RED       = 0xF800;
const uint16_t Color::GREEN     = 0x07E0;
const uint16_t Color::BLUE      = 0x001F;

const uint16_t Color::CYAN      = 0x07FF;
const uint16_t Color::MAGENTA   = 0xF81F;
const uint16_t Color::YELLOW    = 0xFFE0;

// =====================================================
// EXTENDED
// =====================================================

const uint16_t Color::ORANGE    = 0xFD20;
const uint16_t Color::PURPLE    = 0x8010;
const uint16_t Color::PINK      = 0xF81F;

const uint16_t Color::BROWN     = 0xA145;
const uint16_t Color::MAROON    = 0x8000;

const uint16_t Color::NAVY      = 0x000F;
const uint16_t Color::SKYBLUE   = 0x867D;

const uint16_t Color::LIME      = 0x87E0;
const uint16_t Color::OLIVE     = 0x8400;

const uint16_t Color::GOLD      = 0xFEA0;
const uint16_t Color::SILVER    = 0xC618;

const uint16_t Color::GREY      = 0x8410;
const uint16_t Color::DARKGREY  = 0x4208;
const uint16_t Color::LIGHTGREY = 0xCE79;

const uint16_t Color::DARKRED   = 0x8800;
const uint16_t Color::DARKGREEN = 0x0320;
const uint16_t Color::DARKBLUE  = 0x0010;

const uint16_t Color::TEAL      = 0x0410;
const uint16_t Color::AQUA      = 0x07FF;

const uint16_t Color::VIOLET    = 0x915C;
const uint16_t Color::INDIGO    = 0x4810;

const uint16_t Color::BEIGE     = 0xF7BB;
const uint16_t Color::TAN       = 0xD5B1;

const uint16_t Color::CORAL     = 0xFBEA;
const uint16_t Color::SALMON    = 0xFC0E;

// =====================================================
// UI COLORS
// =====================================================

const uint16_t Color::WINDOW_BG        = 0x2104;
const uint16_t Color::PANEL_BG         = 0x3186;
const uint16_t Color::BUTTON_BG        = 0x4208;

const uint16_t Color::BUTTON_HIGHLIGHT = 0xFFFF;
const uint16_t Color::BUTTON_SHADOW    = 0x0000;

const uint16_t Color::SUCCESS          = 0x07E0;
const uint16_t Color::WARNING          = 0xFFE0;
const uint16_t Color::ERROR            = 0xF800;

const uint16_t Color::TEXT_PRIMARY     = 0xFFFF;
const uint16_t Color::TEXT_SECONDARY   = 0xBDF7;

// =====================================================
// RGB888 -> RGB565
// =====================================================

uint16_t Color::rgb565(
    uint8_t r,
    uint8_t g,
    uint8_t b
)
{
    return
        ((r & 0xF8) << 8) |
        ((g & 0xFC) << 3) |
        (b >> 3);
}

// =====================================================
// RGB565 -> RGB888
// =====================================================

void Color::rgb888(
    uint16_t color,
    uint8_t& r,
    uint8_t& g,
    uint8_t& b
)
{
    r =
        ((color >> 11) & 0x1F) << 3;

    g =
        ((color >> 5) & 0x3F) << 2;

    b =
        (color & 0x1F) << 3;
}

// =====================================================
// LIGHTEN
// =====================================================

uint16_t Color::lighten(
    uint16_t color,
    uint8_t amount
)
{
    uint8_t r,g,b;

    rgb888(color,r,g,b);

    r = min(255, r + amount);
    g = min(255, g + amount);
    b = min(255, b + amount);

    return rgb565(r,g,b);
}

// =====================================================
// DARKEN
// =====================================================

uint16_t Color::darken(
    uint16_t color,
    uint8_t amount
)
{
    uint8_t r,g,b;

    rgb888(color,r,g,b);

    r = (r > amount) ? r - amount : 0;
    g = (g > amount) ? g - amount : 0;
    b = (b > amount) ? b - amount : 0;

    return rgb565(r,g,b);
}

// =====================================================
// BLEND
// =====================================================

uint16_t Color::blend(
    uint16_t color1,
    uint16_t color2,
    uint8_t percent
)
{
    if(percent > 100)
    {
        percent = 100;
    }

    uint8_t r1,g1,b1;
    uint8_t r2,g2,b2;

    rgb888(color1,r1,g1,b1);
    rgb888(color2,r2,g2,b2);

    uint8_t r =
        (r1 * (100 - percent) +
         r2 * percent) / 100;

    uint8_t g =
        (g1 * (100 - percent) +
         g2 * percent) / 100;

    uint8_t b =
        (b1 * (100 - percent) +
         b2 * percent) / 100;

    return rgb565(r,g,b);
}

// =====================================================
// INVERT
// =====================================================

uint16_t Color::invert(
    uint16_t color
)
{
    uint8_t r,g,b;

    rgb888(color,r,g,b);

    return rgb565(
        255 - r,
        255 - g,
        255 - b
    );
}

// =====================================================
// GRAYSCALE
// =====================================================

uint16_t Color::grayscale(
    uint16_t color
)
{
    uint8_t r,g,b;

    rgb888(color,r,g,b);

    uint8_t gray =
        (r + g + b) / 3;

    return rgb565(
        gray,
        gray,
        gray
    );
}

// =====================================================
// RANDOM COLORS
// =====================================================

uint16_t Color::randomColor()
{
    return rgb565(
        random(256),
        random(256),
        random(256)
    );
}

uint16_t Color::randomBright()
{
    return rgb565(
        random(128,256),
        random(128,256),
        random(128,256)
    );
}

uint16_t Color::randomDark()
{
    return rgb565(
        random(128),
        random(128),
        random(128)
    );
}

// =====================================================
// SHADE
// =====================================================

uint16_t Color::shade(
    uint16_t color,
    float intensity
)
{
    uint8_t r,g,b;

    rgb888(color,r,g,b);

    r = (uint8_t)(r * intensity);
    g = (uint8_t)(g * intensity);
    b = (uint8_t)(b * intensity);

    return rgb565(
        r,
        g,
        b
    );
}

// =====================================================
// FOG
// =====================================================

uint16_t Color::fog(
    uint16_t color,
    uint16_t fogColor,
    float distance
)
{
    if(distance < 0.0f)
    {
        distance = 0.0f;
    }

    if(distance > 1.0f)
    {
        distance = 1.0f;
    }

    return blend(
        color,
        fogColor,
        (uint8_t)(distance * 100.0f)
    );
}