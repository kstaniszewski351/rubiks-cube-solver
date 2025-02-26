#pragma once

#include <array>
#include <string>
#include <map>
#include "defs.h"

class CoordCube;

using FaceCube = std::array<std::array<std::array<Face, 3>, 3>, 6>;

class CubieCube
{
public:
    CubieCube();
    CubieCube(CoordCube* c);

    void move(Move m);
    void reset();
    bool isSolved();
    FaceCube toFaceCube();

    std::array<Edge, EDGE_COUNT> edgePerm;
    std::array<Corner, CORNER_COUNT> cornerPerm;
    std::array<bool, EDGE_COUNT> edgeOri{};
    std::array<int, CORNER_COUNT> cornerOri{};
    void invEdgePermCoord(int coord);
    void invCornerPermCoord(int coord);
    void invEdgeOriCoord(int coord);
    void invCornerOriCoord(int coord);
    void invUDSliceCoord(int coord);
    int toCornerOriCoord();
    int toEdgeOriCoord();
    int toCornerPermCoord();
    int toEdgePermCoord();
    int toUDSliceCoord();
private:
    void updateCorner(Corner c, int amount);
};
