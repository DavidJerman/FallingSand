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

    // Main functions
    void render();
    void input();
    void logic();

    // ---> Logic <---
    bool createSandGrain(uint32_t x, uint32_t y, olc::Pixel color);
    bool createSandBlob(uint32_t x, uint32_t y, uint32_t size, olc::Pixel color);
    void createSandBlob(uint32_t x, uint32_t y, uint32_t size);
    void countNumberOfGrains();
    void processSand();
    void clearSand();
    void deleteSand(uint32_t x, uint32_t y);
    void checkWinCondition();

    // ---> Input <---
    std::pair<uint32_t, uint32_t> getMousePosition();

    // ---> Rendering <---
    void renderSand();
    void renderNextColorIndicator();
    void renderScore();
    void renderWinScreen();

    // Win condition
    void checkSandConnection();
    void sideSearch(uint32_t x, uint32_t y, const olc::Pixel &color, bool &foundConnection);
    void clearVisited(bool connectionFound);

    // Variables
    std::array<std::array<SandGrain, SCREEN_HEIGHT>, SCREEN_WIDTH> sand;
    std::vector<olc::Pixel> colors;

    bool mouseHeld{false};
    uint32_t numberOfGrains{0};
    uint32_t numberOfConnections{0};
    olc::Pixel nextColor{olc::BLANK};
    bool gameLost{false};
};
