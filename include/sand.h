#pragma once

#include <cstdint>

#include "constants.h"
#include "olcPixelGameEngine.h"

struct SandGrain
{
    SandGrain(olc::Pixel color)
        : color(color), exists(true)
    {
    }

    SandGrain() = default;

    olc::Pixel color;
    bool exists {false};
};
