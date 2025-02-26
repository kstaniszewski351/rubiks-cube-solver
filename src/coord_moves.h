#pragma once

#include <array>
#include "defs.h"

using moveArray = std::array<int, 18>;

class CoordMoves
{
public:
    CoordMoves();
    void GenerateMoves();
    std::array<moveArray, CORNER_ORI_COUNT> cornerOriMoves {};
    std::array<moveArray,  EDGE_ORI_COUNT> edgeOriMoves {};
    std::array<moveArray, CORNER_PERM_COUNT> cornerPermMoves {};
};