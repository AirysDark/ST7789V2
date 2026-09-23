#include "Render.h"
#include <string.h>
#include "Framebuffer.h"
#include "Graphics.h"
#include "Fonts.h"

Renderer renderer;

// =====================================================
// BITMAP
// =====================================================

void Renderer::drawBitmap(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    const uint16_t* bitmap,
    bool transparent,
    uint16_t transparentColor
)
{
    if(bitmap == nullptr)
    {
        return;
    }

    for(int16_t iy = 0; iy < h; iy++)
    {
        for(int16_t ix = 0; ix < w; ix++)
        {
            uint16_t color =
                bitmap[
                    iy * w + ix
                ];

            if(
                transparent &&
                color ==
                transparentColor
            )
            {
                continue;
            }

            graphics.drawPixel(
                x + ix,
                y + iy,
                color
            );
        }
    }
}

// =====================================================
// SCALED BITMAP
// =====================================================

void Renderer::drawBitmapScaled(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    const uint16_t* bitmap,
    uint8_t scale,
    bool transparent,
    uint16_t transparentColor
)
{
    if(bitmap == nullptr)
    {
        return;
    }

    for(int16_t iy = 0; iy < h; iy++)
    {
        for(int16_t ix = 0; ix < w; ix++)
        {
            uint16_t color =
                bitmap[
                    iy * w + ix
                ];

            if(
                transparent &&
                color ==
                transparentColor
            )
            {
                continue;
            }

            graphics.fillRect(
                x + (ix * scale),
                y + (iy * scale),
                scale,
                scale,
                color
            );
        }
    }
}

// =====================================================
// ROTATED BITMAP
// =====================================================

void Renderer::drawBitmapRotated90(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    const uint16_t* bitmap,
    bool transparent,
    uint16_t transparentColor
)
{
    if(bitmap == nullptr)
    {
        return;
    }

    for(int16_t iy = 0; iy < h; iy++)
    {
        for(int16_t ix = 0; ix < w; ix++)
        {
            uint16_t color =
                bitmap[
                    iy * w + ix
                ];

            if(
                transparent &&
                color ==
                transparentColor
            )
            {
                continue;
            }

            graphics.drawPixel(
                x + (h - 1 - iy),
                y + ix,
                color
            );
        }
    }
}

// =====================================================
// SPRITE
// =====================================================

void Renderer::drawSprite(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    const uint16_t* sprite
)
{
    drawBitmap(
        x,
        y,
        w,
        h,
        sprite,
        true,
        Color::BLACK
    );
}

// =====================================================
// ICON
// =====================================================

void Renderer::drawIcon(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    const uint16_t* icon
)
{
    drawBitmap(
        x,
        y,
        w,
        h,
        icon,
        true,
        Color::BLACK
    );
}

// =====================================================
// CHARACTER
// =====================================================

void Renderer::drawChar(
    int16_t x,
    int16_t y,
    char c,
    uint16_t color,
    uint8_t scale
)
{
    if(c < 32 || c > 126)
    {
        return;
    }

    const uint8_t* glyph =
        font5x7[c - 32];

    for(uint8_t col = 0; col < 5; col++)
    {
        uint8_t bits =
            glyph[col];

        for(uint8_t row = 0; row < 7; row++)
        {
            if(bits & (1 << row))
            {
                graphics.fillRect(
                    x + (col * scale),
                    y + (row * scale),
                    scale,
                    scale,
                    color
                );
            }
        }
    }
}

// =====================================================
// TEXT
// =====================================================

void Renderer::drawText(
    int16_t x,
    int16_t y,
    const char* text,
    uint16_t color,
    uint8_t scale
)
{
    while(*text)
    {
        drawChar(
            x,
            y,
            *text,
            color,
            scale
        );

        x +=
            (6 * scale);

        text++;
    }
}

// =====================================================
// ROTATED CHARACTER
// =====================================================

void Renderer::drawCharRotated90(
    int16_t x,
    int16_t y,
    char c,
    uint16_t color,
    uint8_t scale
)
{
    if(c < 32 || c > 126)
    {
        return;
    }

    const uint8_t* glyph =
        font5x7[c - 32];

    for(uint8_t col = 0; col < 5; col++)
    {
        uint8_t bits =
            glyph[col];

        for(uint8_t row = 0; row < 7; row++)
        {
            if(bits & (1 << row))
            {
                graphics.fillRect(
                    x + ((6 - row) * scale),
                    y + (col * scale),
                    scale,
                    scale,
                    color
                );
            }
        }
    }
}

// =====================================================
// ROTATED TEXT
// =====================================================

void Renderer::drawTextRotated90(
    int16_t x,
    int16_t y,
    const char* text,
    uint16_t color,
    uint8_t scale
)
{
    while(*text)
    {
        drawCharRotated90(
            x,
            y,
            *text,
            color,
            scale
        );

        y +=
            (6 * scale);

        text++;
    }
}

// =====================================================
// CENTERED TEXT
// =====================================================

void Renderer::drawTextCentered(
    int16_t centerX,
    int16_t y,
    const char* text,
    uint16_t color,
    uint8_t scale
)
{
    if(text == nullptr)
    {
        return;
    }

    int16_t width =
        strlen(text) *
        6 *
        scale;

    drawText(
        centerX - (width / 2),
        y,
        text,
        color,
        scale
    );
}

// =====================================================
// RIGHT ALIGNED TEXT
// =====================================================

void Renderer::drawTextRight(
    int16_t rightX,
    int16_t y,
    const char* text,
    uint16_t color,
    uint8_t scale
)
{
    if(text == nullptr)
    {
        return;
    }

    int16_t width =
        strlen(text) *
        6 *
        scale;

    drawText(
        rightX - width,
        y,
        text,
        color,
        scale
    );
}

// =====================================================
// TEXT BOX
// =====================================================

void Renderer::drawTextBox(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    const char* text,
    uint16_t textColor,
    uint16_t borderColor,
    uint8_t scale
)
{
    graphics.drawFrame(
        x,
        y,
        w,
        h,
        borderColor
    );

    int16_t textWidth =
        strlen(text) *
        6 *
        scale;

    int16_t textHeight =
        8 *
        scale;

    drawText(
        x + ((w - textWidth) / 2),
        y + ((h - textHeight) / 2),
        text,
        textColor,
        scale
    );
}