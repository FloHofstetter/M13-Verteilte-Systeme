#include <stdio.h>

void showNumbers(int h, int w, int (*matrix)[h][w])
{
    for (int y=0; y < h; y++)
    {
        for(int x=0; x < w; x++)
        {
            printf("%i ", (*matrix)[y][x]);
        }
        printf("\n");
    }
}


