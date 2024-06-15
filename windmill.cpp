#include "module.h"
#include <ncurses.h>

#define PROPELLER_FRAMES 4


const char* propeller_frames[PROPELLER_FRAMES][5] = {
    { "     |     ", "     |     ", "     |     ", "     |     ", "     |     " },
    { "    / \\    ", "   /   \\   ", "  /     \\  ", " /       \\ ", "/         \\" },
    { "     -     ", "     -     ", "     -     ", "     -     ", "     -     " },
    { " \\         /", "  \\       / ", "   \\     /  ", "    \\   /   ", "     \\ /    " }
};

int current_frame = 0;
int windmill_x = 40;  // x der Windmühle
int windmill_y = 10;  // y der Windmühle


void init_windmill() {
    current_frame = 0;
}

void update_windmill() {
    current_frame = (current_frame + 1) % PROPELLER_FRAMES;
}


void render_windmill() {
   
    mvprintw(windmill_y + 5, windmill_x, "     |     ");
    mvprintw(windmill_y + 6, windmill_x, "     |     ");
    mvprintw(windmill_y + 7, windmill_x, "     |     ");
    mvprintw(windmill_y + 8, windmill_x, "    |-|    ");
    mvprintw(windmill_y + 9, windmill_x, "    |_|    ");
    mvprintw(windmill_y + 10, windmill_x, "   /   \\   ");
    mvprintw(windmill_y + 11, windmill_x, "  /     \\  ");
    mvprintw(windmill_y + 12, windmill_x, " /       \\ ");

   
    for (int i = 0; i < 5; i++) {
        mvprintw(windmill_y + i, windmill_x, "%s", propeller_frames[current_frame][i]);
    }
}