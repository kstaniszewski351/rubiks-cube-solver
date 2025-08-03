#include "cubie_cube.h"

#include <algorithm>
#include <iostream>

#include "face_cube.h"

CubieCube::CubieCube() { Reset(); }

CubieCube::CubieCube(const std::array<Edge, EdgeCount>& ep,
                     const std::array<Corner, CornerCount>& cp,
                     const std::array<bool, EdgeCount>& eo,
                     const std::array<int, CornerCount>& co)
    : edge_perm(ep), corner_perm(cp), edge_flip(eo), corner_ori(co) {}

CubieCube::CubieCube(const FaceCube& c) {
  for (int i = 0; i < CornerCount; i++) {
    std::array<Face, 3> colors;

    for (int j = 0; j < 3; j++) {
      colors[j] = c.facelets[corner_colors[i][j] * facelet_count +
                             corner_positions[i][j]];
    }

    int r;
    int j;

    for (r = 0; r < 6; r++) {
      for (j = 0; j < CornerCount; j++) {
        if (std::ranges::equal(corner_colors[j], colors)) {
          break;
        }
      }

      if (j != CornerCount) {
        break;
      }

      if (r <= 3) {
        // rotate right
        std::ranges::rotate(colors, colors.end() - 1);
      }

      else if (r >= 3) {
        // rotate left
        std::ranges::rotate(colors, colors.begin() + 1);
      }
    }

    corner_perm[i] = static_cast<Corner>(j);
    corner_ori[i] = r;
  }

  for (int i = 0; i < EdgeCount; i++) {
    std::array<Face, 2> colors;

    for (int j = 0; j < 2; j++) {
      colors[j] =
          c.facelets[edge_colors[i][j] * facelet_count + edge_positions[i][j]];
    }

    int r;
    int j;

    for (r = 0; r < 2; r++) {
      for (j = 0; j < EdgeCount; j++) {
        if (std::ranges::equal(edge_colors[j], colors)) {
          break;
        }
      }

      if (j != EdgeCount) {
        break;
      }

      std::ranges::rotate(colors, colors.end() - 1);
    }

    edge_perm[i] = static_cast<Edge>(j);
    edge_flip[i] = r;
  }
}

bool CubieCube::operator==(const CubieCube& c) const {
  return edge_perm == c.edge_perm && corner_perm == c.corner_perm &&
         edge_flip == c.edge_flip && corner_ori == c.corner_ori;
}

bool CubieCube::operator!=(const CubieCube& c) const { return !operator==(c); }

void CubieCube::Reset() {
  for (int i = 0; i < CornerCount; i++) {
    corner_perm[i] = static_cast<Corner>(i);
    corner_ori[i] = 0;
  }

  for (int i = 0; i < EdgeCount; i++) {
    edge_perm[i] = static_cast<Edge>(i);
    edge_flip[i] = 0;
  }
}

bool CubieCube::IsSolved() const {
  for (int i = 0; i < CornerCount; i++) {
    if (corner_perm[i] != i | corner_ori[i] != 0) {
      return false;
    }
  }

  for (int i = 0; i < EdgeCount; i++) {
    if (edge_perm[i] != i | edge_flip[i] != 0) {
      return false;
    }
  }

  return true;
}

void CubieCube::Move(enum Move move) {
  int face = static_cast<Face>(move / 3);
  int n_rotations = (move % 3) + 1;

  std::array<Edge, 4> ep;
  std::array<Corner, 4> cp;
  std::array<bool, 4> eo;
  std::array<int, 4> co;
  for (int i = 0; i < 4; i++) {
    ep[i] = edge_perm[face_edges[face][i]];
    cp[i] = corner_perm[face_corners[face][i]];
    eo[i] = edge_flip[face_edges[face][i]];
    co[i] = corner_ori[face_corners[face][i]];
  }

  int mod = 4 - (n_rotations % 4);

  for (int i = 0; i < 4; i++) {
    int j = (mod + i) % 4;
    edge_perm[face_edges[face][i]] = ep[j];
    corner_perm[face_corners[face][i]] = cp[j];
    edge_flip[face_edges[face][i]] = eo[j];
    corner_ori[face_corners[face][i]] = co[j];
  }

  if (n_rotations % 2 == 0) {
    return;
  }

  switch (face) {
    case Right:
      UpdateCorner(URF, 1);
      UpdateCorner(UBR, 2);
      UpdateCorner(DRB, 1);
      UpdateCorner(DFR, 2);
      break;
    case Left:
      UpdateCorner(UFL, 2);
      UpdateCorner(ULB, 1);
      UpdateCorner(DBL, 2);
      UpdateCorner(DLF, 1);
      break;
    case Front:
      edge_flip[UF] = !edge_flip[UF];
      edge_flip[FR] = !edge_flip[FR];
      edge_flip[FL] = !edge_flip[FL];
      edge_flip[DF] = !edge_flip[DF];
      UpdateCorner(URF, 2);
      UpdateCorner(DFR, 1);
      UpdateCorner(DLF, 2);
      UpdateCorner(UFL, 1);
      break;
    case Back:
      edge_flip[UB] = !edge_flip[UB];
      edge_flip[BR] = !edge_flip[BR];
      edge_flip[BL] = !edge_flip[BL];
      edge_flip[DB] = !edge_flip[DB];

      UpdateCorner(UBR, 1);
      UpdateCorner(DRB, 2);
      UpdateCorner(DBL, 1);
      UpdateCorner(ULB, 2);
      break;
  }
}

void CubieCube::UpdateCorner(Corner c, int amount) {
  corner_ori[c] = (corner_ori[c] + amount) % 3;
}

void CubieCube::MultiplyEdges(const CubieCube& cube) {
  std::array<Edge, EdgeCount> ep;
  std::array<bool, EdgeCount> eo;

  for (int i = 0; i < EdgeCount; i++) {
    ep[i] = edge_perm[cube.edge_perm[i]];

    eo[i] = (cube.edge_flip[i] + edge_flip[cube.edge_perm[i]]) % 2;
  }

  edge_perm = ep;
  edge_flip = eo;
}

void CubieCube::MultiplyCorners(const CubieCube& cube) {
  std::array<Corner, CornerCount> cp;
  std::array<int, CornerCount> co;

  for (int i = 0; i < CornerCount; i++) {
    cp[i] = corner_perm[cube.corner_perm[i]];

    int ori = 0;
    int a = corner_ori[cube.corner_perm[i]];
    int b = cube.corner_ori[i];
    // both are regular, ori < 3
    if (a < 3 && b < 3) {
      ori = a + b;
      if (ori >= 3) {
        ori -= 3;
      }
    }
    // one is mirrored
    else if (a < 3 && b >= 3) {
      ori = a + b;
      if (ori >= 6) {
        ori -= 3;
      };
    }
    // one is mirrored
    else if ((a >= 3 && b < 3)) {
      ori = a - b;
      if (ori < 3) {
        ori += 3;
      }
    }
    // both are mirrored, ori < 3
    else if (a >= 3 && b >= 3) {
      ori = a - b;
      if (ori < 0) {
        ori += 3;
      }
    }

    co[i] = ori;
  }

  corner_perm = cp;
  corner_ori = co;
}

void CubieCube::Multiply(const CubieCube& cube) {
  MultiplyCorners(cube);
  MultiplyEdges(cube);
}

constexpr std::array<int, FaceCount> face_string_index{42, 48, 3, 81, 45, 39};

constexpr std::array<char, FaceCount> face_names{'W', 'Y', 'R', 'O', 'G', 'B'};

constexpr int n_rows = 9;
constexpr int n_columns = 13;

std::ostream& operator<<(std::ostream& os, const CubieCube& cube) {
  FaceCube f_cube = cube;
  std::string s(n_columns * n_rows, ' ');

  for (int i = 1; i <= n_rows; i++) {
    s.at(i * n_columns - 1) = '\n';
  }

  for (int f = 0; f < FaceCount; f++) {
    int si = face_string_index[f];
    for (int i = 0; i < 9; i++) {
      int x = i % 3;
      int y = i / 3;

      Face c;
      if (i == center_facelet) {
        c = static_cast<Face>(f);
      } else if (i > center_facelet) {
        c = f_cube.facelets[f * facelet_count + i - 1];
      } else {
        c = f_cube.facelets[f * facelet_count + i];
      }

      s.at(si + x + y * n_columns) = face_names[c];
    }
  }
  return os << "\n" << s;
}