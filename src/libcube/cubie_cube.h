#pragma once

#include <array>
#include <string>
#include <map>
#include "defs.h"

class CoordCube;
class FaceCube;

class CubieCube
{
public:
    CubieCube();
    CubieCube(const CoordCube& c);
    CubieCube(const FaceCube& c);

    void move(Move m);
    void reset();
    bool isSolved();

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
    void multiplyCorners(CubieCube& b);
    void multiplyEdges(CubieCube& b);
private:
    void updateCorner(Corner c, int amount);
};
