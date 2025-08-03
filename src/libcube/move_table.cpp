#include "move_table.h"

#include "coords/coord_generator.h"
#include "move.h"

MoveTable::MoveTable(CoordGenerator const* generator)
    : table_(generator->GetMaxCoord() * MoveCount), n_moves_(MoveCount) {
  CubieCube c;
  for (int coord = 0; coord < generator->GetMaxCoord(); ++coord) {
    for (int move = 0; move < MoveCount; move++) {
      generator->InvertCoord(coord, c);
      c.Move(static_cast<Move>(move));
      table_[coord * MoveCount + move] = generator->GetCoord(c);
    }
  }
}

MoveTable::MoveTable(CoordGenerator const* generator,
                     const std::vector<Move>& moves)
    : table_(generator->GetMaxCoord() * moves.size()), n_moves_(moves.size()) {
  const int n_moves_ = moves.size();

  CubieCube c;
  for (int coord = 0; coord < generator->GetMaxCoord(); ++coord) {
    for (int move_index = 0; move_index < n_moves_; ++move_index) {
      generator->InvertCoord(coord, c);

      c.Move(moves[move_index]);

      table_[coord * n_moves_ + move_index] = generator->GetCoord(c);
    }
  }
}

int MoveTable::Get(int coord, int move) const {
  return table_[coord * n_moves_ + move];
};