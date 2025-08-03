#include "move.h"

#include <random>

Face GetMoveFace(Move move) { return static_cast<Face>(move / 3); }

Axis GetFaceAxis(Face face) { return static_cast<Axis>(face / 2); }

std::vector<Move> RandomScramble(int lenght, int seed) {
  std::vector<Move> moves;
  auto move_distrib = std::uniform_int_distribution<>(0, MoveCount - 1);
  moves.reserve(lenght);
  auto random = std::mt19937(seed);

  for (int i = 0; i < lenght; i++) {
    Move move;

    do {
      move = static_cast<Move>(move_distrib(random));
    } while (IsMoveRedundant(move, moves.begin(), moves.end()));

    moves.push_back(move);
  }

  return moves;
}
