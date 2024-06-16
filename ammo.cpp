#include <ncurses.h>
#include "module.h"


int MAX_AMMO = 5;
int ammo = MAX_AMMO;

void render_ammo()
{
    for (int i = 0; i < MAX_AMMO; i++)
    {
        if (i < ammo)
        {
            mvprintw(LINES - 2, COLS - 2 - i * 3, " | ");
            mvprintw(LINES - 1, COLS - 2 - i * 3, "|_|");
        }
        else
        {
            mvprintw(LINES - 2, COLS - 2 - i * 3, "   ");
            mvprintw(LINES - 1, COLS - 2 - i * 3, "   ");
        }
    }
}

void use_ammo()
{
    if (ammo > 0)
    {
        ammo--;
    }
}

void reload_ammo()
{
    ammo = MAX_AMMO;
}

void add_ammo(int amount)
{
    ammo += amount;
    if (ammo > MAX_AMMO)
    {
        ammo = MAX_AMMO;
    }
}

int get_ammo()
{
    return ammo;
}