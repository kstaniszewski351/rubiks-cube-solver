#pragma once
#include <array>
#include "coord_moves.h"

class Symmetry
{
    public:
    Symmetry();
    std::array<int, 64430> flipUDSlice;
    void generateSyms(CoordMoves& moves);
};