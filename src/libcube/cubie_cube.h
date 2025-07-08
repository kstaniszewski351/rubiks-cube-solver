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
    std::array<Edge, EdgeCount> edgePerm{};
    std::array<Corner, CornerCount> cornerPerm{};
    std::array<bool, EdgeCount> edgeOri{};
    std::array<int, CornerCount> cornerOri{};

    CubieCube();
    CubieCube(const CoordCube& c);
    CubieCube(const FaceCube& c);
    CubieCube(const std::array<Edge, EdgeCount>& ep, const std::array<Corner, CornerCount>& cp, const std::array<bool, EdgeCount>& eo, const std::array<int, CornerCount>& co);

    bool operator==(const CubieCube& c);
    bool operator!=(const CubieCube& c);

    void move(Move m);
    void reset();
    bool isSolved();
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
    void multiplyCorners(const CubieCube& cube);
    void multiplyEdges(const CubieCube& cube);
    void multiply(const CubieCube& cube);
private:
    void updateCorner(Corner c, int amount);
};
