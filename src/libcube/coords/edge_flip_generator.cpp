#include "edge_flip_generator.h"
#include <numeric>

#include "algorithms.h"
#include "cubie_cube.h"

int EdgeFlipGenerator::GetCoord(const CubieCube& cube) const {
  return BaseNEncode(2, cube.edge_flip.begin() + 1, cube.edge_flip.end());
}
void EdgeFlipGenerator::InvertCoord(int coord, CubieCube& cube) const {
  BaseNDecode(coord, 2, cube.edge_flip.begin() + 1, cube.edge_flip.end());

  const int sum =
      std::accumulate(cube.edge_flip.begin() + 1, cube.edge_flip.end(), 0);

  const int first = (2 - (sum % 2)) % 2;
  cube.edge_flip[0] = first;
}
int EdgeFlipGenerator::GetMaxCoord() const { return n_coords_; }