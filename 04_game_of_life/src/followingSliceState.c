#include "followingCellState.h"
#define CELLNEIGHBOURS 8

void followingSliceState(int w, int h, int (*cellsIn)[w], int (*cellsOut)[w][h])
{

    int x, y;
    int neighbours[8];
    int neighbour = 0;
    int neighbourY[8] = {-1, -1, -1, +0, +0, +1, +1, +1};
    int neighbourX[8] = {-1, +0, +1, -1, +1, -1, +0, +1};

    for (y=1; y < h - 2; y++)
    {
        for (x=1; x < h - 2; x++)
        {
            for (neighbour=0; neighbour < CELLNEIGHBOURS; neighbour++)
            {
                int neighbourXCoordinate = x + neighbourX[neighbour];
                int neighbourYCoordinate = y + neighbourY[neighbour];
                neighbours[neighbour] = cellsIn[neighbourYCoordinate][neighbourXCoordinate];
                (*cellsOut)[y][x] = followingCellState(&cellsIn[y][x], &neighbours);
            }
        }
    }
}
