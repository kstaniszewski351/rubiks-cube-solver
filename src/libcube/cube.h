#pragma once

enum Face
{
    Up,
    Down,
    Right,
    Left,
    Front,
    Back,
    FaceCount,
    InvalidFace
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
    DBL,
    CornerCount,
    InvalidCorner
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
    EdgeCount,
    InvalidEdge
};

enum Axis
{
    X,
    Y,
    Z,
    AxisCount,
    InvalidAxis
};