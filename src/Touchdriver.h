#pragma once

#include <Arduino.h>
#include <Wire.h>

#define TOUCH_SDA   11
#define TOUCH_SCL   10

#define TOUCH_RST   13
#define TOUCH_INT   14

#define CST816_ADDR 0x15

// Fine offsets
#define TOUCH_OFFSET_X   0
#define TOUCH_OFFSET_Y   0

// Real measured ranges
#define TOUCH_MIN_X   15
#define TOUCH_MAX_X   224

#define TOUCH_MIN_Y   18
#define TOUCH_MAX_Y   245

struct TouchCalibration
{
    uint16_t rawMinX;
    uint16_t rawMaxX;
    uint16_t rawMinY;
    uint16_t rawMaxY;
};

class TouchDriver
{
public:
    TouchCalibration calib = {
        TOUCH_MIN_X,
        TOUCH_MAX_X,
        TOUCH_MIN_Y,
        TOUCH_MAX_Y
    };

    bool touched = false;
    uint16_t x = 0;
    uint16_t y = 0;
    unsigned long lastRead = 0;

    void begin();
    bool update();
    bool isTouched();
    uint16_t getX();
    uint16_t getY();
};

extern TouchDriver touch;
