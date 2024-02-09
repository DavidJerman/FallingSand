#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "game.h"
#include "constants.h"

#include <cassert>

int main()
{
    assert(SCREEN_WIDTH > 0);
    assert(SCREEN_HEIGHT > 0);
    assert(SCALE > 0);
    assert(NUM_OF_COLORS > 0);
    assert(NUM_OF_COLORS <= 12);
    assert(MAX_GRAINS > 0);
    assert(MAX_GRAINS <= SCREEN_WIDTH * SCREEN_HEIGHT);

    Game game;
    if (game.Construct(SCREEN_WIDTH, SCREEN_HEIGHT, SCALE, SCALE, false, true))
        game.Start();
    return 0;
}
