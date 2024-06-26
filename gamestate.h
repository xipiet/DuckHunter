#ifndef GAMESTATE_H
#define GAMESTATE_H

enum GAME_STATE
{
    GAME_INTRO = 0,
    GAME_LOOP = 1
};

void init_state();
bool update_state(int c);
GAME_STATE get_state();

#endif
