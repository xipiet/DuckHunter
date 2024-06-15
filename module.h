#ifndef MODULE_H
#define MODULE_H

#include <ncurses.h>

extern int px;
extern int py;
extern int target_x;
extern int target_y;
extern float speed;
extern float beschleunigung;

//funktionen
void game_loop();
void show_start_screen();

void print_bird(int y, int x, bool f);
void msleep(float ms);
void generate_random_coordinates();
void generate_random_start_position();

//ammo
void render_ammo();
void use_ammo();
void reload_ammo();
int get_ammo();
void add_ammo(int amount);

//score
void increase_score();
int get_score();
void render_score();
void reset_score();
void write_to_file();
void show_highscores();

//windmill
void init_windmill();
void update_windmill();
void render_windmill();

//vogels
void generate_random_start_position();
void generate_random_coordinates();
void vogel_speed();
#endif
