#include "face_cube.h"
#include "cubie_cube.h"
#include <algorithm>
#include <unordered_set>



FaceCube::FaceCube()
{
    reset();
};

void FaceCube::reset()
{
    for(int i = 0; i < FaceCount; i++)
    {
        for(int j = 0; j < FACELET_COUNT; j++)
        {
            facelets[i * FACELET_COUNT + j] = static_cast<Face>(i);
        }
    };
}

FaceCube::FaceCube(const CubieCube& cube)
{
    // for(int i = 0; i < FaceCount; i++)
    // {
    //     facelets[i][CENTER] = static_cast<Face>(i);
    // }

    for(int i = 0; i < CornerCount; i++)
    {

        for(int p = 0; p < 3; p++)
        {
            int r = 0;
            if(cube.cornerOri[i] < 3)
            {
                r = (p + cube.cornerOri[i]) % 3;
            }
            else
            {
                r = ((p + cube.cornerOri[i]) % 3 + p) % 3;
            }

            facelets[CORNER_COLORS[i][p] * FACELET_COUNT + CORNER_POSITIONS[i][p]] = CORNER_COLORS[cube.cornerPerm[i]][r];
        }
    }


    for(int i = 0; i < EdgeCount; i++)
    {

        for(int p = 0; p < 2; p++)
        {
            int r = (p + cube.edgeFlip[i]) % 2;

            facelets[EDGE_COLORS[i][p] * FACELET_COUNT + EDGE_POSITIONS[i][p]] = EDGE_COLORS[cube.edgePerm[i]][r];
        }
    }
}

void FaceCube::move(Move m)
{

}

//checks if cube can be safely converted to CubieCube
bool FaceCube::isValid()
{
    std::array<int, FaceCount> count {};

    for(int i = 0; i < FaceCount; i++)
    {
        for(int j = 0; j < FACELET_COUNT; j++)
        {
            count[facelets[i * FACELET_COUNT + j]] ++;
        }
    }

    for(int i : count)
    {
        if(i != FACELET_COUNT)
        {
            return false;
        }
    }

    for(int i = 0; i < CornerCount; i++)
    {
        std::unordered_set<Face> colors;

        for(int j = 0; j < 3; j ++)
        {
            if(!colors.insert(facelets[CORNER_COLORS[i][j] * FACELET_COUNT + CORNER_POSITIONS[i][j]]).second)
            {
                return false;
            };
        }
    }

    return true;
}