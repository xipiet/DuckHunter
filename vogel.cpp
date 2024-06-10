#include <ncurses.h>
#include "module.h"


void print_bird(int y, int x, bool f){
    mvprintw(y+0, x, "   _ _   ");
    mvprintw(y+1, x, " /( v )\\");
    mvprintw(y+2, x, "   ' '   ");
}
