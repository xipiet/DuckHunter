#include <ncurses.h>
#include "module.h"

int score = 0; // Punktestand-Variable

void increase_score()
{
    score++;
}

int get_score()
{
    return score;
}

void render_score()
{
    mvprintw(0, COLS - 10, "Score: %d", get_score());
}

void reset_score()
{
    score = 0;
}