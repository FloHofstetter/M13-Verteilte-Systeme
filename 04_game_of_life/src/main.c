#include "main.h"
#include "showCells.h"
#include <stdio.h>
#include "followingCellState.h"
#include "followingSliceState.h"
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
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int cellsNextState[MATCHFIELD_W][MATCHFIELD_H];

    int cellSlice[MATCHFIELD_H/2 + 2][MATCHFIELD_W/2 + 2] = {0};
    int cellSlice2[MATCHFIELD_H/2 + 2][MATCHFIELD_W/2 + 2] = {0};

    fieldSlice(MATCHFIELD_H, MATCHFIELD_W, 0, 0, 2, &cellsActualState, &cellSlice);


    followingSliceState(MATCHFIELD_H/2 + 2, MATCHFIELD_W/2 + 2, &cellSlice, &cellSlice2);

    show_cells(MATCHFIELD_H/2 + 2, MATCHFIELD_W/2 + 2, cellSlice2);
    for (int y=0; y < 7; y++)
    {
        for(int x=0; x < 7; x++)
        {
            // printf("%i\n", cellSlice[y][x]);
        }
    }



    //show_cells(MATCHFIELD_H/2 + 2, MATCHFIELD_W/2 + 2, cellSlice);
    /*for(int y=0; y < 5; y++)
    {
        for(int x=0; x < 5; x++)
        {
            printf("Y: %i, X: %i, : %i\n",y, x, cellSlice[y][x]);
        }
    }*/

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
