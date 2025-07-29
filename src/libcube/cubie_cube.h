#pragma once

#include <array>
#include <string>
#include <map>
#include "defs.h"
#include <streambuf>
#include <ostream>

class CoordCube;
class FaceCube;

class CubieCube
{
public:
    std::array<Edge, EdgeCount> edgePerm;
    std::array<Corner, CornerCount> cornerPerm;
    std::array<bool, EdgeCount> edgeFlip;
    std::array<int, CornerCount> cornerOri;

    CubieCube();
    CubieCube(const CoordCube& c);
    CubieCube(const FaceCube& c);
    CubieCube(const std::array<Edge, EdgeCount>& ep, const std::array<Corner, CornerCount>& cp, const std::array<bool, EdgeCount>& eo, const std::array<int, CornerCount>& co);

    bool operator==(const CubieCube& c) const;
    bool operator!=(const CubieCube& c) const;

    friend std::ostream& operator<<(std::ostream& os, const CubieCube& cube);

    void move(Move m);
    void move(int m);
    void reset();
    bool isSolved() const;
    void multiplyCorners(const CubieCube& cube);
    void multiplyEdges(const CubieCube& cube);
    void multiply(const CubieCube& cube);
private:
    void updateCorner(Corner c, int amount);
};