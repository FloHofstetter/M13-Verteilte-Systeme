#include <stdio.h>

int fieldSlice(
        int hTotal, int wTotal, int hStart, int wStart, int slices, int(*fullField)[hTotal][wTotal],
        int(*fieldSlice)[hTotal/slices + 2][wTotal/slices + 2]
        )
{
    int hA = hTotal/slices;
    int wA = wTotal/slices;
    int hD = hA;
    int hB = hA;
    int wE = wA + 2;
    int wC = wA + 2;
    int wD = 1;
    int wB = 1;
    int hE = 1;
    int hC = 1;
    int x, y, xFull, yFull, xSlice, ySlice;

    // Area A
    for (y=0; y < hA; y++)  //
    {
        for (x=0; x < wA; x++)  //
        {
            ySlice = hE + y;
            xSlice = wD + x;
            yFull = hStart + y;
            xFull = wStart + x;
            (*fieldSlice)[ySlice][xSlice] = (*fullField)[yFull][xFull];
            // printf("Y: %i, X: %i, :%i\n",ySlice, xSlice, *(fieldSlice)[ySlice][xSlice]);

        }

    }

    // Area B
    xSlice = wD + wA;
    xFull = wStart + wA;
    // Over right boarder -> loop left.
    for (y=0; y < hB; y++)
    {
        ySlice = hE + y;
        yFull = hStart + y;
        if (yFull > wTotal)
        {
            yFull -= wTotal;
        }
        (*fieldSlice)[ySlice][xSlice] = (*fullField)[yFull][xFull];
    }

    // Area C
    ySlice = hE + hD;
    yFull = hStart + hA;
    // Over lower boarder -> loop top.
    if (yFull > hTotal)
    {
        yFull -= hTotal;
    }
    for (x=0; x < wC; x++)
    {
        xSlice = 0 + x;
        xFull = wStart - 1 + x;
        // Over right boarder -> loop left.
        if (xFull > wTotal)
        {
            xFull -= wTotal;
        }
        // Over left boarder -> loop right.
        else if (xFull < 0)
        {
            xFull += wTotal;
        }
        (*fieldSlice)[ySlice][xSlice] = (*fullField)[yFull][xFull];
    }

    // Area D
    xSlice = 0;
    xFull = wStart - 1;
    // Over left boarder -> loop right.
    if (xFull <  wTotal)
    {
        xFull += wTotal;
    }
    for (y=0; y < hD; y++)
    {
        ySlice = hE + y;
        yFull = hStart + y;
        (*fieldSlice)[ySlice][xSlice] = (*fullField)[yFull][xFull];
    }

    // Area E
    ySlice = 0;
    yFull = hStart - 1;
    if (yFull < hTotal)
    {
        yFull += hTotal;
    }
    for (x=0; x < wE; x++)
    {
        xSlice = 0 + x;
        xFull = wStart - 1 + x;
        // Over left boarder -> loop right.
        if (xFull < 0)
        {
            xFull += wTotal;
        }
        else if (xFull > wTotal)
        {
            xFull -= wTotal;
        }
        (*fieldSlice)[ySlice][xSlice] = (*fullField)[yFull][xFull];
    }
}
