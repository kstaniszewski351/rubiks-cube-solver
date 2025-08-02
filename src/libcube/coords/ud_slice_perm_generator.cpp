#include "ud_slice_perm_generator.h"

constexpr int ud_slice_start = 8;

int UDSlicePermGenerator::getCoord(const CubieCube& cube) const {
  return lehmerEncode(cube.edgePerm.begin() + ud_slice_start,
                      cube.edgePerm.end());
}

void UDSlicePermGenerator::invertCoord(int coord, CubieCube& cube) const {
  lehmerDecode<Edge>(coord, 4, cube.edgePerm.end());

  for (int i = ud_slice_start; i < EdgeCount; i++) {
    cube.edgePerm[i] =
        static_cast<Edge>(static_cast<int>(cube.edgePerm[i]) + ud_slice_start);
  }
}
int UDSlicePermGenerator::getMaxCoord() const { return n_coords_; }