#pragma once

#include <string>
#include "defs.h"
#include "cubie_cube.h"


class FaceCube
{
public:
    FaceCube(const CubieCube& cube);
    std::array<std::array<Face, FACELET_COUNT>, FACE_COUNT> facelets;
    std::string toString();
};