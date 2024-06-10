#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "module.h"
#include "sound.h"
#include "windmill.h"
#include "gamestate.h"

int px = 0;
int py;
int target_x;
int target_y;
bool bird_reached_target = false;

void generate_random_coordinates()
{
    target_x = rand() % (COLS - 9);  // dass x im fenster ist
    target_y = rand() % (LINES - 3); // dass y im fenster ist
}

void generate_random_start_position()
{
    int side = rand() % 4;
    switch (side)
    {
    case 0: // links
        px = -9;
        py = rand() % (LINES - 3);
        break;
    case 1: // rechts
        px = COLS;
        py = rand() % (LINES - 3);
        break;
    case 2: // oben
        px = rand() % (COLS - 9);
        py = -3;
        break;
    case 3: // unten
        px = rand() % (COLS - 9);
        py = LINES;
        break;
    }
}

void game_loop()
{
    bird_reached_target = false;
    generate_random_start_position();
    generate_random_coordinates();

    curs_set(0);
    timeout(0);

    while (get_state() == GAME_LOOP)
    {
        int ch = getch();
        update_state(ch);

        if (ch == 'q')
        {
            break;
        }

        MEVENT event;
        if (ch == KEY_MOUSE && getmouse(&event) == OK)
        {
            if (event.bstate & BUTTON1_CLICKED)
            {
                if (event.x >= px && event.x <= px + 8 && event.y >= py && event.y <= py + 2)
                {
                    sound_play("boing.wav");
                    generate_random_start_position();
                    generate_random_coordinates();
                }
            }
            clear();
        }

        clear();

        if (!bird_reached_target)
        {
            if (px < target_x)
            {
                px++;
            }
            else if (px > target_x)
            {
                px--;
            }

            if (py < target_y)
            {
                py++;
            }
            else if (py > target_y)
            {
                py--;
            }

            if (px == target_x && py == target_y)
            {
                bird_reached_target = true;
                generate_random_start_position();
                generate_random_coordinates();
            }
        }

        update_windmill();
        render_windmill();

        print_bird(py, px, 1);
        refresh();
        msleep(100); // 100ms = 10 fps
    }
}
