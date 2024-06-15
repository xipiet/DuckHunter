#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "module.h"
#include "sound.h"
#include "windmill.h"
#include "gamestate.h"

int px;
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
    reload_ammo();
    reset_score();

    curs_set(0);
    timeout(0);

    float speed = 1.0;  // Initial speed
    int frame_counter = 0;  // To keep track of frames for increasing speed

    while (get_state() == GAME_LOOP)
    {
        int ch = getch();
        if (update_state(ch))
        {
            break;
        }

        if (ch == 'q')
        {
            break;
        }

        MEVENT event;
        if (ch == KEY_MOUSE && getmouse(&event) == OK)
        {
            if (event.bstate & BUTTON1_CLICKED)
            {
                sound_play("shoot.wav");
                use_ammo();
                if (get_ammo() == 0)
                {
                    FILE *fptr;
                    fptr = fopen("scores.txt", "a");

                    int score = get_score();
                    fprintf(fptr, "\nScore: %d", score);

                    fclose(fptr);

                    set_state(GAME_INTRO);
                    break;
                }
                if (event.x >= px && event.x <= px + 8 && event.y >= py && event.y <= py + 2)
                {
                    sound_play("hit.wav");
                    add_ammo(2);
                    increase_score();

                    get_ammo();
                    generate_random_start_position();
                    generate_random_coordinates();
                }
            }
        }

        clear();

        if (px < target_x)
        {
            px += speed;
        }
        else if (px > target_x)
        {
            px -= speed;
        }

        if (py < target_y)
        {
            py += speed;
        }
        else if (py > target_y)
        {
            py -= speed;
        }

        if (px == target_x && py == target_y)
        {
            generate_random_coordinates();
        }

        update_windmill();
        render_windmill();

        print_bird(py, px, 1);
        render_ammo();
        render_score();

        refresh();

        frame_counter++;
        if (frame_counter % 100 == 0)  // Increase speed every 100 frames
        {
            speed += 0.1;  // Adjust the increment as needed
        }

        msleep(100 / speed);  // Adjust sleep duration to control game speed
    }
}
