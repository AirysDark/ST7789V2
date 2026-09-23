#include "Touchdriver.h"

TouchDriver touch;

void TouchDriver::begin()
{
    pinMode(TOUCH_RST, OUTPUT);
    pinMode(TOUCH_INT, INPUT_PULLUP);

    // RESET CONTROLLER
    digitalWrite(TOUCH_RST, LOW);
    delay(20);
    digitalWrite(TOUCH_RST, HIGH);
    delay(200);

    // I2C INIT
    Wire.begin(TOUCH_SDA, TOUCH_SCL);
    Wire.setClock(400000);

    // PROBE DEVICE
    Wire.beginTransmission(CST816_ADDR);
    if(Wire.endTransmission() == 0)
    {
        Serial.println("CST816 FOUND");
    }
    else
    {
        Serial.println("CST816 NOT FOUND");
    }
}

bool TouchDriver::update()
{
    touched = false;

    // POLL LIMITER
    if(millis() - lastRead < 10)
    {
        return false;
    }

    lastRead = millis();

    // TOUCH IRQ
    if(digitalRead(TOUCH_INT) == HIGH)
    {
        return false;
    }

    // READ TOUCH DATA
    Wire.beginTransmission(CST816_ADDR);
    Wire.write(0x03);

    if(Wire.endTransmission(false) != 0)
    {
        return false;
    }

    Wire.requestFrom(CST816_ADDR, 4);

    if(Wire.available() < 4)
    {
        return false;
    }

    uint8_t xh = Wire.read();
    uint8_t xl = Wire.read();
    uint8_t yh = Wire.read();
    uint8_t yl = Wire.read();

    uint16_t rawX = ((xh & 0x0F) << 8) | xl;
    uint16_t rawY = ((yh & 0x0F) << 8) | yl;

    // FILTER NOISE
    if(rawX == 0 && rawY == 0)
    {
        return false;
    }

    // CALIBRATED TOUCH MAPPING
    int16_t calibratedX = map(rawY, calib.rawMinY, calib.rawMaxY, 279, 0);
    int16_t calibratedY = map(rawX, calib.rawMinX, calib.rawMaxX, 0, 239);

    // APPLY OFFSETS
    calibratedX += TOUCH_OFFSET_X;
    calibratedY += TOUCH_OFFSET_Y;

    // CLAMP
    calibratedX = constrain(calibratedX, 0, 279);
    calibratedY = constrain(calibratedY, 0, 239);

    // SAVE
    x = calibratedX;
    y = calibratedY;

    touched = true;
    return true;
}

bool TouchDriver::isTouched()
{
    return touched;
}

uint16_t TouchDriver::getX()
{
    return x;
}

uint16_t TouchDriver::getY()
{
    return y;
}
