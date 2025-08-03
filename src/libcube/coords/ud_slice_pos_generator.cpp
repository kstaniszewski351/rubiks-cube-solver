#include "ud_slice_pos_generator.h"

constexpr int ud_slice_start = 8;

int UDSlicePosGenerator::GetCoord(const CubieCube& cube) const {
  return CombinationEncode(cube.edge_perm,
                           [](Edge e) { return e >= ud_slice_start; });
}

void UDSlicePosGenerator::InvertCoord(int coord, CubieCube& cube) const {
  auto combination = CombinationDecode<12>(coord, 4);
  std::array<Edge, EdgeCount> edge_perm;

  int index = 0;
  int ud_slice_index = ud_slice_start;

  for (int i = 0; i < EdgeCount; i++) {
    if (combination[i]) {
      edge_perm[i] = static_cast<Edge>(ud_slice_index);
      ud_slice_index++;
    } else {
      edge_perm[i] = static_cast<Edge>(index);
      index++;
    }
  }
  cube.edge_perm = edge_perm;
}
int UDSlicePosGenerator::GetMaxCoord() const { return n_coords_; }