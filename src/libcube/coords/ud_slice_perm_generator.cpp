#include "ud_slice_perm_generator.h"

constexpr int ud_slice_start = 8;

int UDSlicePermGenerator::GetCoord(const CubieCube& cube) const {
  return LehmerEncode(cube.edge_perm.begin() + ud_slice_start,
                      cube.edge_perm.end());
}

void UDSlicePermGenerator::InvertCoord(int coord, CubieCube& cube) const {
  LehmerDecode<Edge>(coord, 4, cube.edge_perm.end());

  for (int i = ud_slice_start; i < EdgeCount; i++) {
    cube.edge_perm[i] =
        static_cast<Edge>(static_cast<int>(cube.edge_perm[i]) + ud_slice_start);
  }
}
int UDSlicePermGenerator::GetMaxCoord() const { return n_coords_; }