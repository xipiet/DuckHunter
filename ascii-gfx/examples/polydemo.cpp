// Polygon demo
// (c) 2022 by Stefan Roettger

#include "gfx.h"
#include "scrollarea.h"
#include "polygon.h"

int main(void)
{
   // init ASCII gfx
   init_gfx();
   init_color();

   // game area setup
   int sx = 80, sy = 30;
   set_area_size(sx, sy);
   set_window_size(COLS, LINES);

   // vertex array
   Vec2 v[] = {0,-12, 7,-6, 3,-6, 13,0, 8,0, 17,6, // right tree top side
               -17,6, -8,0, -13,0, -3,-6, -7,-6, // left tree top side
               2,6, 2,12, -2,12, -2,6, // tree trunk
               -20,10, 20,10, 0,-20}; // paper plane

   // interleaved polygon index array
   static const int n = 4; // number of polygons
   int p[3*n] = {0,11,3, 11,4,5, 15,3,2, 15,3,1}; // start index, run-length, and color index

   // object structure
   struct Object
   {
      Mat3 M; // transformation matrix
      Vec2 T; // initial translation
      float R; // initial rotation
      float S; // initial scaling
      int idx; // polygon start index
      int num; // polygon run length
   };

   // object array
   static const int m = 5; // number of transformed objects
   Object O[m] =
   {
      mat3(), vec2(sx/2, sy/6), 90, 0.3, 2,1,
      mat3(), vec2(0.1*sx, 0.8*sy), 0, 0.3, 0,2,
      mat3(), vec2(0.85*sx, 0.7*sy), 0, 0.5, 0,2,
      mat3(), vec2(sx/2, sy/2), 0, 1, 0,2,
      mat3(), vec2(sx/2, sy/3+2), 0, 0.2, 3,1
   };

   // transform objects according to their initial position, rotation, and scale
   for (int o=0; o<m; o++)
   {
      replace(O[o].M);
      translate(O[o].T);
      rotate(O[o].R);
      scale(O[o].S);
      O[o].M=top();
   }

   // game loop
   do
   {
      // clear game area
      clear_area();

      // render game area
      render_frame(0, 0, sx-1, sy-1);

      // render objects
      for (int o=0; o<m; o++)
      {
         // use transformation matrix of each object
         replace(O[o].M);

         // render polygons
         int idx = O[o].idx;
         int num = O[o].num;
         for (int i=idx; i<idx+num; i++)
            render_polygon(p[3*i+1], &v[p[3*i]], ACS_CKBOARD | COLOR_PAIR(p[3*i+2]));
      }

      // update game area objects
      replace(O[0].M);
      translate(vec2(300, 0));
      rotate(3);
      translate(vec2(-300, 0));
      O[0].M=top();
      static int angle = 0;
      replace(O[4].M);
      translate(0, -5);
      angle += 10;
      if (angle%720 < 330) rotate(10);
      else rotate(-10);
      O[4].M=top();

      // update log
      log_clear();
      log_text("transformation matrix:");
      log_mat3(top());
      log_text("");
      log_text("translation vector:");
      log_vec2(translation());
      log_text("");
      log_text("rotation angle:");
      log_float(rotation());
      log_text("");
      log_text("scaling factor:");
      log_float(scaling());

      // scroll game area
      center_window(sx/2, sy/2);

      // refresh screen
      refresh();

      // wait until next frame
      msleep(100); // 100 ms = 10 fps
   }
   while (tolower(getch()) != 'q');

   // release allocated memory
   release_area();

   // exit ASCII gfx
   exit_gfx();

   return(0);
}
