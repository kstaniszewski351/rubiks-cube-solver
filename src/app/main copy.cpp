#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "cubie_cube.h"
#include "coord_cube.h"
#include "coord_moves.h"
#include "face_cube.h"
#include "symmetries.h"
#include "defs.h"
#include "util.h"
#include "symmetries.h"
#include "const.h"

CubieCube cube = CubieCube();

void printFaceCube(const FaceCube& f_cube)
{
    constexpr int ROWS = 9;
    constexpr int COLUMNS = 12;

    std::array<Face, ROWS*COLUMNS> bitmap;
    bitmap.fill(FaceCount); 

    for(int f = 0; f < FaceCount; f++)
    {
        int si = FACE_BITMAP_INDEX[f];
        for(int i = 0; i < 9; i++)
        {
            int x = i % 3;
            int y = i / 3;
            
            Face c;
            if(i == CENTER)
            {
                c = static_cast<Face>(f);
            }
            else if( i > CENTER)
            {
                c = f_cube.facelets[f][i - 1];
            }
            else
            {
                c = f_cube.facelets[f][i];
            }

            bitmap[si + x + y * COLUMNS] = c;
        }
    }

    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            Face color = bitmap[x + y * COLUMNS];

            if(color == FaceCount)
            {
                std::cout << "  ";
            }
            else
            {
                std::stringstream ss;
                ss << ANSI_BEGIN << ANSI_COLORS[color] << ANSI_MODE << " " << ANSI_BEGIN << ANSI_RESET_MODES << ANSI_MODE;
                std::string out = ss.str();
                
                std::cout << out << out;
            }
        }
        std::cout << "\n";
    }

    //std::cout << s;
    return;
}

FaceCube inputCube()
{
    FaceCube icube;
    while(true)
    {
        for(int i = 0; i < FaceCount; i++)
        {
        input:
            std::cout << FACE_NAMES[i] << ": ";
    
            std::string face;
            std::cin >> face;
    
            if(face.length() != FACELET_COUNT)
            {
                std::cout << "invalid lenght\n";
                goto input;
            }
    
            for(int j = 0; j < FACELET_COUNT; j++)
            {
                auto facelet = std::find(FACE_NAMES.begin(), FACE_NAMES.end(), face[j]);
    
                if(facelet == FACE_NAMES.end())
                {
                    std::cout << "invalid face color\n"; 
                    goto input;
                }
                else
                {
                    icube.facelets[i][j] = static_cast<Face>(std::distance(FACE_NAMES.begin(), facelet));
                }
            }
        }

        if(!icube.isValid())
        {
            std::cout << "invalid cube\n";
        }
        else
        {
            break;
        }
    }


    return icube;
}

void moveCube()
{
    while(true)
    {
        std::cout << "Input moves, r to reset, q to exit: \n";
        std::string input;

        std::getline(std::cin >> std::ws, input);

        if(input == "r")
        {
            cube.reset();
            continue;
        }

        if(input == "q")
        {
            return;
        }

        std::istringstream iss(input);
        std::string move;
        std::vector<Move> moves;
        bool success = true;

        while(iss >> move)
        {
            auto result = std::ranges::find(MOVE_NAMES, move);

            if(result == MOVE_NAMES.end())
            {
                std::cout << "invalid move: " << move << "\n";
                success = false;
                break;
            }

            moves.push_back(static_cast<Move>(std::distance(MOVE_NAMES.begin(), result)));
        }

        if(!success) { continue;}
        
        for(Move i : moves)
        {
            cube.move(i);
        }

    }
}

void testSyms()
{
    Symmetries* sym = new Symmetries();

    sym->generateSyms();

    bool single_color_faces = true;

    for(CubieCube c : sym->syms)
    {
        FaceCube f_cube(c);
        for(auto f : f_cube.facelets)
        {
            Face c0 = f[0];
            for(Face c : f)
            {
                if(c0 != c)
                {
                    single_color_faces = false;
                }
            }
        }
    }

    bool are_unique = true;

    for(int i = 0; i < SYM_COUNT; i++)
    {
        for(int j = 0; j < SYM_COUNT; j++)
        {
            if(j != i && sym->syms[i] == sym->syms[j])
            {
                are_unique = false;
            };
        }
    }
    delete sym;
    std::cout << "Are all the faces single color: " << single_color_faces << "\n";
    std::cout << "Are the symmetries unique: " << are_unique << "\n";
}

void printCubieCube()
{
    std::cout << "Edge permutation: ";
    for(Edge i: cube.edgePerm)
    {
        for(Face c: EDGE_COLORS[i])
        {
            std::cout << FACE_NAMES[c];
        }
        std::cout << " ";
    }
    std::cout << "\n";

    std::cout << "Corner permutation: ";
    for(Corner i: cube.cornerPerm)
    {
        for(Face c: CORNER_COLORS[i])
        {
            std::cout << FACE_NAMES[c];
        }
        std::cout << " ";
    }
    std::cout << "\n";

    std::cout << "Edge orientation: ";
    for(int i: cube.edgeFlip)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::cout << "Corner orientation: ";
    for(int i: cube.cornerOri)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

int main()
{
    while(true)
    {
        std::cout <<
        "\n"
        "Cube solver test\n"
        "1: Input cube\n"
        "2: Moves\n"
        "3: Test symmetries\n"
        "4: Print cube\n"
        "5: Print cube in cubie cube format\n"
        "q: exit\n";

        std::string input;

        std::cin >> input;

        if(input == "q")
        {
            break;
        }
        else if(input == "1")
        {
            cube = FaceCube(inputCube());
        }
        else if (input == "2")
        {
            moveCube();
        }
        else if (input == "3")
        {
            testSyms();
        }
        else if (input == "4")
        {
            FaceCube fcube(cube);
            printFaceCube(fcube);
        }
        else if (input == "5")
        {
            printCubieCube();
        }
        else
        {
            std:: cout << "invalid option\n";
        }
    };
    return 0;
}