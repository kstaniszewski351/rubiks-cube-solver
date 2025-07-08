#pragma once

#include <array>

// enum Move
// {
//     U1,
//     U2,
//     U3,
//     D1,
//     D2,
//     D3,
//     R1,
//     R2,
//     R3,
//     L1,
//     L2,
//     L3,
//     F1,
//     F2,
//     F3,
//     B1,
//     B2,
//     B3,
//     MoveCount
// };

enum Corner
{
    URF,
    UFL,
    UBR,
    ULB,
    DFR,
    DLF,
    DRB,
    DBL,
    CornerCount
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
    BL,
    EdgeCount
};

enum Face
{
    Up,
    Down,
    Right,
    Left,
    Front,
    Back,
    FaceCount
};

struct Move
{
    Move(Face face, int rotations) : face(face), rotations(rotations) {}
    Face face;
    int rotations;
};

constexpr int CORNER_ORI_COUNT = 2187;
constexpr int EDGE_ORI_COUNT = 2048;
constexpr int CORNER_PERM_COUNT = 40320;
constexpr int EDGE_PERM_COUNT = 479001600;
constexpr int UDSLICE_PERM_COUNT = 495;
constexpr int SYM_COUNT = 48;
constexpr int UD_SLICE = 8;

constexpr std::array<std::array<Face, 2>, EdgeCount> EDGE_COLORS =
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

constexpr int FACELET_COUNT = 8;
constexpr int CENTER = 4;

constexpr std::array<std::array<int, 2>, EdgeCount> EDGE_POSITIONS = 
{{
    {{1, 6}},
    {{6, 1}},
    {{3, 4}},
    {{1, 1}},
    {{6, 6}},
    {{4, 3}},
    {{1, 4}},
    {{6, 4}},
    {{4, 3}},
    {{3, 4}},
    {{1, 3}},
    {{6, 3}},
}};

//the indexes are arranged in clockwise order, the first being on U or D face
constexpr std::array<std::array<int, 3>, CornerCount> CORNER_POSITIONS =
{{
    {{2, 7, 0}},
    {{7, 5, 2}},
    {{0, 2, 5}},
    {{5, 0, 7}},
    {{0, 2, 2}},
    {{5, 7, 7}},
    {{2, 0, 0}},
    {{7, 5, 5}}
}};