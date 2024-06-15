#include <ncurses.h>
#include "module.h"

void show_highscores()
{
    clear();
    mvprintw(1, (COLS / 2), "Scores");

    FILE *fptr = fopen("scores.txt", "r");
    if (fptr == NULL)
    {
        mvprintw(2, (COLS / 2), "No scores available.");
    }
    else
    {
        char line[256];
        int line_num = 2;
        while (fgets(line, sizeof(line), fptr) != NULL)
        {
            mvprintw(line_num++, (COLS / 2), "%s", line);
        }
        fclose(fptr);
    }

    mvprintw(LINES - 2, (COLS / 2), "Press 'q' to return.");
    msleep(100);
    refresh();

    while (true)
    {
        int ch = getch();
        if (ch == 'q')
        {
            break;
        }
    }
}