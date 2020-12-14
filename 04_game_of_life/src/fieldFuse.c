#include <stdio.h>

int fieldFuse(
        int hTotal, int wTotal, int hStart, int wStart, int slices, int(*fullField)[hTotal][wTotal],
        int(*fieldSlice)[hTotal/slices + 2][wTotal/slices + 2]
)

{
    int hA = hTotal/slices;
    int hE, wD = 1;
    int wA = wTotal/slices;
    int x, y, xFull, yFull, xSlice, ySlice;

    for (y=0; y < hA; y++)
    {
        for (x=0; x < wA; x++)
        {
            ySlice = hE + y;
            xSlice = wD + x;
            yFull = hStart + y;
            xFull = wStart + x;
            (*fullField)[yFull][xFull] = (*fieldSlice)[ySlice][xSlice];
            // printf("Y: %i, X: %i, :%i\n",ySlice, xSlice, (*fieldSlice)[ySlice][xSlice]);
            // printf("Y: %i, X: %i, :%i\n",yFull, xFull, (*fullField)[yFull][xFull]);
        }

    }
}

