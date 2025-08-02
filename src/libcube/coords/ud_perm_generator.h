#pragma once
#include "algorithms.h"
#include "coord_generator.h"

class UDPermGenerator : public CoordGenerator {
 public:
  int getCoord(const CubieCube& cube) const override;
  void invertCoord(int coord, CubieCube& cube) const override;
  int getMaxCoord() const override;

 private:
  constexpr static int n_coords_ = factorial(8);
};