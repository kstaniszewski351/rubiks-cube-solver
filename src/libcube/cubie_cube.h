#pragma once

#include <array>
#include <string>
#include <map>
#include "defs.h"
#include <streambuf>
#include <ostream>
#include "face_cube.h"
#include "cube.h"
#include "move.h"

class FaceCube;

constexpr std::array<std::array<Face, 2>, EdgeCount> EDGE_COLORS =
{{
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

constexpr std::array<std::array<Face, 3>, CornerCount> CORNER_COLORS =
{{
    {{Up, Right, Front}},
    {{Up, Front, Left}},
    {{Up, Back, Right}},
    {{Up, Left, Back}},
    {{Down, Front, Right}},
    {{Down, Left, Front}},
    {{Down, Right, Back}},
    {{Down, Back, Left}}
}};

constexpr std::array<std::array<Corner, 4>, 6> FACE_CORNERS =
{{
    {ULB, UBR, URF, UFL},
    {DLF, DFR, DRB, DBL},
    {URF, UBR, DRB, DFR},
    {ULB, UFL, DLF, DBL},
    {UFL, URF, DFR, DLF},
    {UBR, ULB, DBL, DRB},
}};

constexpr std::array<std::array<Edge, 4>, 6> FACE_EDGES =
{{
    {UB, UR, UF, UL},
    {DF, DR, DB, DL},
    {UR, BR, DR, FR},
    {UL, FL, DL, BL},
    {UF, FR, DF, FL},
    {UB, BL, DB, BR},
}};

class CubieCube
{
public:
    std::array<Edge, EdgeCount> edgePerm;
    std::array<Corner, CornerCount> cornerPerm;
    std::array<bool, EdgeCount> edgeFlip;
    std::array<int, CornerCount> cornerOri;

    CubieCube();
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