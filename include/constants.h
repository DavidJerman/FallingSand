#pragma once

#include <cstdint>
#include "olcPixelGameEngine.h"

// Max and min macros
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

const uint32_t SCREEN_WIDTH = 160;
const uint32_t SCREEN_HEIGHT = 200;
const uint32_t SCALE = 4;

const uint32_t NUM_OF_COLORS = 1;
const uint32_t MAX_GRAINS = SCREEN_WIDTH * SCREEN_HEIGHT * 0.64;

const olc::Pixel COLORS[12] = {
    olc::Pixel(255, 223, 186),  // Light Peach
    olc::Pixel(255, 204, 153),  // Light Orange
    olc::Pixel(255, 179, 102),  // Light Goldenrod
    olc::Pixel(255, 153, 51),   // Orange
    olc::Pixel(255, 128, 0),    // Dark Orange
    olc::Pixel(204, 102, 0),    // Burnt Orange
    olc::Pixel(153, 76, 0),     // Rust
    olc::Pixel(102, 51, 0),     // Brown
    olc::Pixel(204, 153, 102),  // Tan
    olc::Pixel(153, 102, 51),   // Sienna
    olc::Pixel(128, 64, 0),     // Dark Brown
    olc::Pixel(102, 51, 0)      // Very Dark Brown
};
