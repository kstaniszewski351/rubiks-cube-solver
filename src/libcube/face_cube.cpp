#include "face_cube.h"

#include <unordered_set>

#include "cubie_cube.h"

FaceCube::FaceCube() { Reset(); };

void FaceCube::Reset() {
  for (int i = 0; i < FaceCount; i++) {
    for (int j = 0; j < facelet_count; j++) {
      facelets[i * facelet_count + j] = static_cast<Face>(i);
    }
  };
}

FaceCube::FaceCube(const CubieCube& cube) {
  for (int i = 0; i < CornerCount; i++) {
    for (int p = 0; p < 3; p++) {
      int r = 0;
      if (cube.corner_ori[i] < 3) {
        r = (p + cube.corner_ori[i]) % 3;
      } else {
        r = ((p + cube.corner_ori[i]) % 3 + p) % 3;
      }

      facelets[corner_colors[i][p] * facelet_count + corner_positions[i][p]] =
          corner_colors[cube.corner_perm[i]][r];
    }
  }

  for (int i = 0; i < EdgeCount; i++) {
    for (int p = 0; p < 2; p++) {
      int r = (p + cube.edge_flip[i]) % 2;

      facelets[edge_colors[i][p] * facelet_count + edge_positions[i][p]] =
          edge_colors[cube.edge_perm[i]][r];
    }
  }
}

// checks if cube can be safely converted to CubieCube
bool FaceCube::IsValid() {
  std::array<int, FaceCount> count{};

  for (int i = 0; i < FaceCount; i++) {
    for (int j = 0; j < facelet_count; j++) {
      count[facelets[i * facelet_count + j]]++;
    }
  }

  for (int i : count) {
    if (i != facelet_count) {
      return false;
    }
  }

  for (int i = 0; i < CornerCount; i++) {
    std::unordered_set<Face> colors;

    for (int j = 0; j < 3; j++) {
      if (!colors
               .insert(facelets[corner_colors[i][j] * facelet_count +
                                corner_positions[i][j]])
               .second) {
        return false;
      };
    }
  }

  return true;
}