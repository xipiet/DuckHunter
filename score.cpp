#include <ncurses.h>
#include "module.h"
#include "gamestate.h"

int score = 0;

void increase_score()
{
    score++;
}

int get_score()
{
    return score;
}

void render_score()
{
    mvprintw(0, COLS - 10, "Score: %d", get_score());
}

void reset_score()
{
    score = 0;
}

void write_to_file()
{
    FILE *fptr;
    fptr = fopen("scores.txt", "a");

    int score = get_score();
    fprintf(fptr, "\nScore: %d", score);

    fclose(fptr);
}

void show_highscores()
{
    clear();
    print_current_state();
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
            set_state(GAME_INTRO);
            break;
        }
    }
}