#include "move_table.h"

#include "coords/coord_generator.h"
#include "move.h"

MoveTable::MoveTable(CoordGenerator const* generator)
    : table_(generator->getMaxCoord() * MoveCount), n_moves_(MoveCount) {
  CubieCube c;
  for (int coord = 0; coord < generator->getMaxCoord(); ++coord) {
    for (int move = 0; move < MoveCount; move++) {
      generator->invertCoord(coord, c);
      c.move(static_cast<Move>(move));
      table_[coord * MoveCount + move] = generator->getCoord(c);
    }
  }
}

MoveTable::MoveTable(CoordGenerator const* generator,
                     const std::vector<Move>& moves)
    : table_(generator->getMaxCoord() * moves.size()), n_moves_(moves.size()) {
  const int n_moves_ = moves.size();

  CubieCube c;
  for (int coord = 0; coord < generator->getMaxCoord(); ++coord) {
    for (int move_index = 0; move_index < n_moves_; ++move_index) {
      generator->invertCoord(coord, c);

      c.move(moves[move_index]);

      table_[coord * n_moves_ + move_index] = generator->getCoord(c);
    }
  }
}

int MoveTable::get(int coord, int move) const {
  return table_[coord * n_moves_ + move];
};