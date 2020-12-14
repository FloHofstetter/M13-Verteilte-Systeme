#include "main.h"
#include "showCells.h"
#include <stdio.h>
#include "followingCellState.h"
#include "followingSliceState.h"
#include "fieldSlice.h"
#include <string.h>
#include <unistd.h>
#include <mpi.h>

// Matchfield
#define MATCHFIELD 10
#define MATCHFIELD_H MATCHFIELD
#define MATCHFIELD_W MATCHFIELD

// Slices
#define NSLICES 2
#define NSLICES_H NSLICES
#define NSLICES_W NSLICES
#define SLICE_FIELDS_H MATCHFIELD_H/NSLICES_H
#define SLICE_FIELDS_W MATCHFIELD_W/NSLICES_W

int main()
{
    int cellsActualState[MATCHFIELD_H][MATCHFIELD_W] =
    {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
            {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int cellsNextState[MATCHFIELD_W][MATCHFIELD_H];

    // Actual slices
    int (cellSliceActual[NSLICES_H][NSLICES_W])[SLICE_FIELDS_H + 2][SLICE_FIELDS_W + 2];
    for(int hSlices=0; hSlices < NSLICES_H; hSlices++)
    {
        for(int wSlices=0; wSlices < NSLICES_W; wSlices++)
        {
            for (int y=0; y < SLICE_FIELDS_H + 2; y++)
            {
                for(int x=0; x < SLICE_FIELDS_W + 2; x++)
                {
                    (cellSliceActual[hSlices][wSlices])[y][x] = -99;
                }
            }
        }
    }

    // Calculate new state for slices
    // Later here come MPI-Calls!
    for (int hSlice=0; hSlice < NSLICES_H; hSlice++)
    {
        for(int wSlice=0; wSlice < NSLICES_W; wSlice++)
        {
            fieldSlice(MATCHFIELD_H, MATCHFIELD_W, SLICE_FIELDS_H*hSlice, SLICE_FIELDS_W*wSlice,
                       2, &cellsActualState, &(cellSliceActual[hSlice][wSlice]));
        }
    }

    // New slices
    int (newSlices[NSLICES_H][NSLICES_W])[SLICE_FIELDS_H + 2][SLICE_FIELDS_W + 2];
    for(int hSlices=0; hSlices < NSLICES_H; hSlices++)
    {
        for(int wSlices=0; wSlices < NSLICES_W; wSlices++)
        {
            for (int y=0; y < SLICE_FIELDS_H + 2; y++)
            {
                for(int x=0; x < SLICE_FIELDS_W + 2; x++)
                {
                    (newSlices[hSlices][wSlices])[y][x] = 2;
                }
            }
        }
    }

    // Calculate new state
    for (int hSlice=0; hSlice < NSLICES_H; hSlice++)
    {
        for(int wSlice=0; wSlice < NSLICES_W; wSlice++)
        {
            followingSliceState(SLICE_FIELDS_H + 2, SLICE_FIELDS_W + 2,
                                &(cellSliceActual[hSlice][wSlice]), &(newSlices[hSlice][wSlice]));
        }
    }

    // Fuse slices
    // newSlices[0][0] = &cellSliceNew0;
    // newSlices[0][1] = &cellSliceNew1;
    // newSlices[1][0] = &cellSliceNew2;
    // newSlices[1][1] = &cellSliceNew3;


    // Display fused slices
    // show_cells(MATCHFIELD_H/2 + 2, MATCHFIELD_W/2 + 2, cellSliceNew1);

    // Fused new big plane is now old plane



    for (int y=0; y < 7; y++)
    {
        for(int x=0; x < 7; x++)
        {
            printf("%i ", (newSlices[0][0])[y][x]    ); // [y][x]
        }
        printf("\n");
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
