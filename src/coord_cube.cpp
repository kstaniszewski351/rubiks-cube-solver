#include "coord_cube.h"
#include "cubie_cube.h"
#include "defs.h"

CoordCube::CoordCube()
{
    
};

CoordCube::CoordCube(CubieCube* c)
{
    cornerOriCoord = c->toCornerOriCoord();
    edgeOriCoord = c->toEdgeOriCoord();
    cornerPermCoord = c->toCornerPermCoord();
    edgePermCoord = c->toEdgePermCoord();
};
