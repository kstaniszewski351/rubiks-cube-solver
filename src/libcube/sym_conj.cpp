#include "sym_conj.h"
#include <iostream>

SymConj::SymConj(CoordGenerator* generator, Symmetries* syms) :
    table_(generator->getMaxCoord() * D4H_SYM_COUNT, -1)
{

    for(int coord = 0; coord < generator->getMaxCoord(); coord++)
    {
        CubieCube cube;
        generator->invertCoord(coord, cube);

        for(int sym = 0; sym < D4H_SYM_COUNT; sym++)
        {
            auto sym_cube = syms->get(sym);
            sym_cube.multiply(cube);
            sym_cube.multiply(syms->getInv(sym));

            table_[coord * D4H_SYM_COUNT + sym] = generator->getCoord(sym_cube);
        }
    }

    int twist_conj_counter = 0;
    for(auto i : table_)
    {
        if(i > 2137)
        {
            twist_conj_counter ++;
        }
    }

    std::cout << "twist conj counter: " << twist_conj_counter << "\n";
}

int SymConj::get(int coord, int sym)
{
    return table_[coord * D4H_SYM_COUNT + sym];
}