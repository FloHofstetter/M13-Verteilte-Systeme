#include <stdio.h>
#include "followingCellState.h"

void followingFieldState(int h, int w, int (*cellsIn)[w], int (*cellsOut)[w])
{
    int x, y;
    for (y=0; y < h; y++)
    {
        for (x=0; x < w; x++)
        {
            int neighbours[8] =
            {
                cellsIn[y - 1][x - 1],  // (x-1, y-1)
                cellsIn[y - 1][x - 0],  // (x-0, y-1)
                cellsIn[y - 1][x + 1],  // (x+1, y-1)
                cellsIn[y + 0][x - 1],  // (x-1, y+0)
                cellsIn[y + 0][x + 1],  // (x+1, y+0)
                cellsIn[y + 1][x - 1],  // (x-1, y+1)
                cellsIn[y + 1][x + 0],  // (x+0, y+1)
                cellsIn[y + 1][x + 1],  // (x+1, y+1)
            };
            printf("%i\n", cellsIn[y-1][x-1]);
            cellsOut[y][x] = followingCellState(&cellsIn[y][x], &neighbours);
        }
        printf("\n");
    }
}
