#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void show_cells (int w, int h, int (*cells)[w])
{
    int x, y;

    printf("\033[2J");
    printf("\033[H");
    for (y=0; y < h; y++)
    {
        for (x=0; x < w; x++)
        {
            printf(cells[y][x] ? "\033[07m  \033[m" : "\033[44m  \033[m");
        }
        printf("\n");
    }
    fflush(stdout);
}
