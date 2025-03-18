#include <iostream>
#include "cubie_cube.h"
#include "coord_cube.h"
#include "coord_moves.h"
#include "face_cube.h"
#include <vector>
#include "defs.h"
#include "util.h"

int main()
{
    CubieCube cube = CubieCube();
    std::cout << cube.toUDSliceCoord() << "\n";


    std::cout << cube.isSolved() << "\n";
    std::cout << sizeof(cube) << "\n";

    std::vector<Move> moves = {F1, L1, F1, U3, R1, U1, F2, L2, U3, L3, B1, D3, B3, L2, U1};

    for (Move i : moves)
    {
        cube.move(i);
    }

    FaceCube face = FaceCube(cube);
    std::cout << face.toString();

    CubieCube two = CubieCube(face);

    std::cout << FaceCube(two).toString();
    
    std::cout << cube.toUDSliceCoord() << "\n";
    cube.reset();
    while(true)
    {
        std::string move;
        std::cin >> move;

        if(move == "reset")
        {
            cube.reset();
            continue;
        }

        auto result = MOVE_NAMES.find(move);

        if(result == MOVE_NAMES.end())
        {
            std::cout << "wrong move \n";
        }
        else
        {
            cube.move(result->second);
            face = FaceCube(cube);
            std::cout << face.toString();
        }
    }

    CoordMoves* c_moves = new CoordMoves();
    c_moves->GenerateMoves();

    // std::cout << cube.isSolved() << "\n";
    // CoordCube cord = CoordCube(&cube);
    // CubieCube cube2 = CubieCube(&cord);
    // int coord = cube.toUDSliceCoord();
    // cube = CubieCube();
    // cube.invUDSliceCoord(coord);
    // printCube(cube2);
    // printCube(cube);
    return 0;
}