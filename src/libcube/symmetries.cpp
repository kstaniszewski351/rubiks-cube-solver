#include "symmetries.h"
#include "defs.h"
#include "cubie_cube.h"
#include "face_cube.h"
#include <iostream>

Symmetries::Symmetries() :
    syms_(std::make_unique<std::array<CubieCube, SYM_COUNT>>())
{
    generateSyms();
    generateInvs();
}

void Symmetries::generateSyms()
{
    int i = 0;
    CubieCube cube;
    for(int urf3 = 0; urf3 < 3; urf3++)
    {
        for(int ud4 = 0; ud4 < 4; ud4++)
        {
            for(int fb2 = 0; fb2 < 2; fb2++)
            {
                for(int rl2 = 0; rl2 < 2; rl2++)
                {
                    (*syms_)[i] = cube;
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

void Symmetries::generateInvs()
{
    for(int sym = 0; sym < SYM_COUNT; sym++)
    {   
        for(int inv = 0; inv < SYM_COUNT; inv++)
        {
            CubieCube inv_cube = get(sym);
            inv_cube.multiply(get(inv));

            if(inv_cube.isSolved())
            {
                sym_inv_[sym] = inv;
                break;
            }
        }
    }
}

const CubieCube& Symmetries::get(int index) const
{
    return (*syms_).at(index);
}

const CubieCube& Symmetries::getInv(int index) const
{
    return (*syms_).at(sym_inv_[index]);
}