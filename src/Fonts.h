#pragma once

#include <Arduino.h>

// =====================================================
// 5x7 BITMAP FONT
// =====================================================
// Each character is 5 pixels wide, 7 pixels tall.
// Stored column-by-column.
// ASCII START: 32 (SPACE)
// FONT INDEX: font5x7[c - 32]

extern const uint8_t font5x7[][5];
