#pragma once

#include <array>
#include <vector>

#include "sand.h"
#include "constants.h"
#include "olcPixelGameEngine.h"

class Game : public olc::PixelGameEngine
{
public:
    Game();

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

private:
    // Init
    void initColors();

    // Functions
    bool createSandGrain(uint32_t x, uint32_t y, olc::Pixel color);
    bool createSandBlob(uint32_t x, uint32_t y, uint32_t size, olc::Pixel color);
    void createSandBlob(uint32_t x, uint32_t y, uint32_t size);
    void processSand();

    // Win condition
    bool checkWin();

// Variables
    std::array<std::array<SandGrain, SCREEN_HEIGHT>, SCREEN_WIDTH> sand;
    std::vector<olc::Pixel> colors;

    bool mouseHeld {false};
    olc::Pixel nextColor;
};
