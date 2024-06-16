#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "module.h"
#include "sound.h"
#include "gfx.h"
#include "gamestate.h"

int main()
{
    init_gfx();
    sound_init();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    srand(time(NULL));
    init_state();

    bool running = true;

    
    while (running) {
        show_start_screen();

        if (get_state() == GAME_INTRO) {
            show_start_screen();
        } else if (get_state() == GAME_LOOP) {
            game_loop();
        } else if (get_state() == GAME_HIGHSCORES) {
            show_highscores();
        }

        int ch = getch();
        update_state(ch);
        if (ch == 'q') {
            running = false;
        }
    }

    sound_exit();
    exit_gfx();

    return 0;
}

void show_start_screen()
{
    clear();
    print_current_state();
    mvprintw(LINES / 2 - 2, (COLS - 20) / 2, "1. Play");
    mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "2. Scores");
    mvprintw(LINES / 2 + 1, (COLS - 20) / 2, "'q' to quit");
    msleep(100);
    refresh();
}
