#pragma once
#include "algorithms.h"
#include "coord_generator.h"
#include "cubie_cube.h"

class CornerPermGenerator : public CoordGenerator {
 public:
  int GetCoord(const CubieCube& cube) const override;
  void InvertCoord(int coord, CubieCube& cube) const override;
  constexpr int GetMaxCoord() const override;

 private:
  constexpr static int n_coords_ = Factorial<int>(CornerCount);
};