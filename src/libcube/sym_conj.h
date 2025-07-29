#pragma once

#include "coords/coord_generator.h"
#include "symmetries.h"
#include <vector>

class SymConj
{
public:
    SymConj(CoordGenerator* generator, Symmetries* syms);
    int get(int coord, int sym);

private:
    std::vector<int> table_;
};