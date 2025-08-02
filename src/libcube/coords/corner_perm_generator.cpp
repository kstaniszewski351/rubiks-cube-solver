#include "corner_perm_generator.h"

int CornerPermGenerator::getCoord(const CubieCube& cube) const {
  return lehmerEncode(cube.cornerPerm.begin(), cube.cornerPerm.end());
}
void CornerPermGenerator::invertCoord(int coord, CubieCube& cube) const {
  lehmerDecode<Corner>(coord, CornerCount, cube.cornerPerm.end());
}
constexpr int CornerPermGenerator::getMaxCoord() const { return n_coords_; }