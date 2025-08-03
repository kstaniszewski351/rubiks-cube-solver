#pragma once
#include "algorithms.h"
#include "coord_generator.h"

class UDSlicePosGenerator : public CoordGenerator {
 public:
  int GetCoord(const CubieCube& cube) const override;
  void InvertCoord(int coord, CubieCube& cube) const override;
  int GetMaxCoord() const override;

 private:
  constexpr static int n_coords_ = BiCoeff<int>(EdgeCount, 4);
};