#pragma once
#include "coord_generator.h"
#include "cubie_cube.h"
#include "util.h"

class CornerTwistGenerator : public CoordGenerator
{
public:
    int getCoord(const CubieCube& cube) const override;
    void invertCoord(int coord, CubieCube& cube) const override;
    int getMaxCoord() const override;
private:
    constexpr static int n_coords_ = power(3, (CornerCount - 1));
};