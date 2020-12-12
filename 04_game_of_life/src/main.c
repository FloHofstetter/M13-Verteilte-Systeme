#include "main.h"
#include "showCells.h"
#include <stdio.h>
#include "followingCellState.h"
#include "followingFieldState.h"
#include "fieldSlice.h"
#include <string.h>
#include <unistd.h>
#include <mpi.h>

#define MATCHFIELD 10
#define MATCHFIELD_H MATCHFIELD
#define MATCHFIELD_W MATCHFIELD

int main()
{
    int cellsActualState[MATCHFIELD_H][MATCHFIELD_W] =
    {
            {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int cellsNextState[MATCHFIELD_W][MATCHFIELD_H];

    int cellSlice[MATCHFIELD_H/2 + 2][MATCHFIELD_W/2 + 2];

    fieldSlice(MATCHFIELD_H, MATCHFIELD_W, 0, 0, 2, &cellsActualState, &cellSlice);
    for(int y=0; y < 5; y++)
    {
        for(int x=0; x < 5; x++)
        {
            printf("Y: %i, X: %i, : %i\n",y, x, cellSlice[y][x]);
        }
    }

}


    /*
    for (int i=0; i<100; i++)
    {
        show_cells(MATCHFIELD_H, MATCHFIELD_W, cellsActualState);
        followingFieldState(MATCHFIELD_W, MATCHFIELD_H, &cellsActualState, &cellsNextState);
        memcpy(&cellsActualState, &cellsNextState, MATCHFIELD_W * MATCHFIELD_H * sizeof(int));
        usleep(250*1e3); // ms
    }
     */
