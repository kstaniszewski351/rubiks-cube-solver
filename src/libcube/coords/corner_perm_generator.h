#pragma once
#include "algorithms.h"
#include "coord_generator.h"
#include "cubie_cube.h"

class CornerPermGenerator : public CoordGenerator {
 public:
  int getCoord(const CubieCube& cube) const override;
  void invertCoord(int coord, CubieCube& cube) const override;
  constexpr int getMaxCoord() const override;

 private:
  constexpr static int n_coords_ = factorial<int>(CornerCount);
};