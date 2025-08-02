#pragma once
#include <vector>
#include "defs.h"
#include "cubie_cube.h"
#include "phase1.h"
#include "phase2.h"

class KociembaSolver
{
public:
    std::vector<Move> solve(CubieCube cube);

private:
    Phase1 phase_1_;
    Phase2 phase_2_;
};