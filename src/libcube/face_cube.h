#pragma once

#include "defs.h"
#include "cubie_cube.h"
#include "move.h"

class CubieCube;


constexpr std::array<std::array<int, 2>, EdgeCount> EDGE_POSITIONS = 
{{
    {{1, 6}},
    {{6, 1}},
    {{3, 4}},
    {{1, 1}},
    {{6, 6}},
    {{4, 3}},
    {{4, 3}},
    {{3, 4}},
    {{1, 4}},
    {{6, 4}},
    {{1, 3}},
    {{6, 3}}
}};

//the indexes are arranged in clockwise order, the first being on U or D face
constexpr std::array<std::array<int, 3>, CornerCount> CORNER_POSITIONS =
{{
    {{2, 7, 0}},
    {{7, 5, 2}},
    {{0, 2, 5}},
    {{5, 0, 7}},
    {{0, 2, 2}},
    {{5, 7, 7}},
    {{2, 0, 0}},
    {{7, 5, 5}}
}};

constexpr int CENTER = 4;
constexpr int FACELET_COUNT = 8;

class FaceCube
{
public:
    FaceCube();
    FaceCube(const CubieCube& cube);
    void move(Move m);
    void reset();
    std::array<Face, FACELET_COUNT * FaceCount> facelets;
    bool isValid();
};