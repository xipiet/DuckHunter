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
        if (c == '1')
        {
            state = GAME_LOOP;
            clear();
        }
        else if (c == '2')
        {
            state = GAME_HIGHSCORES;
            clear();
        }
        else if (c == 'q')
        {
            return true; // exits the game
        }
    }
    else if (state == GAME_LOOP)
    {
        if (c == 'q')
        {
            state = GAME_INTRO;
        }
    }
    else if (state == GAME_HIGHSCORES)
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

void set_state(GAME_STATE new_state)
{
    state = new_state;
}

void print_current_state() {
    if (state == GAME_INTRO) {
        mvprintw(0, 0, "Current State: Intro");
    } else if (state == GAME_LOOP) {
        mvprintw(0, 0, "Current State: Gameloop");
    } else if (state == GAME_HIGHSCORES) {
        mvprintw(0, 0, "Current State: Highscores");
    }
}