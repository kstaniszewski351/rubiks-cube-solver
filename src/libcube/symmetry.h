#pragma once
#include <array>
#include "coord_moves.h"
#include "defs.h"
#include "cubie_cube.h"

//flip on RL axis
inline const CubieCube S_RL2 = CubieCube(
    std::array<Edge, EdgeCount> {UL, UR, UB, DL, DR, DB, FL, FR, UF, DF, BL, BR}, 
    std::array<Corner, CornerCount> {UFL, URF, ULB, UBR, DLF, DFR, DBL, DRB},
    std::array<bool, EdgeCount> {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    std::array<int, CornerCount> {3, 3, 3, 3, 3, 3, 3, 3}
);

//rotate 90 degrees on UD axis
inline const CubieCube S_UD4 = CubieCube(
    std::array<Edge, EdgeCount> {UB, UF, UL, DB, DF, DL, BR, FR, UR, DR, BL, FL}, 
    std::array<Corner, CornerCount> {UBR, URF, ULB, UFL, DRB, DFR, DBL, DLF},
    std::array<bool, EdgeCount> {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
    std::array<int, CornerCount> {0, 0, 0, 0, 0, 0, 0, 0}
);

//rotate 180 degrees on FB axis
inline const CubieCube S_FB2 = CubieCube(
    std::array<Edge, EdgeCount> {DL, DR, DB, UL, UR, UB, FL, FR, DF, UF, BL, BR}, 
    std::array<Corner, CornerCount> {DLF, DFR, DBL, DRB, UFL, URF, ULB, UBR},
    std::array<bool, EdgeCount> {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    std::array<int, CornerCount> {0, 0, 0, 0, 0, 0, 0, 0}
);

//rotate 120 degrees on URF DBL axis
inline const CubieCube S_URF3 = CubieCube(
    std::array<Edge, EdgeCount> {UF, DF, FL, UB, DB, BL, UR, DR, FR, BR, UL, DL}, 
    std::array<Corner, CornerCount> {URF, DFR, UFL, DLF, UBR, DRB, ULB, DBL},
    std::array<bool, EdgeCount> {1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1},
    std::array<int, CornerCount> {2, 1, 1, 2, 1, 2, 2, 1}
);

class Symmetry
{
public:
    Symmetry();
    void generateSyms();

    std::array<int, 64430> flipUDSlice;
    std::array<CubieCube, SYM_COUNT> syms;
};

