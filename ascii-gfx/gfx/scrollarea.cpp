// NCurses side-scrolling area
// (c) 2020 by Stefan Roettger

#include "scrollarea.h"

#include <stdarg.h>
#include "gridfont.h"

static int sizex = 0, sizey = 0; // the size of the scrollable area
static int winx = 0, winy = 0; // the size of the displayed window
static int offx = 0, offy = 0; // the offset of the displayed window
static int scrollx = 0, scrolly = 0; // the actual scrolled position

static WINDOW *W = NULL; // the drawing window
static int *area = NULL; // the scrollable area
static int *window = NULL; // the displayed window
static bool window_change = false; // the displayed window was changed
static int window_border_ch = -1; // the displayed window border
static int coordx = 0, coordy = 0; // the cell coordinate offset
static int mode = 0; // the cell modification mode

struct SpriteType
{
   int x, y;
   int sx, sy;
   bool window;
   bool hidden;
   bool background;
   bool parallax;
   float dx, dy;
   int *data;
   bool own;
};

static const int sprites = 64; // the number of supported sprites
static SpriteType sprite[sprites] = {{0}}; // the sprite data
static int sprite_begin = 0; // the begin of the active sprite range
static int sprite_end = -1; // the end of the active sprite range

// set the drawing window
void set_drawing_window(WINDOW *w)
{
   if (w != W)
   {
      W = w;
      window_change = true;
   }
}

// create a scrollable canvas area
void set_area_size(int sx, int sy)
{
   if (sx < 1 || sy < 1) return;

   sizex = sx;
   sizey = sy;

   if (area) delete[] area;
   area = new int[sx*sy];

   clear_area();
   window_change = true;

   init_grid_font();
}

// is a scrollable canvas area available?
bool has_area()
{
   return(area);
}

// get the width of the scrollable area
int get_area_width()
{
   return(sizex);
}

// get the height of the scrollable area
int get_area_height()
{
   return(sizey);
}

// set the size of the displayed window
void set_window_size(int sx, int sy)
{
   if (sx < 1 || sy < 1) return;
   if (window && sx == winx && sy == winy) return;

   winx = sx;
   winy = sy;

   if (window) delete[] window;
   window = new int[winx*winy];

   window_change = true;
}

// is a displayed window available?
bool has_window()
{
   return(window);
}

// get the width of the displayed window
int get_window_width()
{
   return(winx);
}

// get the height of the displayed window
int get_window_height()
{
   return(winy);
}

// set the offset of the displayed window
void set_window_offset(int ox, int oy)
{
   if (ox == offx && oy == offy) return;

   offx = ox;
   offy = oy;

   window_change = true;
}

// clear the scrollable area
void clear_area(int ch)
{
   if (!area) return;
   if (ch < 0) return;

   int n = sizex * sizey;
   for (int i=0; i<n; i++)
      area[i] = ch;
}

// set the border of the scrollable area
void set_area_border(int ch)
{
   for (int i=0; i<sizex; i++)
   {
      set_cell(i, 0, ch);
      set_cell(i, sizey-1, ch);
   }

   for (int j=0; j<sizey; j++)
   {
      set_cell(0, j, ch);
      set_cell(sizex-1, j, ch);
   }
}

// set the border of the displayed window
void set_window_border(int ch)
{
   window_border_ch = ch;
}

// get the cell character at position (x, y)
int get_cell(int x, int y)
{
   if (!area) return(-1);

   x += coordx;
   y += coordy;

   if (x < 0) return(-1);
   else if (x >= sizex) return(-1);

   if (y < 0) return(-1);
   else if (y >= sizey) return(-1);

   int idx = x+y*sizex;

   return(area[idx]);
}

// set the cell at position (x, y) to character ch
void set_cell(int x, int y, int ch)
{
   if (!area) return;
   if (ch < 0) return;

   x += coordx;
   y += coordy;

   if (x < 0) return;
   else if (x >= sizex) return;

   if (y < 0) return;
   else if (y >= sizey) return;

   int idx = x+y*sizex;

   if (mode)
      if (area[idx] != ' ') return;

   area[idx] = ch;
}

// set the cell coordinate offset
void set_cell_offset(int x, int y)
{
   coordx = x;
   coordy = y;
}

// set the cell modification mode
void set_cell_mode(bool retain)
{
   mode = retain;
}

// get the cell area at top-left position (x, y) with size (sx, sy)
int *get_cell_area(int x, int y,
                   int sx, int sy,
                   int ch)
{
   if (sx < 1 || sy < 1) return(NULL);

   int *cells = new int[sx*sy];

   for (int j=0; j<sy; j++)
   {
      for (int i=0; i<sx; i++)
      {
         int c = get_cell(x+i, y+j);
         if (c == ch) c = -1;
         cells[i+j*sx] = c;
      }
   }

   return(cells);
}

// fill a cell area at top-left position (x, y) with size (sx, sy)
void fill_cell_area(int x, int y,
                    int sx, int sy,
                    int ch)
{
   int c = ch;
   if (c < 0) c = ACS_CKBOARD;

   for (int j=0; j<sy; j++)
   {
      for (int i=0; i<sx; i++)
      {
         set_cell(x+i, y+j, c);
      }
   }
}

// render a cell area at top-left position (x, y) with size (sx, sy)
void render_cell_area(int x, int y,
                      int sx, int sy,
                      const int *data)
{
   if (!data) return;

   for (int j=0; j<sy; j++)
   {
      for (int i=0; i<sx; i++)
      {
         int ch = data[i+j*sx];
         set_cell(x+i, y+j, ch);
      }
   }
}

// render a text area at top-left position (x, y)
int render_text_area(int x, int y,
                     const char *text)
{
   int lines = 0;
   int start = x;
   int count = strlen(text);

   for (int i=0; i<count; i++)
   {
      int ch = text[i];

      if (ch != '\n')
      {
         set_cell(x, y, ch);
         x++;
      }
      else
      {
         lines++;
         x = start;
         y++;
      }
   }

   return(lines);
}

// render a formatted text at position (x, y)
int render_text_format(int x, int y,
                       const char *format, ...)
{
   va_list argp;
   va_start(argp, format);
   int n = vsnprintf(NULL, 0, format, argp);
   va_end(argp);

   char *text = get_string_buffer(n);
   va_start(argp, format);
   vsnprintf(text, n+1, format, argp);
   va_end(argp);

   return(render_text_area(x, y, text));
}

// render a grid font character at top-left position (x, y)
void render_grid_char(int x, int y, int ch)
{
   int sx = get_grid_char_cols();
   int sy = get_grid_char_lines();
   int *data = get_grid_char_data(ch);

   render_cell_area(x, y, sx, sy, data);
}

// render a text string with grid font characters at top-left position (x, y)
void render_grid_text(int x, int y,
                      const char *text)
{
   int start = x;

   int sx = get_grid_char_cols();
   int sy = get_grid_char_lines();

   while (*text != '\0')
   {
      if (*text != '\n')
      {
         int *data = get_grid_char_data(*text);
         render_cell_area(x, y, sx, sy, data);
         x += sx;
      }
      else
      {
         x = start;
         y += sy;
      }

      text++;
   }
}

// render a line from position (x1, y1) to (x2, y2)
void render_line(int x1, int y1, int x2, int y2,
                 int ch)
{
   int dx, dy;
   int ix, iy;

   // determine x increment
   if (x2 >= x1)
   {
      dx = x2-x1;
      ix = 1;
   }
   else
   {
      dx = x1-x2;
      ix = -1;
   }

   // determine y increment
   if (y2 >= y1)
   {
      dy = y2-y1;
      iy = 1;
   }
   else
   {
      dy = y1-y2;
      iy = -1;
   }

   int pdx, pdy;
   int ddx, ddy;
   int slow, fast;

   // determine fast direction
   if (dx > dy)
   {
      // x is fast direction
      pdx = ix; pdy = 0;
      ddx = ix; ddy = iy;
      slow = dy; fast = dx;
   }
   else
   {
      // y is fast direction
      pdx = 0; pdy = iy;
      ddx = ix; ddy = iy;
      slow = dx; fast = dy;
   }

   // determine line character
   int c = ch;
   if (c < 0)
   {
      if (dx > 2*dy) c = ACS_HLINE;
      else if (dy > 2*dx) c = ACS_VLINE;
      else if (ix*iy > 0) c = '\\';
      else c = '/';
   }

   // loop along fast direction
   int x = x1, y = y1;
   int err = fast;
   int i = 0;
   while (TRUE)
   {
      set_cell(x, y, c);

      if (i++ == fast)
         break;

      err -= slow<<1;

      if (err < 0)
      {
         err += fast<<1;
         x += ddx;
         y += ddy;
      }
      else
      {
         x += pdx;
         y += pdy;
      }
   }
}

// render a frame from position (x1, y1) to (x2, y2)
void render_frame(int x1, int y1, int x2, int y2,
                  int ch)
{
   if (x2 > x1 && y2 > y1)
   {
      if (x2 - x1 > 1)
      {
         render_line(x1+1, y1, x2-1, y1, ch);
         render_line(x1+1, y2, x2-1, y2, ch);
      }

      if (y2 - y1 > 1)
      {
         render_line(x1, y1+1, x1, y2-1, ch);
         render_line(x2, y1+1, x2, y2-1, ch);
      }

      set_cell(x1, y1, ch>=0?ch:ACS_ULCORNER);
      set_cell(x2, y1, ch>=0?ch:ACS_URCORNER);
      set_cell(x1, y2, ch>=0?ch:ACS_LLCORNER);
      set_cell(x2, y2, ch>=0?ch:ACS_LRCORNER);
   }
}

// render a circle at center position (xc, yc) with radius r
void render_circle(int xc, int yc, int r,
                   int ch, double aspect)
{
   render_ellipse(xc, yc, aspect*r + 0.5, r, ch, aspect);
}

// helper for ellipse rendering
void render_points(int xc, int yc, int x, int y,
                   int ax, int ay, double aspect,
                   int ch)
{
   int c = ch;
   if (c < 0)
   {
      if (2*ay*x < aspect*ax*y) c = ACS_HLINE;
      else if (ay*x < 2*aspect*ax*y) c = '/';
      else c = ACS_VLINE;
   }

   set_cell(xc+x, yc+y, c);
   set_cell(xc-x, yc+y, c=='/'?'\\':c);
   set_cell(xc+x, yc-y, c=='/'?'\\':c);
   set_cell(xc-x, yc-y, c);
}

// render a ellipse at center position (xc, yc) with principle axis ax and ay
void render_ellipse(int xc, int yc, int ax, int ay,
                    int ch, double aspect)
{
   if (ax <= 0 || ay <= 0) return;

   int dx = ax*ax;
   int dy = ay*ay;
   int dx2 = 2*dx;
   int dy2 = 2*dy;

   {
      int x = 0, y = ay;
      int e = dy - dx*ay + (dx+2)/4;
      int ex = 0, ey = dx2*ay;

      render_points(xc, yc, x, y, ax, ay, aspect, ch);

      while (ex <= ey)
      {
         x++;
         ex += dy2;
         if (e >= 0)
         {
            y--;
            ey -= dx2;
            e -= ey;
         }
         e += dy + ex;

         render_points(xc, yc, x, y, ax, ay, aspect, ch);
      }
   }

   {
      int x = ax, y = 0;
      int e = dx - dy*ax + (dy+2)/4;
      int ex = dy2*ax, ey = 0;

      render_points(xc, yc, x, y, ax, ay, aspect, ch);

      while (ex >= ey)
      {
         y++;
         ey += dx2;
         if (e >= 0)
         {
            x--;
            ex -= dy2;
            e -= ex;
         }
         e += dx + ey;

         render_points(xc, yc, x, y, ax, ay, aspect, ch);
      }
   }
}

// flood-fill a cell area starting at position (x, y)
void flood_fill(int x, int y, int ch)
{
   if (mode) return;
   if (x < 0 || x >= sizex || y < 0 || y >= sizey) return;
   if (ch < 0) ch = ACS_CKBOARD;

   int c = get_cell(x, y);
   if (c == ch) return;
   set_cell(x, y, ch);

   if (get_cell(x-1, y) == c) flood_fill(x-1, y, ch);
   if (get_cell(x+1, y) == c) flood_fill(x+1, y, ch);
   if (get_cell(x, y-1) == c) flood_fill(x, y-1, ch);
   if (get_cell(x, y+1) == c) flood_fill(x, y+1, ch);
}

// flood-fill everything but a cell area starting at position (x, y)
void inverse_flood_fill(int x, int y, int ch)
{
   int c = get_cell(x, y);

   flood_fill(x, y, 0);

   for (int j=0; j<sizey; j++)
   {
      for (int i=0; i<sizex; i++)
      {
         if (get_cell(i, j) == c)
            flood_fill(i, j, ch);
      }
   }

   flood_fill(x, y, c);
}

// scroll the content of the canvas area up
void scroll_area_up()
{
   for (int j=1; j<sizey; j++)
      for (int i=0; i<sizex; i++)
         set_cell(i, j-1, get_cell(i, j));

   for (int i=0; i<sizex; i++)
      set_cell(i, sizey-1, ' ');
}

// scroll the content of the canvas area down
void scroll_area_down(int num)
{
   for (int j=sizey-2; j>=0; j--)
      for (int i=0; i<sizex; i++)
         set_cell(i, j+1, get_cell(i, j));

   for (int i=0; i<sizex; i++)
      set_cell(i, 0, ' ');
}

// scroll the content of the canvas area left
void scroll_area_left(int num)
{
   for (int i=1; i<sizex; i++)
      for (int j=0; j<sizey; j++)
         set_cell(i-1, j, get_cell(i, j));

   for (int j=0; j<sizey; j++)
      set_cell(sizex-1, j, ' ');
}

// scroll the content of the canvas area right
void scroll_area_right(int num)
{
   for (int i=sizex-2; i>=0; i--)
      for (int j=0; j<sizey; j++)
         set_cell(i+1, j, get_cell(i, j));

   for (int j=0; j<sizey; j++)
      set_cell(0, j, ' ');
}

// get the number of available sprite overlays
int get_sprite_num()
{
   return(sprites);
}

// enable a sprite overlay
void enable_sprite(int num,
                   int sx, int sy,
                   bool window,
                   bool own)
{
   if (num < 0 || num >= sprites) return;

   if (sprite_end < 0)
   {
      sprite_begin = sprites - 1;
      sprite_end = 0;
   }

   if (num < sprite_begin) sprite_begin = num;
   if (num > sprite_end) sprite_end = num;

   if (sprite[num].data && sprite[num].own)
      delete[] sprite[num].data;

   SpriteType s = {0, 0, sx, sy, window, false, false, false, 0, 0, NULL, !own};
   if (s.own) s.data = new int[sx*sy];
   sprite[num] = s;

   clear_sprite(num);
}

// is a sprite overlay enabled?
bool is_sprite_enabled(int num)
{
   if (num < 0 || num >= sprites) return(false);

   return(sprite[num].data);
}

// get the width of a sprite
int get_sprite_width(int num)
{
   if (num < 0 || num >= sprites) return(0);

   return(sprite[num].sx);
}

// get the height of a sprite
int get_sprite_height(int num)
{
   if (num < 0 || num >= sprites) return(0);

   return(sprite[num].sy);
}

// clear a sprite
void clear_sprite(int num, int ch)
{
   if (num < 0 || num >= sprites) return;
   if (!sprite[num].data) return;

   SpriteType *s = &sprite[num];

   int n = s->sx*s->sy;
   for (int i=0; i<n; i++)
      s->data[i] = ch;
}

// set the sprite data
void set_sprite_data(int num, int sx, int sy, int *data)
{
   if (num < 0 || num >= sprites) return;
   if (!sprite[num].data && sprite[num].own) return;
   if (!data) return;

   SpriteType *s = &sprite[num];

   if (sx != s->sx || sy != s->sy) return;

   if (s->own)
   {
      int n = s->sx*s->sy;
      for (int i=0; i<n; i++)
         s->data[i] = data[i];
   }
   else
   {
      s->data = data;
   }
}

// get the sprite data
int *get_sprite_data(int num)
{
   if (num < 0 || num >= sprites) return(NULL);

   return(sprite[num].data);
}

// set the sprite data by text string
void set_sprite_text(int num, const char *text,
                     int ch, bool interprete)
{
   if (num < 0 || num >= sprites) return;
   if (!sprite[num].data) return;

   SpriteType *s = &sprite[num];

   int *data = convert_char_text(text, s->sx, s->sy, ch, interprete);

   if (data)
   {
      int n = s->sx*s->sy;
      for (int i=0; i<n; i++) s->data[i] = data[i];
      delete[] data;
   }
}

// fill a sprite cell area
void fill_sprite_area(int num, int x, int y, int sx, int sy, int ch)
{
   if (num < 0 || num >= sprites) return;
   if (!sprite[num].data) return;

   SpriteType *s = &sprite[num];

   for (int j=0; j<sy; j++)
      for (int i=0; i<sx; i++)
         if (x+i >= 0 && x+i < s->sx && y+j >= 0 && y+j < s->sy)
            s->data[x+i+(y+j)*s->sx] = ch;
}

// set a sprite cell area
void set_sprite_area(int num, int x, int y, int sx, int sy, const int *data)
{
   if (num < 0 || num >= sprites) return;
   if (!sprite[num].data) return;
   if (!data) return;

   SpriteType *s = &sprite[num];

   for (int j=0; j<sy; j++)
      for (int i=0; i<sx; i++)
         if (x+i >= 0 && x+i < s->sx && y+j >= 0 && y+j < s->sy)
         {
            int ch = data[i+j*sx];
            if (ch >= 0) s->data[x+i+(y+j)*s->sx] = ch;
         }
}

// print a sprite text area
int print_sprite_text(int num,
                      int x, int y,
                      const char *text)
{
   if (num < 0 || num >= sprites) return(0);
   if (!sprite[num].data) return(0);
   if (!text) return(0);

   SpriteType *s = &sprite[num];

   int lines = 0;
   int start = x;
   int count = strlen(text);

   for (int i=0; i<count; i++)
   {
      int ch = text[i];

      if (ch != '\n')
      {
         if (x >= 0 && x < s->sx && y >= 0 && y < s->sy)
            s->data[x+y*s->sx] = ch;
         x++;
      }
      else
      {
         lines++;
         x = start;
         y++;
      }
   }

   return(lines+1);
}

// print a sprite grid font character
void print_sprite_grid_char(int num,
                            int x, int y,
                            int ch)
{
   int sx = get_grid_char_cols();
   int sy = get_grid_char_lines();
   const int *data = get_grid_char_data(ch);

   set_sprite_area(num, x, y, sx, sy, data);
}

// print a sprite text string with grid font characters
void print_sprite_grid_text(int num,
                            int x, int y,
                            const char *text)
{
   int start = x;

   int sx = get_grid_char_cols();
   int sy = get_grid_char_lines();

   while (*text != '\0')
   {
      if (*text != '\n')
      {
         int *data = get_grid_char_data(*text);
         set_sprite_area(num, x, y, sx, sy, data);
         x += sx;
      }
      else
      {
         x = start;
         y += sy;
      }

      text++;
   }
}

// mirror the sprite horizontally
void mirror_sprite_horizontal(int num, bool flip)
{
   if (num < 0 || num >= sprites) return;
   if (!sprite[num].data) return;

   SpriteType *s = &sprite[num];

   for (int i=0; i<s->sx/2; i++)
      for (int j=0; j<s->sy; j++)
      {
         int c1 = s->data[i+j*s->sx];
         int c2 = s->data[s->sx-1-i+j*s->sx];

         if (flip)
         {
            if ((c1 & A_CHARTEXT) == '/') c1 = '\\' | (c1 & (~A_CHARTEXT));
            else if ((c1 & A_CHARTEXT) == '\\') c1 = '/' | (c1 & (~A_CHARTEXT));
            if ((c2 & A_CHARTEXT) == '/') c2 = '\\' | (c2 & (~A_CHARTEXT));
            else if ((c2 & A_CHARTEXT) == '\\') c2 = '/' | (c2 & (~A_CHARTEXT));
         }

         s->data[i+j*s->sx] = c2;
         s->data[s->sx-1-i+j*s->sx] = c1;
      }
}

// mirror the sprite vertically
void mirror_sprite_vertical(int num, bool flip)
{
   if (num < 0 || num >= sprites) return;
   if (!sprite[num].data) return;

   SpriteType *s = &sprite[num];

   for (int j=0; j<s->sy/2; j++)
      for (int i=0; i<s->sx; i++)
      {
         int c1 = s->data[i+j*s->sx];
         int c2 = s->data[i+(s->sy-1-j)*s->sx];

         if (flip)
         {
            if ((c1 & A_CHARTEXT) == '_') c1 = ACS_S1 | (c1 & (~A_CHARTEXT));
            else if ((c1 & A_CHARTEXT) == ACS_S1) c1 = '_' | (c1 & (~A_CHARTEXT));
            else if ((c1 & A_CHARTEXT) == '/') c1 = '\\' | (c1 & (~A_CHARTEXT));
            else if ((c1 & A_CHARTEXT) == '\\') c1 = '/' | (c1 & (~A_CHARTEXT));
            if ((c2 & A_CHARTEXT) == '_') c2 = ACS_S1 | (c2 & (~A_CHARTEXT));
            else if ((c2 & A_CHARTEXT) == ACS_S1) c2 = '_' | (c2 & (~A_CHARTEXT));
            else if ((c2 & A_CHARTEXT) == '/') c2 = '\\' | (c2 & (~A_CHARTEXT));
            else if ((c2 & A_CHARTEXT) == '\\') c2 = '/' | (c2 & (~A_CHARTEXT));
         }

         s->data[i+j*s->sx] = c2;
         s->data[i+(s->sy-1-j)*s->sx] = c1;
      }
}

// scroll the sprite up
void scroll_sprite_up(int num)
{
   if (num < 0 || num >= sprites) return;
   if (!sprite[num].data) return;

   SpriteType *s = &sprite[num];

   for (int j=1; j<s->sy; j++)
      for (int i=0; i<s->sx; i++)
         s->data[i+(j-1)*s->sx] = s->data[i+j*s->sx];

   for (int i=0; i<s->sx; i++)
      s->data[i+(s->sy-1)*s->sx] = -1;
}

// scroll the sprite down
void scroll_sprite_down(int num)
{
   if (num < 0 || num >= sprites) return;
   if (!sprite[num].data) return;

   SpriteType *s = &sprite[num];

   for (int j=s->sy-2; j>=0; j--)
      for (int i=0; i<s->sx; i++)
         s->data[i+(j+1)*s->sx] = s->data[i+j*s->sx];

   for (int i=0; i<s->sx; i++)
      s->data[i] = -1;
}

// scroll the sprite left
void scroll_sprite_left(int num)
{
   if (num < 0 || num >= sprites) return;
   if (!sprite[num].data) return;

   SpriteType *s = &sprite[num];

   for (int i=1; i<s->sx; i++)
      for (int j=0; j<s->sy; j++)
         s->data[i-1+j*s->sx] = s->data[i+j*s->sx];

   for (int j=0; j<s->sy; j++)
      s->data[s->sx-1+j*s->sx] = -1;
}

// scroll the sprite right
void scroll_sprite_right(int num)
{
   if (num < 0 || num >= sprites) return;
   if (!sprite[num].data) return;

   SpriteType *s = &sprite[num];

   for (int i=s->sx-2; i>=0; i--)
      for (int j=0; j<s->sy; j++)
         s->data[i+1+j*s->sx] = s->data[i+j*s->sx];

   for (int j=0; j<s->sy; j++)
      s->data[j*s->sx] = -1;
}

// set the sprite position
void set_sprite_position(int num, int x, int y)
{
   if (num < 0 || num >= sprites) return;

   SpriteType *s = &sprite[num];

   s->x = x;
   s->y = y;
}

// center the sprite position
void center_sprite_position(int num, int x, int y)
{
   if (num < 0 || num >= sprites) return;

   SpriteType *s = &sprite[num];

   set_sprite_position(num, x - s->sx/2, y - s->sy/2);
}

// get the sprite position
void get_sprite_position(int num, int *x, int *y)
{
   if (num < 0 || num >= sprites) return;

   SpriteType *s = &sprite[num];

   *x = s->x;
   *y = s->y;
}

// hide a sprite
void hide_sprite(int num)
{
   if (num < 0 || num >= sprites) return;

   SpriteType *s = &sprite[num];

   s->hidden = true;
}

// show a sprite
void show_sprite(int num)
{
   if (num < 0 || num >= sprites) return;

   SpriteType *s = &sprite[num];

   s->hidden = false;
}

// make background sprite
void background_sprite(int num, bool background)
{
   if (num < 0 || num >= sprites) return;

   SpriteType *s = &sprite[num];

   s->background = background;
}

// make parallax sprite
void parallax_sprite(int num, float dx, float dy)
{
   if (num < 0 || num >= sprites) return;

   SpriteType *s = &sprite[num];

   s->parallax = true;
   s->dx = dx;
   s->dy = dy;
}

// detect a sprite collision with a non-empty canvas area
bool detect_area_collision(int num, int ch)
{
   if (num < 0 || num >= sprites) return(false);
   if (!sprite[num].data) return(false);

   SpriteType *s = &sprite[num];

   for (int y=0; y<s->sy; y++)
      for (int x=0; x<s->sx; x++)
      {
         int c1 = s->data[x+y*s->sx];
         int c2 = get_cell(s->x+x, s->y+y);

         if (c1 < 0 || c2 < 0) continue; // skip transparent areas

         if (c2 != ch && c2 != ' ') // colliding with non-empty area
            return(true);
      }

   return(false);
}

// detect a sprite touch with a non-empty canvas area
bool detect_area_touch(int num, int dx, int dy, int ch)
{
   if (num < 0 || num >= sprites) return(false);

   if (detect_area_collision(num, ch)) return(false);

   SpriteType *s = &sprite[num];

   int x = s->x;
   int y = s->y;

   s->x += dx;
   s->y += dy;

   bool touch = detect_area_collision(num, ch);

   s->x = x;
   s->y = y;

   return(touch);
}

// detect a sprite collision with a non-transparent area of another sprite
bool detect_sprite_collision(int num, int spr)
{
   if (num < 0 || num >= sprites) return(false);
   if (spr < 0 || spr >= sprites) return(false);

   if (!sprite[num].data) return(false);
   if (!sprite[spr].data) return(false);

   SpriteType *s1 = &sprite[num];
   SpriteType *s2 = &sprite[spr];

   if (s1->x > s2->x+s2->sx-1) return(false); // no overlap in x-direction
   if (s1->x+s1->sx-1 < s2->x) return(false); // no overlap in x-direction
   if (s1->y > s2->y+s2->sy-1) return(false); // no overlap in y-direction
   if (s1->y+s1->sy-1 < s2->y) return(false); // no overlap in y-direction

   int dx = s1->x - s2->x;
   int dy = s1->y - s2->y;

   for (int y=0; y<s1->sy; y++)
      for (int x=0; x<s1->sx; x++)
      {
         int c1 = s1->data[x+y*s1->sx];

         if (c1 < 0) continue; // skip transparent sprite areas

         int px = x + dx;
         int py = y + dy;

         if (px >= 0 && px < s2->sx && py >= 0 && py < s2->sy)
         {
            int c2 = s2->data[px+py*s2->sx];

            if (c2 >= 0) // colliding with non-transparent area
               return(true);
         }
      }

   return(false);
}

// detect a sprite touch with a non-transparent area of another sprite
bool detect_sprite_touch(int num, int dx, int dy, int spr)
{
   if (num < 0 || num >= sprites) return(false);
   if (spr < 0 || spr >= sprites) return(false);

   if (detect_sprite_collision(num, spr)) return(false);

   SpriteType *s = &sprite[num];

   int x = s->x;
   int y = s->y;

   s->x += dx;
   s->y += dy;

   bool touch = detect_sprite_collision(num, spr);

   s->x = x;
   s->y = y;

   return(touch);
}

// bake the sprite into the canvas area
void bake_sprite(int num)
{
   if (num < 0 || num >= sprites) return;

   SpriteType *s = &sprite[num];

   render_cell_area(s->x, s->y, s->sx, s->sy, s->data);
}

// disable a sprite
void disable_sprite(int num)
{
   if (num < 0 || num >= sprites) return;

   if (sprite[num].data && sprite[num].own)
      delete[] sprite[num].data;

   SpriteType s = {0, 0, 0, 0, false, false, false, false, 0, 0, NULL, false};
   sprite[num] = s;
}

// disable all sprites
void disable_sprites()
{
   for (int i=0; i<sprites; i++)
      disable_sprite(i);

   sprite_begin = 0;
   sprite_end = -1;
}

// redraw the displayed window at top-left position (x, y)
void redraw_window(int x, int y)
{
   if (!area || !window) return;

   WINDOW *w = W?W:stdscr;

   bool reposition = true;

   // process each visible cell
   for (int j=0; j<winy; j++)
   {
      for (int i=0; i<winx; i++)
      {
         // get visible cell character
         int ch = get_cell(x+i, y+j);
         if (ch < 0) ch = ' ';

         // override visible character with sprite data
         for (int k=sprite_begin; k<=sprite_end; k++)
         {
            SpriteType *s = &sprite[k];

            if (s->data != NULL &&
                s->sx > 0 && s->sy > 0 &&
                !s->hidden)
            {
               int ax = i - s->x;
               int ay = j - s->y;

               if (!s->window)
               {
                  ax += x;
                  ay += y;

                  if (s->parallax)
                  {
                     ax += s->dx * x;
                     ay += s->dy * y;
                  }
               }

               if (ax >= 0 && ax < s->sx && ay >= 0 && ay < s->sy)
               {
                  int c = s->data[ax+ay*s->sx];
                  if (c >= 0)
                  {
                     if (!s->background || ch == ' ')
                     {
                        ch = c;
                        break;
                     }
                  }
               }
            }
         }

         // override visible character with window border
         if (window_border_ch >= 0)
            if (i == 0 || i == winx-1 || j == 0 || j == winy-1)
               ch = window_border_ch;

         // check for character change
         if (window_change || ch != window[i+j*winx])
         {
            // check for cursor repositioning
            if (reposition)
            {
               wmove(w, j+offy, i+offx);
               reposition = false;
            }

            // draw changed character
            waddch(w, ch);

            // save changed character
            window[i+j*winx] = ch;
         }
         else
         {
            reposition = true;
         }
      }

      reposition = true;
   }

   window_change = false;

   scrollx = x;
   scrolly = y;
}

// position the displayed window at center position (x, y)
void position_window(int x, int y)
{
   redraw_window(x - winx/2, y - winy/2);
}

// scroll the displayed window to top-left position (x, y)
void scroll_window(int x, int y, int deltax, int deltay, bool stop)
{
   if (stop)
   {
      int offx = 0, offy = 0;
      if (winx > sizex) offx = (winx - sizex + 1) / 2;
      if (winy > sizey) offy = (winy - sizey + 1) / 2;

      if ((x+deltax < scrollx && scrollx > 0) || scrollx-offx > sizex-winx) scrollx--;
      else if ((x-deltax > scrollx && scrollx < sizex-winx) || scrollx+offx < 0) scrollx++;

      if ((y+deltay < scrolly && scrolly > 0) || scrolly-offy > sizey-winy) scrolly--;
      else if ((y-deltay > scrolly && scrolly < sizey-winy) || scrolly+offy < 0) scrolly++;
   }
   else
   {
      if (x+deltax < scrollx) scrollx--;
      else if (x-deltax > scrollx) scrollx++;

      if (y+deltay < scrolly) scrolly--;
      else if (y-deltay > scrolly) scrolly++;
   }

   redraw_window(scrollx, scrolly);
}

// scroll the displayed window to center position (x, y)
void center_window(int x, int y, int deltax, int deltay, bool stop)
{
   scroll_window(x - winx/2, y - winy/2, deltax, deltay, stop);
}

// get the top-left position (x, y) of the scrolled window
void get_window(int *x, int *y)
{
   *x = scrollx;
   *y = scrolly;
}

// release allocated memory
void release_area()
{
   if (area) delete[] area;
   area = NULL;

   if (window) delete[] window;
   window = NULL;

   for (int i=0; i<sprites; i++)
      disable_sprite(i);

   release_grid_font();
}
