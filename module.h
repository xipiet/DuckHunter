#ifndef MODULE_H
#define MODULE_H

#include <ncurses.h>

// Function declarations
void game_loop();
void print_bird(int y, int x, bool f);
void msleep(float ms);
void generate_random_coordinates();
void generate_random_start_position();

// Ammo management functions
void render_ammo();
void use_ammo();
void reload_ammo();
int get_ammo();
void add_ammo(int amount);

#endif
