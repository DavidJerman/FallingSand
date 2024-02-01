#include "game.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "constants.h"

int main()
{
    Game game;
    if (game.Construct(SCREEN_WIDTH, SCREEN_HEIGHT, SCALE, SCALE))
        game.Start();
    return 0;
}
