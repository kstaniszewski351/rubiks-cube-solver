#pragma once
#include "algorithms.h"
#include "coord_generator.h"

class UDSlicePosGenerator : public CoordGenerator {
 public:
  int getCoord(const CubieCube& cube) const override;
  void invertCoord(int coord, CubieCube& cube) const override;
  int getMaxCoord() const override;

 private:
  constexpr static int n_coords_ = biCoeff<int>(EdgeCount, 4);
};