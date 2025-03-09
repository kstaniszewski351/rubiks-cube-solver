#pragma once

class CubieCube;

class CoordCube
{
public:
    CoordCube();
    CoordCube(CubieCube* c);

    int cornerOriCoord{};
    int edgeOriCoord{};
    int cornerPermCoord{};
    int edgePermCoord{};
    
};