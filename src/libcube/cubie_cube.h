#pragma once

#include <array>
#include <ostream>

#include "cube.h"
#include "face_cube.h"
#include "move.h"

class FaceCube;

constexpr std::array<std::array<Face, 2>, EdgeCount> edge_colors = {{
    {Up, Right},
    {Up, Left},
    {Up, Back},
    {Down, Right},
    {Down, Left},
    {Down, Back},
    {Up, Front},
    {Down, Front},
    {Front, Right},
    {Front, Left},
    {Back, Right},
    {Back, Left},
}};

constexpr std::array<std::array<Face, 3>, CornerCount> corner_colors = {
    {{{Up, Right, Front}},
     {{Up, Front, Left}},
     {{Up, Back, Right}},
     {{Up, Left, Back}},
     {{Down, Front, Right}},
     {{Down, Left, Front}},
     {{Down, Right, Back}},
     {{Down, Back, Left}}}};

constexpr std::array<std::array<Corner, 4>, 6> face_corners = {{
    {ULB, UBR, URF, UFL},
    {DLF, DFR, DRB, DBL},
    {URF, UBR, DRB, DFR},
    {ULB, UFL, DLF, DBL},
    {UFL, URF, DFR, DLF},
    {UBR, ULB, DBL, DRB},
}};

constexpr std::array<std::array<Edge, 4>, 6> face_edges = {{
    {UB, UR, UF, UL},
    {DF, DR, DB, DL},
    {UR, BR, DR, FR},
    {UL, FL, DL, BL},
    {UF, FR, DF, FL},
    {UB, BL, DB, BR},
}};

struct CubieCube {
 public:
  std::array<Edge, EdgeCount> edge_perm;
  std::array<Corner, CornerCount> corner_perm;
  std::array<bool, EdgeCount> edge_flip;
  std::array<int, CornerCount> corner_ori;

  CubieCube();
  CubieCube(const FaceCube& c);
  CubieCube(const std::array<Edge, EdgeCount>& ep,
            const std::array<Corner, CornerCount>& cp,
            const std::array<bool, EdgeCount>& eo,
            const std::array<int, CornerCount>& co);

  bool operator==(const CubieCube& c) const;
  bool operator!=(const CubieCube& c) const;

  friend std::ostream& operator<<(std::ostream& os, const CubieCube& cube);

  void Move(Move m);
  void Reset();
  bool IsSolved() const;
  void MultiplyCorners(const CubieCube& cube);
  void MultiplyEdges(const CubieCube& cube);
  void Multiply(const CubieCube& cube);

 private:
  void UpdateCorner(Corner c, int amount);
};