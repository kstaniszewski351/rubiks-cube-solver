#pragma once

#include <array>
#include <map>
#include <string>
#include <unordered_set>

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
    UFL,
    UBR,
    ULB,
    DFR,
    DLF,
    DRB,
    DBL
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

constexpr int CORNER_ORI_COUNT = 2187;
constexpr int EDGE_ORI_COUNT = 2048;
constexpr int CORNER_PERM_COUNT = 40320;
constexpr int EDGE_PERM_COUNT = 479001600;
constexpr int UDSLICE_PERM_COUNT = 495;

constexpr int EDGE_COUNT = 12;
constexpr int CORNER_COUNT = 8;
constexpr int FACE_COUNT = 6;
constexpr int FACELET_COUNT = 8;

constexpr int CENTER = 4;
constexpr int UD_SLICE = 8;

constexpr std::array<std::array<Face, 2>, EDGE_COUNT> EDGE_COLORS =
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

const std::array<std::array<Face, 3>, CORNER_COUNT> CORNER_COLORS =
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

constexpr std::array<std::array<int, 2>, EDGE_COUNT> EDGE_POSITIONS = 
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

//the indexes need to be arranged in clockwise order starting from U or D face
constexpr std::array<std::array<int, 3>, CORNER_COUNT> CORNER_POSITIONS =
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

constexpr std::array<char, FACE_COUNT> FACE_NAMES
{
    'W',
    'Y',
    'R',
    'O',
    'G',
    'B'
};

constexpr std::array<int, FACE_COUNT> FACE_STRING_INDEX
{
    42,
    48,
    3,
    81,
    45,
    39
};

constexpr CubieCube S_U4;