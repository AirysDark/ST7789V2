#pragma once

// =====================================================
// ESP32-S3-Watch-Engine
// Master Include Header
// =====================================================
//
// Hardware:
//   ESP32-S3-LCD-1.69
//   ST7789V2 Display
//   CST816 Touch
//
// Features:
//   Display Driver
//   Touch Driver
//   Framebuffer
//   Double Buffering
//   Z-Buffer
//   2D Graphics
//   UI Widgets
//   Texture Mapping
//   Software 3D Renderer
//   Mesh Rendering
//
// =====================================================

// Core Arduino
#include <Arduino.h>

// =====================================================
// CORE SYSTEMS
// =====================================================

#include "Color.h"

#include "DisplayDriver.h"

#include "TouchDriver.h"

#include "Framebuffer.h"

// =====================================================
// 2D GRAPHICS
// =====================================================

#include "Graphics.h"

#include "Render.h"

// =====================================================
// 3D ENGINE
// =====================================================

#include "Renderer3D.h"

// =====================================================
// VERSION
// =====================================================

#define ESP32S3_WATCH_ENGINE_VERSION_MAJOR 1
#define ESP32S3_WATCH_ENGINE_VERSION_MINOR 0
#define ESP32S3_WATCH_ENGINE_VERSION_PATCH 0

#define ESP32S3_WATCH_ENGINE_VERSION "1.0.0"

// =====================================================
// LIBRARY INFO
// =====================================================

namespace ESP32S3WatchEngine
{
    inline const char* version()
    {
        return ESP32S3_WATCH_ENGINE_VERSION;
    }
}