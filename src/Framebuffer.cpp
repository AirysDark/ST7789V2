#include "Framebuffer.h"

Framebuffer framebuffer;

// =====================================================
// INIT
// =====================================================

bool Framebuffer::begin()
{
    buffer =
        (uint16_t*)heap_caps_malloc(
            FB_WIDTH *
            FB_HEIGHT *
            sizeof(uint16_t),
            MALLOC_CAP_SPIRAM |
            MALLOC_CAP_8BIT
        );

    if(buffer == nullptr)
    {
        Serial.println(
            "FRAMEBUFFER ALLOC FAILED"
        );

        return false;
    }

    Serial.println(
        "FRAMEBUFFER ALLOC OK"
    );

    clear(0x0000);

    return true;
}

// =====================================================
// DOUBLE BUFFER
// =====================================================

bool Framebuffer::enableDoubleBuffer()
{
    backBuffer =
        (uint16_t*)heap_caps_malloc(
            FB_WIDTH *
            FB_HEIGHT *
            sizeof(uint16_t),
            MALLOC_CAP_SPIRAM |
            MALLOC_CAP_8BIT
        );

    if(backBuffer == nullptr)
    {
        Serial.println(
            "BACKBUFFER FAILED"
        );

        return false;
    }

    Serial.println(
        "BACKBUFFER OK"
    );

    clearBack(0x0000);

    return true;
}

bool Framebuffer::isDoubleBuffered()
{
    return (
        backBuffer != nullptr
    );
}

// =====================================================
// SPRITE BUFFER
// =====================================================

bool Framebuffer::createSpriteBuffer(
    uint16_t** sprite,
    int16_t w,
    int16_t h
)
{
    *sprite =
        (uint16_t*)heap_caps_malloc(
            w *
            h *
            sizeof(uint16_t),
            MALLOC_CAP_SPIRAM |
            MALLOC_CAP_8BIT
        );

    return (*sprite != nullptr);
}

void Framebuffer::freeSpriteBuffer(
    uint16_t** sprite
)
{
    if(*sprite)
    {
        heap_caps_free(
            *sprite
        );

        *sprite = nullptr;
    }
}

// =====================================================
// BUFFER ACCESS
// =====================================================

uint16_t* Framebuffer::getBuffer()
{
    return buffer;
}

uint16_t* Framebuffer::getBackBuffer()
{
    return backBuffer;
}

// =====================================================
// CLEAR
// =====================================================

void Framebuffer::clear(
    uint16_t color
)
{
    uint32_t total =
        FB_WIDTH *
        FB_HEIGHT;

    for(
        uint32_t i = 0;
        i < total;
        i++
    )
    {
        buffer[i] = color;
    }
}

void Framebuffer::clearBack(
    uint16_t color
)
{
    if(backBuffer == nullptr)
    {
        return;
    }

    uint32_t total =
        FB_WIDTH *
        FB_HEIGHT;

    for(
        uint32_t i = 0;
        i < total;
        i++
    )
    {
        backBuffer[i] = color;
    }
}

// =====================================================
// PIXEL
// =====================================================

void Framebuffer::drawPixel(
    int16_t x,
    int16_t y,
    uint16_t color
)
{
    if(x < 0 || y < 0)
    {
        return;
    }

    if(x >= FB_WIDTH)
    {
        return;
    }

    if(y >= FB_HEIGHT)
    {
        return;
    }

    buffer[
        y * FB_WIDTH + x
    ] = color;
}

void Framebuffer::drawPixelFast(
    int16_t x,
    int16_t y,
    uint16_t color
)
{
    buffer[
        y * FB_WIDTH + x
    ] = color;
}

void Framebuffer::drawPixelBack(
    int16_t x,
    int16_t y,
    uint16_t color
)
{
    if(backBuffer == nullptr)
    {
        return;
    }

    if(x < 0 || y < 0)
    {
        return;
    }

    if(x >= FB_WIDTH)
    {
        return;
    }

    if(y >= FB_HEIGHT)
    {
        return;
    }

    backBuffer[
        y * FB_WIDTH + x
    ] = color;
}

// =====================================================
// RECT
// =====================================================

void Framebuffer::fillRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t color
)
{
    if(w <= 0 || h <= 0)
    {
        return;
    }

    for(
        int16_t iy = 0;
        iy < h;
        iy++
    )
    {
        for(
            int16_t ix = 0;
            ix < w;
            ix++
        )
        {
            drawPixel(
                x + ix,
                y + iy,
                color
            );
        }
    }
}

// =====================================================
// SWAP BUFFERS
// =====================================================

void Framebuffer::swapBuffers()
{
    if(backBuffer == nullptr)
    {
        return;
    }

    uint16_t* temp =
        buffer;

    buffer =
        backBuffer;

    backBuffer =
        temp;
}

// =====================================================
// FULL PUSH
// =====================================================

void Framebuffer::push()
{
    pushRect(
        0,
        0,
        FB_WIDTH,
        FB_HEIGHT
    );
}

// =====================================================
// PARTIAL PUSH
// =====================================================

void Framebuffer::pushRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h
)
{
    if(w <= 0 || h <= 0)
    {
        return;
    }

    if(x < 0)
    {
        w += x;
        x = 0;
    }

    if(y < 0)
    {
        h += y;
        y = 0;
    }

    if((x + w) > FB_WIDTH)
    {
        w = FB_WIDTH - x;
    }

    if((y + h) > FB_HEIGHT)
    {
        h = FB_HEIGHT - y;
    }

    display.setFramebufferWindow(
        x,
        y,
        x + w - 1,
        y + h - 1
    );

    display.startFramebufferWrite();

    for(
        int16_t iy = 0;
        iy < h;
        iy++
    )
    {
        uint16_t* row =
            &buffer[
                (y + iy) *
                FB_WIDTH +
                x
            ];

        for(
            int16_t ix = 0;
            ix < w;
            ix++
        )
        {
            uint16_t color =
                row[ix];

            display.spi.transfer(
                color >> 8
            );

            display.spi.transfer(
                color & 0xFF
            );
        }
    }

    display.endFramebufferWrite();
}

// =====================================================
// DIRTY RECT
// =====================================================

void Framebuffer::pushDirty(
    int16_t oldX,
    int16_t oldY,
    int16_t oldW,
    int16_t oldH,

    int16_t newX,
    int16_t newY,
    int16_t newW,
    int16_t newH
)
{
    int16_t minX =
        min(
            oldX,
            newX
        );

    int16_t minY =
        min(
            oldY,
            newY
        );

    int16_t maxX =
        max(
            oldX + oldW,
            newX + newW
        );

    int16_t maxY =
        max(
            oldY + oldH,
            newY + newH
        );

    if(minX < 0)
    {
        minX = 0;
    }

    if(minY < 0)
    {
        minY = 0;
    }

    if(maxX > FB_WIDTH)
    {
        maxX = FB_WIDTH;
    }

    if(maxY > FB_HEIGHT)
    {
        maxY = FB_HEIGHT;
    }

    pushRect(
        minX,
        minY,
        maxX - minX,
        maxY - minY
    );
}

bool Framebuffer::enableZBuffer()
{
    zBuffer =
        (float*)heap_caps_malloc(
            FB_WIDTH *
            FB_HEIGHT *
            sizeof(float),
            MALLOC_CAP_SPIRAM |
            MALLOC_CAP_8BIT
        );

    if(!zBuffer)
    {
        return false;
    }

    clearZBuffer();

    return true;
}

void Framebuffer::clearZBuffer(
    float value
)
{
    if(!zBuffer)
    {
        return;
    }

    uint32_t total =
        FB_WIDTH *
        FB_HEIGHT;

    for(uint32_t i = 0;
        i < total;
        i++)
    {
        zBuffer[i] = value;
    }
}