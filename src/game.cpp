#include "game.h"

#include <random>

Game::Game()
{
    sAppName = "Game";
}

bool Game::OnUserCreate()
{
    initColors();
    nextColor = colors[0];

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
    // --> Input <--
    int32_t mouseX = GetMouseX();
    int32_t mouseY = GetMouseY();

    if (GetMouse(0).bHeld)
    {
        if (!mouseHeld)
            createSandBlob(mouseX, mouseY, 19);
        mouseHeld = true;
    }
    else
    {
        mouseHeld = false;
    }

    processSand();

    // --> Drawing <--
    Clear(olc::BLACK);

    // Next color indicator
    FillCircle(mouseX, mouseY, 9, nextColor);

    // SandGrain
    for (uint32_t x = 0; x < SCREEN_WIDTH; ++x)
    {
        for (uint32_t y = 0; y < SCREEN_HEIGHT; ++y)
        {
            if (sand[x][y].exists)
            {
                Draw(x, y, sand[x][y].color);
            }
        }
    }

    return true;
}

void Game::initColors()
{
    for (uint32_t i = 0; i < NUM_OF_COLORS; ++i)
    {
        colors.push_back(COLORS[i]);
    }
}

bool Game::createSandGrain(uint32_t x, uint32_t y, olc::Pixel color)
{
    if (sand[x][y].exists)
        return false;
    
    sand[x][y] = {color};

    return true;
}

bool Game::createSandBlob(uint32_t x, uint32_t y, uint32_t size, olc::Pixel color)
{
    bool grainCreated = false;

    for (uint32_t i = x - size / 2; i < x + size / 2; ++i)
    {
        for (uint32_t j = y - size / 2; j < y + size / 2; ++j)
        {
            if (rand() % 10 > 3)
                if (createSandGrain(MAX(MIN(i, SCREEN_WIDTH - 1), 0), MAX(MIN(j, SCREEN_HEIGHT - 1), 0), color))
                    grainCreated = true;
        }
    }

    return grainCreated;
}

void Game::createSandBlob(uint32_t x, uint32_t y, uint32_t size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_OF_COLORS - 1);
    
    if (createSandBlob(x, y, size, nextColor))
        nextColor = colors[dis(gen)];
}

void Game::processSand()
{
    for (int32_t x = SCREEN_WIDTH - 1; x >= 0; --x)
    {
        for (int32_t y = SCREEN_HEIGHT - 1; y >= 0; --y)
        {
            auto &grain = sand[x][y];

            if (grain.exists)
            {
                if (y < SCREEN_HEIGHT - 1)
                {
                    auto &below = sand[x][y + 1];
                    if (!below.exists)
                    {
                        below = grain;
                        grain.exists = false;
                    }
                    else if (x > 0 && x < SCREEN_WIDTH - 1)
                    {
                        auto &belowLeft = sand[x - 1][y + 1];
                        auto &belowRight = sand[x + 1][y + 1];
                        if (!belowLeft.exists && belowRight.exists)
                        {
                            belowLeft = grain;
                            grain.exists = false;
                        }
                        else if (belowLeft.exists && !belowRight.exists)
                        {
                            belowRight = grain;
                            grain.exists = false;
                        }
                        else if (!belowLeft.exists && !belowRight.exists)
                        {
                            if (rand() % 2)
                            {
                                belowLeft = grain;
                            }
                            else
                            {
                                belowRight = grain;
                            }
                            grain.exists = false;
                        }
                    }
                }
            }
        }
    }
}

bool Game::checkWin()
{
    // TODO: Implement

    return false;
}
