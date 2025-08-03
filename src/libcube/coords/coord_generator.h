#pragma once
#include <cubie_cube.h>

class CoordGenerator {
 public:
  virtual int GetCoord(const CubieCube& cube) const = 0;
  virtual void InvertCoord(int coord, CubieCube& cube) const = 0;
  virtual int GetMaxCoord() const = 0;
};