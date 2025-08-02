#pragma once

#include <vector>

#include "coords/corner_twist_generator.h"
#include "coords/edge_flip_generator.h"
#include "coords/ud_slice_pos_generator.h"
#include "cubie_cube.h"
#include "move_table.h"
#include "pruning.h"

struct Phase1Coord {
  int flip;
  int slice_pos;
  int twist;

  bool isSolved() const;
};

class Phase1 {
 public:
  Phase1();
  std::vector<Move> solve(const CubieCube& cube);

 private:
  const EdgeFlipGenerator flip_gen_;
  const UDSlicePosGenerator slice_pos_gen_;
  const CornerTwistGenerator twist_gen_;
  const MoveTable flip_moves_;
  const MoveTable slice_pos_moves_;
  const MoveTable twist_moves_;
  const Pruning flip_slice_pos_pruning_;
  const Pruning twist_slice_pos_pruning_;

  int IDASearch(std::vector<Phase1Coord>& coord_stack,
                std::vector<Move>& move_stack, int depth, int bound);
  int estimateDistanceLeft(Phase1Coord coord);
  Phase1Coord moveCoord(Phase1Coord coord, Move m);
};