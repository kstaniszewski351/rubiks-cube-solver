#pragma once

#include <array>
#include <map>
#include <string>

enum Move
{
    U1,
    U2,
    U3,
    D1,
    D2,
    D3,
    R1,
    R2,
    R3,
    L1,
    L2,
    L3,
    F1,
    F2,
    F3,
    B1,
    B2,
    B3
};

enum Corner
{
    URF,
    ULF,
    URB,
    ULB,
    DRF,
    DLF,
    DRB,
    DLB
};

enum Edge
{
    UR,
    UL,
    UB,
    DR,
    DL,
    DB,
    FR,
    FL,
    UF,
    DF,
    BR,
    BL
};

enum Face
{
    Up,
    Down,
    Right,
    Left,
    Front,
    Back
};

struct CornerCubie
{
    Corner index;
    int orientation;
};

struct EdgeCubie
{
    Edge index;
    int orientation;
};

constexpr int CORNER_ORI_COUNT = 2187;
constexpr int EDGE_ORI_COUNT = 2048;
constexpr int CORNER_PERM_COUNT = 40320;
constexpr int EDGE_PERM_COUNT = 479001600;

constexpr int EDGE_COUNT = 12;
constexpr int CORNER_COUNT = 8;

constexpr std::array<std::array<Face, 2>, 12> EDGE_COLORS =
{{
    {Up, Right},
    {Up, Left},
    {Up, Back},
    {Down, Right},
    {Down, Left},
    {Down, Back},
    {Front, Right},
    {Front, Left},
    {Up, Front},
    {Down, Front},
    {Back, Right},
    {Back, Left}
}};

constexpr int UD_SLICE = 8;

constexpr std::array<std::array<Face, 3>, 8> CORNER_COLORS =
{{
    {Up, Right, Front},
    {Up, Front, Left},
    {Up, Back, Right},
    {Up, Left, Back},
    {Down, Front, Right},
    {Down, Left, Front},
    {Down, Right, Back},
    {Down, Back, Left}
}};

constexpr std::array<std::array<std::array<int, 2>, 2>, 12> EDGE_POSITIONS =
{{
    {{{2, 1}, {1, 0}}},
    {{{0, 1}, {1, 0}}},
    {{{1, 0}, {1, 0}}},

    {{{2, 1}, {1, 2}}},
    {{{0, 1}, {1, 2}}},
    {{{1, 2}, {1, 2}}},
    {{{2, 1}, {0, 1}}},
    {{{0, 1}, {2, 1}}},
    {{{1, 2}, {1, 0}}},
    {{{1, 0}, {1, 2}}},
    {{{0, 1}, {2, 1}}},
    {{{2, 1}, {0, 1}}}
}};

constexpr std::array<std::array<std::array<int, 2>, 3>, 8> CORNER_POSITIONS =
{{
    {{{2, 2}, {0, 0}, {2, 0}}},
    {{{0, 2}, {0, 0}, {2, 0}}},
    {{{2, 0}, {0, 0}, {2, 0}}},
    {{{0, 0}, {0, 0}, {2, 0}}},
    {{{2, 0}, {2, 2}, {0, 2}}},
    {{{0, 0}, {2, 2}, {0, 2}}},
    {{{2, 2}, {2, 2}, {0, 2}}},
    {{{0, 2}, {2, 2}, {0, 2}}}
}};

constexpr std::array<std::array<Corner, 4>, 6> FACE_CORNERS =
{{
    {ULB, URB, URF, ULF},
    {DLF, DRF, DRB, DLB},
    {URF, URB, DRB, DRF},
    {ULB, ULF, DLF, DLB},
    {ULF, URF, DRF, DLF},
    {URB, ULB, DLB, DRB},
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

const std::map<std::string, Move> MOVE_NAMES =
{
    {"U1", U1},
    {"U2", U2},
    {"U3", U3},
    {"D1", D1},
    {"D2", D2},
    {"D3", D3},
    {"R1", R1},
    {"R2", R2},
    {"R3", R3},
    {"L1", L1},
    {"L2", L2},
    {"L3", L3},
    {"F1", F1},
    {"F2", F2},
    {"F3", F3},
    {"B1", B1},
    {"B2", B2},
    {"B3", B3},
};