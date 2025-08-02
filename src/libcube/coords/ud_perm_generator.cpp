#include "ud_perm_generator.h"

constexpr int ud_slice_start = 8;

int UDPermGenerator::getCoord(const CubieCube& cube) const {
  return lehmerEncode(cube.edgePerm.begin(),
                      cube.edgePerm.begin() + ud_slice_start);
}

void UDPermGenerator::invertCoord(int coord, CubieCube& cube) const {
  return lehmerDecode<Edge>(coord, ud_slice_start,
                            cube.edgePerm.begin() + ud_slice_start);
}

int UDPermGenerator::getMaxCoord() const { return n_coords_; }