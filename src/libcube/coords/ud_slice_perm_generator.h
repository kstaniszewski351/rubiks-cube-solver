#pragma once
#include "coord_generator.h"
#include "algorithms.h"
#include "defs.h"

class UDSlicePermGenerator : public CoordGenerator
{
public:
    int getCoord(const CubieCube& cube) const override;
    void invertCoord(int coord, CubieCube& cube) const override;
    int getMaxCoord() const override;
private:
    constexpr static int n_coords_ = factorial(4);
};