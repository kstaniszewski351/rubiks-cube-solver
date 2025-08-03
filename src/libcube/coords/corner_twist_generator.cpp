#include "corner_twist_generator.h"

#include <numeric>

int CornerTwistGenerator::GetCoord(const CubieCube& cube) const {
  return BaseNEncode(3, cube.corner_ori.begin() + 1, cube.corner_ori.end());
}
void CornerTwistGenerator::InvertCoord(int coord, CubieCube& cube) const {
  BaseNDecode(coord, 3, cube.corner_ori.begin() + 1, cube.corner_ori.end());

  const int sum =
      std::accumulate(cube.corner_ori.begin() + 1, cube.corner_ori.end(), 0);

  const int first = (3 - (sum % 3)) % 3;
  cube.corner_ori[0] = first;
}
int CornerTwistGenerator::GetMaxCoord() const { return n_coords_; }