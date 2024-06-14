#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "module.h"
#include "windmill.h"
#include "sound.h"
#include "gfx.h"
#include "gamestate.h"

void msleep(float ms);
void show_start_screen();
void game_loop();

int main()
{
init_gfx();
sound_init();

keypad(stdscr, TRUE);
mousemask(ALL_MOUSE_EVENTS, NULL);
srand(time(NULL));

init_windmill();
init_state();

bool running = true;

while (running)
{
    show_start_screen();

    while (get_state() == GAME_LOOP)
    {
        game_loop();
    }

    if (get_state() == GAME_INTRO)
    {
        int ch = getch();
        if (update_state(ch))
        {
            running = false;  // verlässt den loop
        }
    }
}

sound_exit();
exit_gfx();

return 0;
}

void show_start_screen()
{
clear();
mvprintw(LINES / 2 - 2, (COLS - 20) / 2, "1. Play");
mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "2. Highscores (not implemented)");
mvprintw(LINES / 2 + 1, (COLS - 20) / 2, "Press 'q' to quit, '1' to play");
msleep(100);
refresh();
}
