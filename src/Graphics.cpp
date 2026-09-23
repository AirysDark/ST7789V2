#include "Graphics.h"
#include "Framebuffer.h"
#include "Color.h"
#include <math.h>

Graphics graphics;

// =====================================================
// SCREEN
// =====================================================

void Graphics::clear(uint16_t color)
{
    framebuffer.clear(color);
}

// =====================================================
// PIXELS
// =====================================================

void Graphics::drawPixel(
    int16_t x,
    int16_t y,
    uint16_t color
)
{
    framebuffer.drawPixel(
        x,
        y,
        color
    );
}

// =====================================================
// FILLED RECTANGLE
// =====================================================

void Graphics::fillRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t color
)
{
    framebuffer.fillRect(
        x,
        y,
        w,
        h,
        color
    );
}

// =====================================================
// LINE
// =====================================================

void Graphics::drawLine(
    int16_t x0,
    int16_t y0,
    int16_t x1,
    int16_t y1,
    uint16_t color
)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;

    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;

    int err = dx + dy;

    while(true)
    {
        drawPixel(
            x0,
            y0,
            color
        );

        if(x0 == x1 &&
           y0 == y1)
        {
            break;
        }

        int e2 = 2 * err;

        if(e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }

        if(e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

// =====================================================
// RECTANGLE
// =====================================================

void Graphics::drawRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t color
)
{
    drawLine(
        x,
        y,
        x + w - 1,
        y,
        color
    );

    drawLine(
        x,
        y,
        x,
        y + h - 1,
        color
    );

    drawLine(
        x + w - 1,
        y,
        x + w - 1,
        y + h - 1,
        color
    );

    drawLine(
        x,
        y + h - 1,
        x + w - 1,
        y + h - 1,
        color
    );
}

// =====================================================
// CIRCLE
// =====================================================

void Graphics::drawCircle(
    int16_t x0,
    int16_t y0,
    int16_t radius,
    uint16_t color
)
{
    int16_t x = radius;
    int16_t y = 0;
    int16_t err = 0;

    while(x >= y)
    {
        drawPixel(x0 + x, y0 + y, color);
        drawPixel(x0 + y, y0 + x, color);
        drawPixel(x0 - y, y0 + x, color);
        drawPixel(x0 - x, y0 + y, color);

        drawPixel(x0 - x, y0 - y, color);
        drawPixel(x0 - y, y0 - x, color);
        drawPixel(x0 + y, y0 - x, color);
        drawPixel(x0 + x, y0 - y, color);

        y++;

        if(err <= 0)
        {
            err += 2 * y + 1;
        }

        if(err > 0)
        {
            x--;
            err -= 2 * x + 1;
        }
    }
}

// =====================================================
// FILLED CIRCLE
// =====================================================

void Graphics::fillCircle(
    int16_t x0,
    int16_t y0,
    int16_t radius,
    uint16_t color
)
{
    for(int16_t y = -radius; y <= radius; y++)
    {
        for(int16_t x = -radius; x <= radius; x++)
        {
            if((x * x + y * y) <=
               (radius * radius))
            {
                drawPixel(
                    x0 + x,
                    y0 + y,
                    color
                );
            }
        }
    }
}

// =====================================================
// ROUND RECTANGLE
// =====================================================

void Graphics::drawRoundRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    int16_t radius,
    uint16_t color
)
{
    // Top
    drawLine(
        x + radius,
        y,
        x + w - radius - 1,
        y,
        color
    );

    // Bottom
    drawLine(
        x + radius,
        y + h - 1,
        x + w - radius - 1,
        y + h - 1,
        color
    );

    // Left
    drawLine(
        x,
        y + radius,
        x,
        y + h - radius - 1,
        color
    );

    // Right
    drawLine(
        x + w - 1,
        y + radius,
        x + w - 1,
        y + h - radius - 1,
        color
    );

    // Corners

    for(int16_t yy = -radius; yy <= radius; yy++)
    {
        for(int16_t xx = -radius; xx <= radius; xx++)
        {
            int32_t d =
                (xx * xx) +
                (yy * yy);

            if(
                d >= (radius - 1) * (radius - 1) &&
                d <= radius * radius
            )
            {
                drawPixel(
                    x + radius + xx,
                    y + radius + yy,
                    color
                );

                drawPixel(
                    x + w - radius - 1 + xx,
                    y + radius + yy,
                    color
                );

                drawPixel(
                    x + radius + xx,
                    y + h - radius - 1 + yy,
                    color
                );

                drawPixel(
                    x + w - radius - 1 + xx,
                    y + h - radius - 1 + yy,
                    color
                );
            }
        }
    }
}

// =====================================================
// FILLED ROUND RECTANGLE
// =====================================================

void Graphics::fillRoundRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    int16_t radius,
    uint16_t color
)
{
    fillRect(
        x + radius,
        y,
        w - (radius * 2),
        h,
        color
    );

    fillRect(
        x,
        y + radius,
        radius,
        h - (radius * 2),
        color
    );

    fillRect(
        x + w - radius,
        y + radius,
        radius,
        h - (radius * 2),
        color
    );

    fillCircle(
        x + radius,
        y + radius,
        radius,
        color
    );

    fillCircle(
        x + w - radius - 1,
        y + radius,
        radius,
        color
    );

    fillCircle(
        x + radius,
        y + h - radius - 1,
        radius,
        color
    );

    fillCircle(
        x + w - radius - 1,
        y + h - radius - 1,
        radius,
        color
    );
}

// =====================================================
// TRIANGLE
// =====================================================

void Graphics::drawTriangle(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    int16_t x3,
    int16_t y3,
    uint16_t color
)
{
    drawLine(
        x1,
        y1,
        x2,
        y2,
        color
    );

    drawLine(
        x2,
        y2,
        x3,
        y3,
        color
    );

    drawLine(
        x3,
        y3,
        x1,
        y1,
        color
    );
}

// =====================================================
// FRAME
// =====================================================

void Graphics::drawFrame(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t color
)
{
    drawRect(
        x,
        y,
        w,
        h,
        color
    );
}

// =====================================================
// WINDOW
// =====================================================

void Graphics::drawWindow(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t fillColor,
    uint16_t borderColor
)
{
    fillRect(
        x,
        y,
        w,
        h,
        fillColor
    );

    drawRect(
        x,
        y,
        w,
        h,
        borderColor
    );
}

// =====================================================
// BUTTON
// =====================================================

void Graphics::drawButton(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t fillColor,
    uint16_t borderColor
)
{
    fillRect(
        x,
        y,
        w,
        h,
        fillColor
    );

    drawRect(
        x,
        y,
        w,
        h,
        borderColor
    );
}

// =====================================================
// PRESSED BUTTON
// =====================================================

void Graphics::drawPressedButton(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t fillColor,
    uint16_t borderColor
)
{
    fillRect(
        x + 1,
        y + 1,
        w - 1,
        h - 1,
        fillColor
    );

    drawRect(
        x + 1,
        y + 1,
        w - 1,
        h - 1,
        borderColor
    );
}

// =====================================================
// PROGRESS BAR
// =====================================================

void Graphics::drawProgressBar(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t value,
    uint16_t maxValue,
    uint16_t fillColor,
    uint16_t borderColor
)
{
    drawRect(
        x,
        y,
        w,
        h,
        borderColor
    );

    int fillWidth =
        ((w - 2) * value) /
        maxValue;

    fillRect(
        x + 1,
        y + 1,
        fillWidth,
        h - 2,
        fillColor
    );
}

// =====================================================
// ELLIPSE
// =====================================================

void Graphics::drawEllipse(
    int16_t x0,
    int16_t y0,
    int16_t rx,
    int16_t ry,
    uint16_t color
)
{
    for(float a = 0; a < 360; a += 1.0f)
    {
        float r = a * 0.0174532925f;

        drawPixel(
            x0 + (int16_t)(cos(r) * rx),
            y0 + (int16_t)(sin(r) * ry),
            color
        );
    }
}

void Graphics::fillEllipse(
    int16_t x0,
    int16_t y0,
    int16_t rx,
    int16_t ry,
    uint16_t color
)
{
    for(int16_t y = -ry; y <= ry; y++)
    {
        for(int16_t x = -rx; x <= rx; x++)
        {
            float dx = (float)x / rx;
            float dy = (float)y / ry;

            if(
                (dx * dx) +
                (dy * dy)
                <= 1.0f
            )
            {
                drawPixel(
                    x0 + x,
                    y0 + y,
                    color
                );
            }
        }
    }
}

// =====================================================
// ARC
// =====================================================

void Graphics::drawArc(
    int16_t x0,
    int16_t y0,
    int16_t radius,
    float startAngle,
    float endAngle,
    uint16_t color
)
{
    for(
        float a = startAngle;
        a <= endAngle;
        a += 1.0f
    )
    {
        float r =
            a * 0.0174532925f;

        drawPixel(
            x0 + (int16_t)(cos(r) * radius),
            y0 + (int16_t)(sin(r) * radius),
            color
        );
    }
}

// =====================================================
// GRADIENT RECTANGLE
// =====================================================

void Graphics::drawGradientRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t colorTop,
    uint16_t colorBottom
)
{
    for(int16_t iy = 0; iy < h; iy++)
    {
        uint16_t color =
            (iy < (h / 2))
            ? colorTop
            : colorBottom;

        drawLine(
            x,
            y + iy,
            x + w - 1,
            y + iy,
            color
        );
    }
}

// =====================================================
// PANEL
// =====================================================

void Graphics::drawPanel(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t fillColor,
    uint16_t lightColor,
    uint16_t darkColor
)
{
    fillRect(
        x,
        y,
        w,
        h,
        fillColor
    );

    drawLine(
        x,
        y,
        x + w - 1,
        y,
        lightColor
    );

    drawLine(
        x,
        y,
        x,
        y + h - 1,
        lightColor
    );

    drawLine(
        x,
        y + h - 1,
        x + w - 1,
        y + h - 1,
        darkColor
    );

    drawLine(
        x + w - 1,
        y,
        x + w - 1,
        y + h - 1,
        darkColor
    );
}

// =====================================================
// CHECKBOX
// =====================================================

void Graphics::drawCheckBox(
    int16_t x,
    int16_t y,
    bool checked,
    uint16_t borderColor,
    uint16_t checkColor
)
{
    drawRect(
        x,
        y,
        16,
        16,
        borderColor
    );

    if(checked)
    {
        drawLine(
            x + 3,
            y + 8,
            x + 7,
            y + 12,
            checkColor
        );

        drawLine(
            x + 7,
            y + 12,
            x + 13,
            y + 3,
            checkColor
        );
    }
}

// =====================================================
// SLIDER
// =====================================================

void Graphics::drawSlider(
    int16_t x,
    int16_t y,
    int16_t w,
    uint16_t value,
    uint16_t maxValue,
    uint16_t fillColor,
    uint16_t borderColor
)
{
    drawRect(
        x,
        y,
        w,
        10,
        borderColor
    );

    int16_t knobX =
        x +
        (((w - 10) * value) /
        maxValue);

    fillRect(
        knobX,
        y,
        10,
        10,
        fillColor
    );
}

// =====================================================
// TAB
// =====================================================

void Graphics::drawTab(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    bool active,
    uint16_t fillColor,
    uint16_t borderColor
)
{
    if(active)
    {
        fillRect(
            x,
            y,
            w,
            h,
            fillColor
        );
    }

    drawRect(
        x,
        y,
        w,
        h,
        borderColor
    );
}
// =====================================================
// FILLED TRIANGLE
// =====================================================

void Graphics::fillTriangle(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    int16_t x3,
    int16_t y3,
    uint16_t color
)
{
    int16_t minY =
        min(y1, min(y2, y3));

    int16_t maxY =
        max(y1, max(y2, y3));

    for(int16_t y = minY;
        y <= maxY;
        y++)
    {
        int16_t nodes[3];
        uint8_t count = 0;

        auto edge =
        [&](int16_t xa,
            int16_t ya,
            int16_t xb,
            int16_t yb)
        {
            if(
                ((ya < y) && (yb >= y))
                ||
                ((yb < y) && (ya >= y))
            )
            {
                nodes[count++] =
                    xa +
                    ((y - ya) *
                    (xb - xa)) /
                    (yb - ya);
            }
        };

        edge(x1,y1,x2,y2);
        edge(x2,y2,x3,y3);
        edge(x3,y3,x1,y1);

        if(count < 2)
        {
            continue;
        }

        if(nodes[0] > nodes[1])
        {
            int16_t t = nodes[0];
            nodes[0] = nodes[1];
            nodes[1] = t;
        }

        drawLine(
            nodes[0],
            y,
            nodes[1],
            y,
            color
        );
    }
}
// =====================================================
// POLYGON
// =====================================================

void Graphics::drawPolygon(
    const int16_t* px,
    const int16_t* py,
    uint8_t count,
    uint16_t color
)
{
    if(count < 2)
    {
        return;
    }

    for(uint8_t i = 0;
        i < count;
        i++)
    {
        uint8_t n =
            (i + 1) % count;

        drawLine(
            px[i],
            py[i],
            px[n],
            py[n],
            color
        );
    }
}
// =====================================================
// FILLED POLYGON
// =====================================================

void Graphics::fillPolygon(
    const int16_t* px,
    const int16_t* py,
    uint8_t count,
    uint16_t color
)
{
    if(count < 3)
    {
        return;
    }

    int16_t minY = py[0];
    int16_t maxY = py[0];

    for(uint8_t i = 1;
        i < count;
        i++)
    {
        if(py[i] < minY)
        {
            minY = py[i];
        }

        if(py[i] > maxY)
        {
            maxY = py[i];
        }
    }

    for(int16_t y = minY;
        y <= maxY;
        y++)
    {
        int16_t nodes[32];
        uint8_t nodeCount = 0;

        for(uint8_t i = 0;
            i < count;
            i++)
        {
            uint8_t j =
                (i + 1) % count;

            if(
                ((py[i] < y) &&
                 (py[j] >= y))
                ||
                ((py[j] < y) &&
                 (py[i] >= y))
            )
            {
                nodes[nodeCount++] =
                    px[i] +
                    ((y - py[i]) *
                    (px[j] - px[i])) /
                    (py[j] - py[i]);
            }
        }

        for(uint8_t i = 0;
            i < nodeCount;
            i++)
        {
            for(uint8_t j = i + 1;
                j < nodeCount;
                j++)
            {
                if(nodes[i] > nodes[j])
                {
                    int16_t t = nodes[i];
                    nodes[i] = nodes[j];
                    nodes[j] = t;
                }
            }
        }

        for(uint8_t i = 0;
            i < nodeCount;
            i += 2)
        {
            if(i + 1 >= nodeCount)
            {
                break;
            }

            drawLine(
                nodes[i],
                y,
                nodes[i + 1],
                y,
                color
            );
        }
    }
}

uint16_t Graphics::alphaBlend(
    uint16_t src,
    uint16_t dst,
    uint8_t alpha
)
{
    uint8_t sr =
        ((src >> 11) & 0x1F) << 3;

    uint8_t sg =
        ((src >> 5) & 0x3F) << 2;

    uint8_t sb =
        (src & 0x1F) << 3;

    uint8_t dr =
        ((dst >> 11) & 0x1F) << 3;

    uint8_t dg =
        ((dst >> 5) & 0x3F) << 2;

    uint8_t db =
        (dst & 0x1F) << 3;

    uint8_t r =
        (sr * alpha +
         dr * (255 - alpha))
        / 255;

    uint8_t g =
        (sg * alpha +
         dg * (255 - alpha))
        / 255;

    uint8_t b =
        (sb * alpha +
         db * (255 - alpha))
        / 255;

    return
        ((r >> 3) << 11) |
        ((g >> 2) << 5) |
        (b >> 3);
}

void Graphics::drawTextureTriangle(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    int16_t x3,
    int16_t y3,

    const uint16_t* texture,
    int16_t texW,
    int16_t texH
)
{
    int16_t minX =
        min(x1,min(x2,x3));

    int16_t maxX =
        max(x1,max(x2,x3));

    int16_t minY =
        min(y1,min(y2,y3));

    int16_t maxY =
        max(y1,max(y2,y3));

    float denom =
        ((y2-y3)*(x1-x3))
        +
        ((x3-x2)*(y1-y3));

    if(denom == 0)
        return;

    for(int16_t y=minY;
        y<=maxY;
        y++)
    {
        for(int16_t x=minX;
            x<=maxX;
            x++)
        {
            float w1 =
                ((y2-y3)*(x-x3)
                +
                (x3-x2)*(y-y3))
                / denom;

            float w2 =
                ((y3-y1)*(x-x3)
                +
                (x1-x3)*(y-y3))
                / denom;

            float w3 =
                1.0f - w1 - w2;

            if(
                w1 >= 0 &&
                w2 >= 0 &&
                w3 >= 0
            )
            {
                int16_t tx =
                    (int16_t)(
                        w1 * 0 +
                        w2 * (texW-1) +
                        w3 * (texW/2)
                    );

                int16_t ty =
                    (int16_t)(
                        w1 * (texH-1) +
                        w2 * (texH-1) +
                        w3 * 0
                    );

                uint16_t color =
                    texture[
                        ty * texW +
                        tx
                    ];

                drawPixel(
                    x,
                    y,
                    color
                );
            }
        }
    }
}

void Graphics::drawTexturedPolygon(
    const int16_t* px,
    const int16_t* py,
    uint8_t count,

    const uint16_t* texture,
    int16_t texW,
    int16_t texH
)
{
    if(count < 3)
        return;

    for(
        uint8_t i = 1;
        i < count - 1;
        i++
    )
    {
        drawTextureTriangle(
            px[0],
            py[0],

            px[i],
            py[i],

            px[i + 1],
            py[i + 1],

            texture,
            texW,
            texH
        );
    }
}

// =====================================================
// TEXTURE RECT
// =====================================================

void Graphics::drawTextureRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    const uint16_t* texture,
    int16_t texW,
    int16_t texH
)
{
    if(texture == nullptr)
    {
        return;
    }

    for(int16_t iy = 0; iy < h; iy++)
    {
        int16_t ty =
            (iy * texH) / h;

        for(int16_t ix = 0; ix < w; ix++)
        {
            int16_t tx =
                (ix * texW) / w;

            drawPixel(
                x + ix,
                y + iy,
                texture[
                    ty * texW +
                    tx
                ]
            );
        }
    }
}

void Graphics::drawLED(
    int16_t x,
    int16_t y,
    int16_t radius,
    bool on,
    uint16_t onColor,
    uint16_t offColor
)
{
    fillCircle(
        x,
        y,
        radius,
        on ? onColor : offColor
    );

    drawCircle(
        x,
        y,
        radius,
        Color::WHITE
    );
}

void Graphics::drawMeter(
    int16_t x,
    int16_t y,
    int16_t radius,
    uint16_t value,
    uint16_t maxValue,
    uint16_t color
)
{
    float angle =
        (
            (float)value /
            (float)maxValue
        ) * 270.0f;

    drawCircle(
        x,
        y,
        radius,
        color
    );

    drawArc(
        x,
        y,
        radius,
        -135,
        -135 + angle,
        color
    );
}

void Graphics::drawCrosshair(
    int16_t x,
    int16_t y,
    int16_t size,
    uint16_t color
)
{
    drawLine(
        x - size,
        y,
        x + size,
        y,
        color
    );

    drawLine(
        x,
        y - size,
        x,
        y + size,
        color
    );
}