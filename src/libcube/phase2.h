#pragma once

#include <vector>

#include "coords/corner_perm_generator.h"
#include "coords/ud_perm_generator.h"
#include "coords/ud_slice_perm_generator.h"
#include "cubie_cube.h"
#include "move_table.h"
#include "pruning.h"

struct Phase2Coord {
  int corner_perm;
  int ud_perm;
  int ud_slice_perm;
};

class Phase2 {
 public:
  Phase2();
  std::vector<Move> Solve(const CubieCube& cube);

 private:
  const CornerPermGenerator corner_perm_gen_;
  const UDPermGenerator ud_perm_gen_;
  const UDSlicePermGenerator ud_slice_perm_gen_;
  const MoveTable corner_perm_moves_;
  const MoveTable ud_perm_moves_;
  const MoveTable ud_slice_perm_moves_;
  const Pruning corner_perm_ud_slice_perm_pruning;
  const Pruning ud_perm_ud_slice_perm_pruning;

  int IDASearch(std::vector<Phase2Coord>& coord_stack,
                std::vector<Move>& move_stack, int depth, int bound);
  int EstimateDistanceLeft(Phase2Coord coord);
  Phase2Coord MoveCoord(Phase2Coord coord, int move);
};