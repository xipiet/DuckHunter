#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "module.h"
#include "sound.h"
#include "gamestate.h"

bool bird_reached_target = false;
float beschleunigung = 0.1; // beschleunigung pro 100 frames hier ändern

void game_loop()
{

    generate_random_start_position();
    generate_random_coordinates();
    reload_ammo();
    reset_score();
    init_windmill();

    bird_reached_target = false;
    int frame_counter = 0;

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
                    write_to_file();
                    set_state(GAME_INTRO);
                    break;
                }
                if (event.x >= px && event.x <= px + 8 && event.y >= py && event.y <= py + 2)
                {

                    sound_play("hit.wav");
                    add_ammo(1);
                    increase_score();

                    if (get_ammo() == MAX_AMMO)
                    {
                        increase_score();
                    }
                    
                    add_ammo(1);
                    get_ammo();
                    generate_random_start_position();
                    generate_random_coordinates();
                }
            }
        }
        clear();
        print_current_state();
        vogel_speed();
        render_windmill();
        update_windmill();
        print_bird(py, px, 1);
        render_ammo();
        render_score();

        refresh();

        frame_counter++;
        if (frame_counter % 100 == 0)
        {
            speed += beschleunigung;
        }

        msleep(100 / speed);
    }
}
