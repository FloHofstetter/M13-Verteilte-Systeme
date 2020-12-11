#include "main.h"
#include "showCells.h"
#include <stdio.h>
#include "followingCellState.h"
#include "followingFieldState.h"
#include <string.h>
#include <unistd.h>

#define MATCHFIELD 10
#define MATCHFIELD_H MATCHFIELD
#define MATCHFIELD_W MATCHFIELD

int main()
{
    int cellsActualState[MATCHFIELD_H][MATCHFIELD] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int cellsNextState[MATCHFIELD_W][MATCHFIELD_H];


    for (int i=0; i<100; i++)
    {
        show_cells(MATCHFIELD_H, MATCHFIELD_W, cellsActualState);
        followingFieldState(MATCHFIELD_W, MATCHFIELD_H, &cellsActualState, &cellsNextState);
        memcpy(&cellsActualState, &cellsNextState, MATCHFIELD_W * MATCHFIELD_H * sizeof(int));
        usleep(250*1e3); // ms
    }
    return 0;
}
