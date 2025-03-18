#include <string>
#include "face_cube.h"

FaceCube::FaceCube(const CubieCube& cube)
{
    // for(int i = 0; i < FACE_COUNT; i++)
    // {
    //     facelets[i][CENTER] = static_cast<Face>(i);
    // }

    for (int i = 0; i < CORNER_COUNT; i++)
    {

        for (int p = 0; p < 3; p++)
        {
            int r = (p + cube.cornerOri[i]) % 3;

            facelets[CORNER_COLORS[i][p]][CORNER_POSITIONS[i][p]] = CORNER_COLORS[cube.cornerPerm[i]][r];
        }
    }


    for (int i = 0; i < EDGE_COUNT; i++)
    {

        for (int p = 0; p < 2; p++)
        {
            int r = (p + cube.edgeOri[i]) % 2;

            facelets[EDGE_COLORS[i][p]][EDGE_POSITIONS[i][p]] = EDGE_COLORS[cube.edgePerm[i]][r];
        }
    }
}

std::string FaceCube::toString()
{
    constexpr int ROWS = 9;
    constexpr int COLUMNS = 13;
    std::string s(COLUMNS * ROWS, ' ');

    for(int i = 1; i <= ROWS; i++)
    {
        s.at(i * COLUMNS - 1) = '\n';
    }

    for(int f = 0; f < FACE_COUNT; f++)
    {
        int si = FACE_STRING_INDEX[f];
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
                c = facelets[f][i - 1];
            }
            else
            {
                c = facelets[f][i];
            }

            s.at(si + x + y * COLUMNS) = FACE_NAMES[c];
        }
    }
    return s;
}