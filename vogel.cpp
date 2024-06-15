#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include "module.h"
#include "sound.h"
#include "gamestate.h"

int px;
int py;
int target_x;
int target_y;
float speed = 1.0;

void print_bird(int y, int x, bool f)
{
    mvprintw(y + 0, x, "   _ _   ");
    mvprintw(y + 1, x, " /( v )\\");
    mvprintw(y + 2, x, "   ' '   ");
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

void generate_random_coordinates()
{
    
    target_x = rand() % (COLS - 9);  // dass x im fenster ist
    target_y = rand() % (LINES - 3); // dass y im fenster ist
}

void vogel_speed()
{
   if (px < target_x)
    {
        px += speed;
        if (px > target_x) px = target_x;
    }
    else if (px > target_x)
    {
        px -= speed;
        if (px < target_x) px = target_x;
    }

    if (py < target_y)
    {
        py += speed;
        if (py > target_y) py = target_y;
    }
    else if (py > target_y)
    {
        py -= speed;
        if (py < target_y) py = target_y;
    }

    if (px == target_x && py == target_y)
    {
        generate_random_coordinates();
    }
}