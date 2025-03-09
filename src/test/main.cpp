#include <iostream>
#include "cubie_cube.h"
#include "coord_cube.h"
#include "coord_moves.h"
#include <vector>
#include "defs.h"
#include "util.h"

void printCube(CubieCube cube)
{
    auto model = cube.toFaceCube();

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                std::cout << model[i][j][k] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

int main()
{
    CubieCube cube = CubieCube();
    std::cout << cube.toUDSliceCoord() << "\n";

    printCube(cube);

    std::cout << cube.isSolved() << std::endl;
    std::cout << sizeof(cube) << std::endl;

    std::vector<Move> moves = {U3, L3, U3, F3, R2, B3, R1, F1, U1, B2, U1, B3, L1, U3, F1, U1, R1, F3};

    for (Move i : moves)
    {
        cube.move(i);
    }

    printCube(cube);
    
    //std::cout << cube.toUDSliceCoord() << "\n";
    //cube.reset();
    // while(true)
    // {
    //     std::string move;
    //     std::cin >> move;

    //     if(move == "reset")
    //     {
    //         cube.reset();
    //         continue;
    //     }

    //     auto result = MOVE_NAMES.find(move);

    //     if(result == MOVE_NAMES.end())
    //     {
    //         std::cout << "wrong move \n";
    //     }
    //     else
    //     {
    //         cube.move(result->second);
    //         printCube(cube);
    //     }
    // }

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