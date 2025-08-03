#pragma once
#include "algorithms.h"
#include "coord_generator.h"

class UDPermGenerator : public CoordGenerator {
 public:
  int GetCoord(const CubieCube& cube) const override;
  void InvertCoord(int coord, CubieCube& cube) const override;
  int GetMaxCoord() const override;

 private:
  constexpr static int n_coords_ = Factorial(8);
};