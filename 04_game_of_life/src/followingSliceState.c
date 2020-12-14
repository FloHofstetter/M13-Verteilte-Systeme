#include "followingCellState.h"
#include <stdio.h>
#define CELLNEIGHBOURS 8

void followingSliceState(int w, int h, int (*cellsIn)[w][h], int (*cellsOut)[w][h])
{

    int x, y;
    int neighbours[8];
    int neighbour = 0;
    int neighbourY[8] = {-1, -1, -1, +0, +0, +1, +1, +1};
    int neighbourX[8] = {-1, +0, +1, -1, +1, -1, +0, +1};

    for (y=1; y < h - 1; y++)
    {
        for (x=1; x < h - 1; x++)
        {
            for (neighbour=0; neighbour < CELLNEIGHBOURS; neighbour++)
            {
                int neighbourXCoordinate = x + neighbourX[neighbour];
                int neighbourYCoordinate = y + neighbourY[neighbour];
                neighbours[neighbour] = (*cellsIn)[neighbourYCoordinate][neighbourXCoordinate];
                (*cellsOut)[y][x] = followingCellState(&((*cellsIn)[y][x]), &neighbours);
                // printf("Y: %i X: %i, Val: %i\n", y, x, (*cellsOut)[y][x]);
            }
        }
    }
}
