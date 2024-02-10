#include "game.h"

#include <random>

Game::Game()
{
#ifdef VERSION
    sAppName = "Falling Sand Game v" VERSION;
#else
    sAppName = "Falling Sand Game"; 
#endif
}

bool Game::OnUserCreate()
{
    initColors();
    nextColor = colors[0];

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
    input();

    logic();

    render();

    return true;
}

void Game::initColors()
{
    for (uint32_t i = 0; i < NUM_OF_COLORS; ++i)
    {
        colors.push_back(COLORS[i]);
    }
}

void Game::render()
{
    Clear(olc::BLACK);

    renderNextColorIndicator();

    renderSand();

    renderScore();

    renderWinScreen();
}

void Game::renderSand()
{
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
}

void Game::renderNextColorIndicator()
{
    uint32_t x, y;
    std::tie(x, y) = getMousePosition();

    FillCircle(x, y, 9, nextColor);
}

void Game::renderScore()
{
    DrawString(3, 3, "G: " + std::to_string(numberOfGrains), olc::WHITE, 1);
    DrawString(3, 15, "C: " + std::to_string(numberOfConnections), olc::WHITE, 1);
}

void Game::renderWinScreen()
{
    if (gameLost)
    {
        Clear(olc::BLACK);
        DrawString(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 - 10, "You lost!", olc::WHITE, 2);
        DrawString(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 + 10, "Press R to restart", olc::WHITE, 1);
        DrawString(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 + 20, "Press ESC to exit", olc::WHITE, 1);
    }
}

void Game::input()
{
    if (GetKey(olc::Key::R).bPressed)
    {
        gameLost = false;
        clearSand();
    }

    if (GetKey(olc::Key::ESCAPE).bPressed)
    {
        exit(0);
    }

    uint32_t x, y;
    std::tie(x, y) = getMousePosition();

    if (GetMouse(0).bHeld)
    {
        if (!mouseHeld)
            createSandBlob(x, y, 19);
        mouseHeld = true;
    }
    else
    {
        mouseHeld = false;
    }
}

std::pair<uint32_t, uint32_t> Game::getMousePosition()
{
    return {GetMouseX(), GetMouseY()};
}

void Game::logic()
{
    if (gameLost)
        return;

    processSand();

    checkWinCondition();
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
    if (x < (size / 2 + 1) ||
        x > (SCREEN_WIDTH - size / 2 - 2) || 
        y < (size / 2 + 1) || 
        y > (SCREEN_HEIGHT - size / 2 - 2))
        return false;

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

    countNumberOfGrains();

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

void Game::countNumberOfGrains()
{
    numberOfGrains = 0;
    for (uint32_t x = 0; x < SCREEN_WIDTH; ++x)
    {
        for (uint32_t y = 0; y < SCREEN_HEIGHT; ++y)
        {
            if (sand[x][y].exists)
                ++numberOfGrains;
        }
    }
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

void Game::clearSand()
{
    for (uint32_t x = 0; x < SCREEN_WIDTH; ++x)
    {
        for (uint32_t y = 0; y < SCREEN_HEIGHT; ++y)
        {
            deleteSand(x, y);
        }
    }

    numberOfGrains = 0;
    numberOfConnections = 0;
}

void Game::deleteSand(uint32_t x, uint32_t y)
{
    sand[x][y].exists = false;
    sand[x][y].color = olc::BLANK;
}

void Game::checkWinCondition()
{
    checkSandConnection();

    if (numberOfGrains >= MAX_GRAINS)
    {
        gameLost = true;
        clearSand();
    }
}

void Game::checkSandConnection()
{
    std::vector<uint32_t> colorBands;
    uint32_t prevColorY = 0;

    for (uint32_t y = 0; y < SCREEN_HEIGHT; ++y)
    {
        if (sand[0][y].color == olc::BLANK)
            continue;

        if (sand[0][y].color == sand[0][prevColorY].color)
            continue;

        colorBands.push_back({y});

        prevColorY = y;
    }

    for (uint32_t i = 0; i < colorBands.size(); ++i)
    {
        const auto color = sand[0][colorBands[i]].color;
        bool connectionFound = false;

        sideSearch(0, colorBands[i], color, connectionFound);
        clearVisited(connectionFound);

        if (connectionFound)
        {
            ++numberOfConnections;
            countNumberOfGrains();
        }
    }
}

// Recrusive search algorithm
void Game::sideSearch(uint32_t x, uint32_t y, const olc::Pixel &color, bool &connectionFound)
{
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
    {
        return;
    }

    if (sand[x][y].visited || sand[x][y].color != color || sand[x][y].color == olc::BLANK)
    {
        return;
    }

    sand[x][y].visited = true;

    if (x == SCREEN_WIDTH - 1)
    {
        connectionFound = true;
        return;
    }

    sideSearch(x - 1, y, color, connectionFound);
    sideSearch(x + 1, y, color, connectionFound);
    sideSearch(x, y - 1, color, connectionFound);
    sideSearch(x, y + 1, color, connectionFound);
}

void Game::clearVisited(bool connectionFound)
{
    for (uint32_t x = 0; x < SCREEN_WIDTH; ++x)
    {
        for (uint32_t y = 0; y < SCREEN_HEIGHT; ++y)
        {
            if (connectionFound && sand[x][y].visited)
                deleteSand(x, y);
            sand[x][y].visited = false;
        }
    }
}
