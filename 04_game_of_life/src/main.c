#include "main.h"
#include "showCells.h"
#include <stdio.h>
#include "followingCellState.h"
#include "followingFieldState.h"
#include <string.h>

#define MATCHFIELD 5
#define MATCHFIELD_H MATCHFIELD
#define MATCHFIELD_W MATCHFIELD

int main()
{
    int cells[MATCHFIELD_H][MATCHFIELD] = {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
    };

    int cellsCopy[MATCHFIELD_W][MATCHFIELD_H];
    // memcpy(&cellsCopy, &cells, MATCHFIELD_W * MATCHFIELD_H * sizeof(int));

    followingFieldState(MATCHFIELD_W, MATCHFIELD_H, &cells, &cellsCopy);

    show_cells(MATCHFIELD_H, MATCHFIELD_W, cellsCopy);

    // int neighbours[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    // int actState = 0;
    // actState = followingCellState(&actState, &neighbours);
    // printf("State: %i", actState);


    return 0;
}
