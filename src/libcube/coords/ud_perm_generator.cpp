#include "ud_perm_generator.h"

constexpr int ud_slice_start = 8;

int UDPermGenerator::GetCoord(const CubieCube& cube) const {
  return LehmerEncode(cube.edge_perm.begin(),
                      cube.edge_perm.begin() + ud_slice_start);
}

void UDPermGenerator::InvertCoord(int coord, CubieCube& cube) const {
  return LehmerDecode<Edge>(coord, cube.edge_perm.begin(),
                            cube.edge_perm.begin() + ud_slice_start);
}

int UDPermGenerator::GetMaxCoord() const { return n_coords_; }