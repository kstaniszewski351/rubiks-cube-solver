#pragma once

#include "defs.h"
#include "cubie_cube.h"

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