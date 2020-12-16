#include "showCells.h"
#include "followingCellState.h"
#include "followingSliceState.h"
#include "fieldSlice.h"
#include "fieldFuse.h"
#include "inicializeSlices.h"
#include <string.h>
#include <unistd.h>

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
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int cellsNextState[MATCHFIELD_W][MATCHFIELD_H] = {0};

    for (int i=0; i<100; i++)
    {


    // Actual slices
    int (cellSliceActual[NSLICES_H][NSLICES_W])[SLICE_FIELDS_H + 2][SLICE_FIELDS_W + 2];

    inicializeSlices(NSLICES_H, NSLICES_W, SLICE_FIELDS_H, SLICE_FIELDS_W, &cellSliceActual);

    // Slice field
    for (int hSlice=0; hSlice < NSLICES_H; hSlice++)
    {
        for(int wSlice=0; wSlice < NSLICES_W; wSlice++)
        {
            fieldSlice(MATCHFIELD_H, MATCHFIELD_W, SLICE_FIELDS_H*hSlice, SLICE_FIELDS_W*wSlice,
                       2, &cellsActualState, &(cellSliceActual[hSlice][wSlice]));
        }
    }

    // New slices - dec and init
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
    for (int hSlice=0; hSlice < NSLICES_H; hSlice++)
    {
        for (int wSlice = 0; wSlice < NSLICES_W; wSlice++)
        {
            fieldFuse(MATCHFIELD_H, MATCHFIELD_W,  SLICE_FIELDS_H*hSlice, SLICE_FIELDS_W*wSlice, NSLICES,
                      &cellsNextState, &(newSlices[hSlice][wSlice]));
        }
    }


    // Show Numbers
    //showNumbers(MATCHFIELD_H, MATCHFIELD_W, &cellsNextState);

        show_cells(MATCHFIELD_H, MATCHFIELD_W, cellsNextState);

        memcpy(&cellsActualState, &cellsNextState, MATCHFIELD_W * MATCHFIELD_H * sizeof(int));
        usleep(250*1e3); // ms
    }


}



    /*

     */
