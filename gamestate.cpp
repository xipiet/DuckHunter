#include "gamestate.h"
#include <ncurses.h>

static GAME_STATE state = GAME_INTRO;

void init_state()
{
    state = GAME_INTRO;
}

bool update_state(int c)
{
    if (state == GAME_INTRO)
    {
        if (c == ' ')
        {
            state = GAME_LOOP;
            clear();
        }
        else if (c == 'q')
        {
            return true;  // Indicate to exit the game
        }
    }
    else if (state == GAME_LOOP)
    {
        if (c == 'q')
        {
            state = GAME_INTRO;
        }
    }
    return false;
}

GAME_STATE get_state()
{
    return state;
}
