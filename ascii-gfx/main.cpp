// ASCII GFX example
// (c) 2020 by Stefan Roettger

#include "gfx.h"
#include "gridfont.h"
#include "sound.h"

static int max_x = 0, max_y = 0; // screen size

int main(int argc, char *argv[])
{
   // init ASCII gfx
   init_gfx();
   init_color();

   // init sound
   sound_init();

   // print screen size
   // * LINES and COLS are predefined macros
   move(0, 0); // position cursor at origin
   printw("screen size is %dx%d\n", COLS, LINES);
   hline(ACS_HLINE, COLS);

   // get screen size
   // * a preceding & as used by the call-by-ref convention is not required
   // * since getmaxyx is a preprocessor macro
   getmaxyx(stdscr, max_y, max_x); // & not required

   // print centered text with 5x3 grid font
   const char text[] = "ASCII GFX!";
   int tx = max_x/2;
   int ty = (max_y-4)/2+1;
   init_grid_font();
   draw_grid_text(ty - get_grid_char_lines()/2, tx - strlen(text)*get_grid_char_cols()/2, text);

   // print help text
   const char help[] = "press q to quit!";
   use_attr_bold(); // enable bold attribute
   use_attr_blink(); // enable blink attribute
   use_color(2); // index 2 equals red
   mvprintw(max_y-2, 1, help);
   use_color(); // default equals white
   use_attr_normal(); // disable all attributes

   // draw horizontal line
   mvhline(max_y-3, 0, ACS_HLINE, max_x);

   // play WAV sound
   sound_play("boing.wav");

   // refresh screen
   refresh();

   // check for pressed keys
   int count = 0;
   while (tolower(getch()) != 'q')
   {
      // terminal bell
      // * beep every 3 seconds
      if (++count%30 == 0) beep();

      // wait 100ms
      msleep(100);
   }

   // exit sound
   sound_exit();

   // exit ASCII gfx
   exit_gfx();

   return(0);
}
