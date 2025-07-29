#pragma once

#include <array>

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
    UF,
    DF,
    FR,
    FL,
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

// struct Move
// {
//     constexpr Move(Face face, int rotations) : face(face), rotations(rotations) {}
//     constexpr Move(int i)
//     {
//         face = static_cast<Face>(i / 3);
//         rotations = (i % 3) + 1;
//     }
//     constexpr int toInt()
//     {
//         return face * 3 + (rotations - 1);
//     }
//     Face face;
//     int rotations;
// };

enum Move
{
    U,
    U2,
    UP,
    D,
    D2,
    DP,
    R,
    R2,
    RP,
    L,
    L2,
    LP,
    F,
    F2,
    FP,
    B,
    B2,
    BP
};

constexpr int SYM_COUNT = 48;
constexpr int D4H_SYM_COUNT = 16;
constexpr int MOVE_COUNT = 18;

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

    {{4, 3}},
    {{3, 4}},
    {{1, 4}},
    {{6, 4}},
    {{1, 3}},
    {{6, 3}}
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