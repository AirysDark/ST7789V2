#include "Displaydriver.h"

DisplayDriver display;

DisplayDriver::DisplayDriver()
: spi(FSPI)
{
}

void DisplayDriver::begin()
{
    pinMode(TFT_CS, OUTPUT);
    pinMode(TFT_DC, OUTPUT);
    pinMode(TFT_RST, OUTPUT);
    pinMode(TFT_BL, OUTPUT);

    digitalWrite(TFT_CS, HIGH);
    digitalWrite(TFT_DC, HIGH);
    digitalWrite(TFT_BL, HIGH);

    spi.begin(
        TFT_SCLK,
        -1,
        TFT_MOSI,
        TFT_CS
    );

    reset();
    initDisplay();
    fillScreen(0x0000);
}

void DisplayDriver::startFramebufferWrite()
{
    spi.beginTransaction(
        SPISettings(
            40000000,
            MSBFIRST,
            SPI_MODE0
        )
    );

    digitalWrite(TFT_DC, HIGH);
    digitalWrite(TFT_CS, LOW);
}

void DisplayDriver::endFramebufferWrite()
{
    digitalWrite(TFT_CS, HIGH);
    spi.endTransaction();
}

void DisplayDriver::setFramebufferWindow(
    uint16_t x0,
    uint16_t y0,
    uint16_t x1,
    uint16_t y1
)
{
    setWindow(x0, y0, x1, y1);
}

void DisplayDriver::fillScreen(uint16_t color)
{
    fillRect(
        0,
        0,
        TFT_WIDTH,
        TFT_HEIGHT,
        color
    );
}

void DisplayDriver::drawPixel(
    int16_t x,
    int16_t y,
    uint16_t color
)
{
    fillRect(
        x,
        y,
        1,
        1,
        color
    );
}

void DisplayDriver::fillRect(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    uint16_t color
)
{
    if(w <= 0 || h <= 0) return;
    if(x >= TFT_WIDTH || y >= TFT_HEIGHT) return;
    if((x + w) <= 0 || (y + h) <= 0) return;

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

    if((x + w) > TFT_WIDTH)
        w = TFT_WIDTH - x;

    if((y + h) > TFT_HEIGHT)
        h = TFT_HEIGHT - y;

    if(w <= 0 || h <= 0) return;

    setWindow(
        x,
        y,
        x + w - 1,
        y + h - 1
    );

    startData();

    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;

    uint32_t total =
        (uint32_t)w * h;

    while(total--)
    {
        spi.transfer(hi);
        spi.transfer(lo);
    }

    endWrite();
}

void DisplayDriver::drawLine(
    int x0,
    int y0,
    int x1,
    int y1,
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
        drawPixel(x0, y0, color);

        if(x0 == x1 && y0 == y1)
            break;

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

void DisplayDriver::fillCircle(
    int16_t x0,
    int16_t y0,
    int16_t r,
    uint16_t color
)
{
    for(int16_t y = -r; y <= r; y++)
    {
        for(int16_t x = -r; x <= r; x++)
        {
            if((x*x + y*y) <= (r*r))
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

void DisplayDriver::reset()
{
    digitalWrite(TFT_RST, HIGH);
    delay(50);

    digitalWrite(TFT_RST, LOW);
    delay(50);

    digitalWrite(TFT_RST, HIGH);
    delay(150);
}

void DisplayDriver::initDisplay()
{
    writeCmd(0x01);
    delay(150);

    writeCmd(0x11);
    delay(150);

    writeCmd(0x3A);
    writeData(0x55);

    writeCmd(0x36);
    writeData(0xA0);

    writeCmd(0x21);
    writeCmd(0x13);
    writeCmd(0x29);

    delay(100);
}

void DisplayDriver::startCommand()
{
    spi.beginTransaction(
        SPISettings(
            40000000,
            MSBFIRST,
            SPI_MODE0
        )
    );

    digitalWrite(TFT_DC, LOW);
    digitalWrite(TFT_CS, LOW);
}

void DisplayDriver::startData()
{
    spi.beginTransaction(
        SPISettings(
            40000000,
            MSBFIRST,
            SPI_MODE0
        )
    );

    digitalWrite(TFT_DC, HIGH);
    digitalWrite(TFT_CS, LOW);
}

void DisplayDriver::endWrite()
{
    digitalWrite(TFT_CS, HIGH);
    spi.endTransaction();
}

void DisplayDriver::writeCmd(uint8_t cmd)
{
    startCommand();
    spi.transfer(cmd);
    endWrite();
}

void DisplayDriver::writeData(uint8_t data)
{
    startData();
    spi.transfer(data);
    endWrite();
}

void DisplayDriver::setWindow(
    uint16_t x0,
    uint16_t y0,
    uint16_t x1,
    uint16_t y1
)
{
    x0 += X_OFFSET;
    x1 += X_OFFSET;

    y0 += Y_OFFSET;
    y1 += Y_OFFSET;

    writeCmd(0x2A);

    startData();
    spi.transfer(x0 >> 8);
    spi.transfer(x0 & 0xFF);
    spi.transfer(x1 >> 8);
    spi.transfer(x1 & 0xFF);
    endWrite();

    writeCmd(0x2B);

    startData();
    spi.transfer(y0 >> 8);
    spi.transfer(y0 & 0xFF);
    spi.transfer(y1 >> 8);
    spi.transfer(y1 & 0xFF);
    endWrite();

    writeCmd(0x2C);
}