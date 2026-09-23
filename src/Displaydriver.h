#pragma once

#include <Arduino.h>
#include <SPI.h>

#define TFT_CS     5
#define TFT_DC     4
#define TFT_RST    8
#define TFT_BL     15

#define TFT_SCLK   6
#define TFT_MOSI   7

#define TFT_WIDTH   280
#define TFT_HEIGHT  240

#define X_OFFSET   20
#define Y_OFFSET   0

class DisplayDriver
{
public:
    SPIClass spi;

    DisplayDriver();

    void begin();

    void startFramebufferWrite();
    void endFramebufferWrite();

    void setFramebufferWindow(
        uint16_t x0,
        uint16_t y0,
        uint16_t x1,
        uint16_t y1
    );

    void fillScreen(uint16_t color);

    void drawPixel(
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

    void drawLine(
        int x0,
        int y0,
        int x1,
        int y1,
        uint16_t color
    );

    void fillCircle(
        int16_t x0,
        int16_t y0,
        int16_t r,
        uint16_t color
    );

private:
    void reset();
    void initDisplay();

    void startCommand();
    void startData();
    void endWrite();

    void writeCmd(uint8_t cmd);
    void writeData(uint8_t data);

    void setWindow(
        uint16_t x0,
        uint16_t y0,
        uint16_t x1,
        uint16_t y1
    );
};

extern DisplayDriver display;