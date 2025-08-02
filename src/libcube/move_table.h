#pragma once
#include <array>
#include <memory>
#include <vector>
#include <cubie_cube.h>
#include "defs.h"
#include "coords/coord_generator.h"
#include "move.h"

class MoveTable
{
public:
    MoveTable(CoordGenerator const* generator);
    MoveTable(CoordGenerator const* generator, const std::vector<Move>& moves);
    int get(int coord, int move) const;
private:
    std::vector<int> table_;
    int n_moves_;
};

