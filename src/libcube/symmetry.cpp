#include "symmetry.h"
#include "coord_moves.h"
#include "defs.h"
#include "cubie_cube.h"
#include "face_cube.h"
#include <iostream>

Symmetry::Symmetry()
{
}

void Symmetry::generateSyms()
{
    int i = 0;
    CubieCube cube = CubieCube();
    for(int urf3 = 0; urf3 < 3; urf3++)
    {
        for(int ud4 = 0; ud4 < 4; ud4++)
        {
            for(int fb2 = 0; fb2 < 2; fb2++)
            {
                for(int rl2 = 0; rl2 < 2; rl2++)
                {
                    syms[i] = cube;
                    i++;
                    cube.multiply(S_RL2);
                }
                cube.multiply(S_FB2);
            }
            cube.multiply(S_UD4);
        }
        cube.multiply(S_URF3);
    }
}