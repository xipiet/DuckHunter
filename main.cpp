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
void show_highscores();
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
            if (ch == '2')  // Show highscores if '2' is pressed
            {
                show_highscores();
            }
            else if (update_state(ch))
            {
                running = false;  // Exit the loop
            }
        }
    }

sound_exit();
exit_gfx();

return 0;
}

void show_highscores()
{
    clear();
    mvprintw(1, (COLS / 2), "Scores");

    FILE *fptr = fopen("scores.txt", "r");
    if (fptr == NULL)
    {
        mvprintw(2, (COLS / 2), "No scores available.");
    }
    else
    {
        char line[256];
        int line_num = 2;
        while (fgets(line, sizeof(line), fptr) != NULL)
        {
            mvprintw(line_num++, (COLS / 2), "%s", line);
        }
        fclose(fptr);
    }

    mvprintw(LINES - 2, (COLS / 2), "Press 'q' to return.");
    msleep(100);
    refresh();

    while (true)
    {
        int ch = getch();
        if (ch == 'q')
        {
            break;
        }
    }
}


void show_start_screen()
{
clear();
mvprintw(LINES / 2 - 2, (COLS - 20) / 2, "1. Play");
mvprintw(LINES / 2 - 1, (COLS - 20) / 2, "2. Scores");
mvprintw(LINES / 2 + 1, (COLS - 20) / 2, "'q' to quit");
msleep(100);
refresh();
}
