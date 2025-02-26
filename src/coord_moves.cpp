#include "coord_moves.h"
#include "cubie_cube.h"
#include "defs.h"

CoordMoves::CoordMoves()
{

}

void CoordMoves::GenerateMoves()
{
    CubieCube c = CubieCube();

    for (int i = 0; i < 18; i++)
    {
        for(int j = 0; j < CORNER_ORI_COUNT; j++)
        {
            c.invCornerOriCoord(j);
            c.move(static_cast<Move>(i));
            cornerOriMoves[j][i] = c.toCornerOriCoord();
            c.reset();
        }
        for(int j = 0; j < EDGE_ORI_COUNT; j++)
        {
            c.invEdgeOriCoord(j);
            c.move(static_cast<Move>(i));
            edgeOriMoves[j][i] = c.toEdgeOriCoord();
            c.reset();
        }
        for(int j = 0; j < CORNER_PERM_COUNT; j++)
        {
            c.invCornerPermCoord(j);
            c.move(static_cast<Move>(i));
            cornerPermMoves[j][i] = c.toCornerPermCoord();
            c.reset();
        }
    }
}