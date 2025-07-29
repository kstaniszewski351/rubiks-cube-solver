#pragma once
#include <cubie_cube.h>

class CoordGenerator
{
public:
    virtual int getCoord(const CubieCube& cube) const = 0;
    virtual void invertCoord(int coord, CubieCube& cube) const = 0;
    virtual int getMaxCoord() const = 0;
};