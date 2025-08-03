#include "corner_perm_generator.h"

int CornerPermGenerator::GetCoord(const CubieCube& cube) const {
  return LehmerEncode(cube.corner_perm.begin(), cube.corner_perm.end());
}
void CornerPermGenerator::InvertCoord(int coord, CubieCube& cube) const {
  LehmerDecode<Corner>(coord, CornerCount, cube.corner_perm.end());
}
constexpr int CornerPermGenerator::GetMaxCoord() const { return n_coords_; }