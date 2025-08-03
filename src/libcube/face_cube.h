#pragma once

#include "cubie_cube.h"
#include "move.h"

class CubieCube;

constexpr std::array<std::array<int, 2>, EdgeCount> edge_positions = {
    {{{1, 6}},
     {{6, 1}},
     {{3, 4}},
     {{1, 1}},
     {{6, 6}},
     {{4, 3}},
     {{4, 3}},
     {{3, 4}},
     {{1, 4}},
     {{6, 4}},
     {{1, 3}},
     {{6, 3}}}};

// the indexes are arranged in clockwise order, the first being on U or D face
constexpr std::array<std::array<int, 3>, CornerCount> corner_positions = {
    {{{2, 7, 0}},
     {{7, 5, 2}},
     {{0, 2, 5}},
     {{5, 0, 7}},
     {{0, 2, 2}},
     {{5, 7, 7}},
     {{2, 0, 0}},
     {{7, 5, 5}}}};

constexpr int center_facelet = 4;
constexpr int facelet_count = 8;

struct FaceCube {
 public:
  FaceCube();
  FaceCube(const CubieCube& cube);
  void Move(Move m);
  void Reset();
  bool IsValid();

  std::array<Face, facelet_count * FaceCount> facelets;
};