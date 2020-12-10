#include "deadAllive.h"

int followingCellState(int *actualCellState, int(*neighbourhood)[8])
{

    int sumNeighbourhood = 0;
    for (int neighbour=0; neighbour < 8; neighbour ++)
    {
        sumNeighbourhood = sumNeighbourhood + (*neighbourhood)[neighbour];
    }

    int nextCellState;
    switch (*actualCellState)
    {
        case 0:
            // Birth
            if (sumNeighbourhood==3)
            {
                nextCellState = ALIVE;
            }
            // Death by overpopulation
            // Implicit except 3.
            else if (sumNeighbourhood >= 0 && sumNeighbourhood <= 8)
            {
                nextCellState = DEAD;
            }
            // Should not be reached.
            else
            {
                nextCellState = UNKNOWN;
            }

            break;
        case 1:
            // Death by isolation
            if (sumNeighbourhood==0 || sumNeighbourhood==1)
            {
                nextCellState = DEAD;
            }
            // Best living conditions
            else if (sumNeighbourhood==2 || sumNeighbourhood==3)
            {
                nextCellState = ALIVE;
            }
            // Death by overpopulation
            else if (sumNeighbourhood >= 4 && sumNeighbourhood <= 8)
            {
                nextCellState = DEAD;
            }
            // Should not be reached.
            else
            {
                nextCellState = UNKNOWN;
            }
            break;
    }
    return nextCellState;
}


