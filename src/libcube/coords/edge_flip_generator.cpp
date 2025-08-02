#include "edge_flip_generator.h"
#include <numeric>

#include "algorithms.h"
#include "cubie_cube.h"

int EdgeFlipGenerator::getCoord(const CubieCube& cube) const {
  return baseNEncode(2, cube.edgeFlip.begin() + 1, cube.edgeFlip.end());
}
void EdgeFlipGenerator::invertCoord(int coord, CubieCube& cube) const {
  baseNDecode(coord, 2, cube.edgeFlip.begin() + 1, cube.edgeFlip.end());

  const int sum =
      std::accumulate(cube.edgeFlip.begin() + 1, cube.edgeFlip.end(), 0);

  const int first = (2 - (sum % 2)) % 2;
  cube.edgeFlip[0] = first;
}
int EdgeFlipGenerator::getMaxCoord() const { return n_coords_; }