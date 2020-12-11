#include <stdio.h>
#include "followingCellState.h"
#define CELLNEIGHBOURS 8

void followingFieldState(int h, int w, int (*cellsIn)[w], int (*cellsOut)[w])
{
    int x, y;
    int neighbours[8];
    int neighbour = 0;
    int neighbourY[8] = {-1, -1, -1, +0, +0, +1, +1, +1};
    int neighbourX[8] = {-1, +0, +1, -1, +1, -1, +0, +1};
    for (y=0; y < h; y++)
    {
        for (x=0; x < w; x++)
        {
            for (neighbour=0; neighbour < CELLNEIGHBOURS; neighbour++)
            {
                int neighbourXCoordinate = x + neighbourX[neighbour];
                // Left end is right end.
                if (neighbourXCoordinate < 0)
                {
                    neighbourXCoordinate += w;
                }
                // Right end is left end.
                else if (neighbourXCoordinate >= w)
                {
                    neighbourXCoordinate = 0;
                }
                int neighbourYCoordinate = y + neighbourY[neighbour];
                // Upper end is lower end.
                if (neighbourYCoordinate < 0)
                {
                    neighbourYCoordinate += h;
                }
                // Lower end is upper end.
                else if (neighbourYCoordinate >= h)
                {
                    neighbourYCoordinate = 0;
                }
                neighbours[neighbour] = cellsIn[neighbourYCoordinate][neighbourXCoordinate];
            }

        cellsOut[y][x] = followingCellState(&cellsIn[y][x], &neighbours);
        }
    }
}
