#include "cubie_cube.h"
#include "face_cube.h"
#include "defs.h"
#include "assert.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

CubieCube::CubieCube()
{
    reset();
}

CubieCube::CubieCube(const std::array<Edge, EdgeCount>& ep, const std::array<Corner, CornerCount>& cp, const std::array<bool, EdgeCount>& eo, const std::array<int, CornerCount>& co)
    :edgePerm(ep), cornerPerm(cp), edgeFlip(eo), cornerOri(co)
{
    
}

CubieCube::CubieCube(const FaceCube& c)
{
    for(int i = 0; i < CornerCount; i++)
    {
        std::array<Face, 3> colors;

        for(int j = 0; j < 3; j++)
        {
            colors[j] = c.facelets[CORNER_COLORS[i][j] * FACELET_COUNT + CORNER_POSITIONS[i][j]];
        }

        int r;
        int j;

        for(r = 0; r < 6; r++)
        {
            for(j = 0; j < CornerCount; j++)
            {
                if(std::ranges::equal(CORNER_COLORS[j], colors)) {break; }
            }

            if(j != CornerCount) {break; }


            if(r <= 3)
            {
                //rotate right
                std::ranges::rotate(colors, colors.end() - 1);
            }

            else if(r >= 3)
            {
                //rotate left
                std::ranges::rotate(colors, colors.begin() + 1);
            }
        }

        cornerPerm[i] = static_cast<Corner>(j);
        cornerOri[i] = r;

    }

    for(int i = 0; i < EdgeCount; i++)
    {
        std::array<Face, 2> colors;

        for(int j = 0; j < 2; j++)
        {
            colors[j] = c.facelets[EDGE_COLORS[i][j] * FACELET_COUNT + EDGE_POSITIONS[i][j]];
        }

        int r;
        int j;

        for(r = 0; r < 2; r++)
        {
            for(j = 0; j < EdgeCount; j++)
            {
                if(std::ranges::equal(EDGE_COLORS[j], colors)) {break; }
            }

            if(j != EdgeCount) {break; }

            std::ranges::rotate(colors, colors.end() - 1);
        }

        edgePerm[i] = static_cast<Edge>(j);
        edgeFlip[i] = r;

    }
}

bool CubieCube::operator==(const CubieCube& c) const
{
    return edgePerm == c.edgePerm && cornerPerm == c.cornerPerm && edgeFlip == c.edgeFlip && cornerOri == c.cornerOri;
}

bool CubieCube::operator!=(const CubieCube& c) const
{
    return !operator==(c);
}


void CubieCube::reset()
{
    for (int i = 0; i < CornerCount; i++)
    {
        cornerPerm[i] = static_cast<Corner>(i);
        cornerOri[i] = 0;
    }

    for (int i = 0; i < EdgeCount; i++)
    {
        edgePerm[i] = static_cast<Edge>(i);
        edgeFlip[i] = 0;
    }

}

bool CubieCube::isSolved() const
{
    for (int i = 0; i < CornerCount; i++)
    {
        if(cornerPerm[i] != i | cornerOri[i] != 0)
        {
            return false;
        }
    }

    for (int i = 0; i < EdgeCount; i++)
    {
        if(edgePerm[i] != i | edgeFlip[i] != 0)
        {
            return false;
        }
    }

    return true;
}

void CubieCube::move(Move move)
{
    int face = static_cast<Face>(move / 3);
    int n_rotations = (move % 3) + 1;

    std::array<Edge, 4> ep;
    std::array<Corner, 4> cp;
    std::array<bool, 4> eo;
    std::array<int, 4> co;
    for (int i = 0; i < 4; i++)
    {
        ep[i] = edgePerm[FACE_EDGES[face][i]];
        cp[i] = cornerPerm[FACE_CORNERS[face][i]];
        eo[i] = edgeFlip[FACE_EDGES[face][i]];
        co[i] = cornerOri[FACE_CORNERS[face][i]];
    }

    int mod = 4 - (n_rotations % 4);

    for (int i = 0; i < 4; i++)
    {
        int j = (mod + i) % 4;
        edgePerm[FACE_EDGES[face][i]] = ep[j];
        cornerPerm[FACE_CORNERS[face][i]] = cp[j];
        edgeFlip[FACE_EDGES[face][i]] = eo[j];
        cornerOri[FACE_CORNERS[face][i]] = co[j];
    }

    if (n_rotations % 2 == 0) {return;}

    switch (face)
    {
        case Right:
            updateCorner(URF, 1);
            updateCorner(UBR, 2);
            updateCorner(DRB, 1);
            updateCorner(DFR, 2);
            break;
        case Left:
            updateCorner(UFL, 2);
            updateCorner(ULB, 1);
            updateCorner(DBL, 2);
            updateCorner(DLF, 1);
            break;
        case Front:
            edgeFlip[UF] = !edgeFlip[UF];
            edgeFlip[FR] = !edgeFlip[FR];
            edgeFlip[FL] = !edgeFlip[FL];
            edgeFlip[DF]= !edgeFlip[DF];
            updateCorner(URF, 2);
            updateCorner(DFR, 1);
            updateCorner(DLF, 2);
            updateCorner(UFL, 1);
            break;
        case Back:
            edgeFlip[UB] = !edgeFlip[UB];
            edgeFlip[BR] = !edgeFlip[BR];
            edgeFlip[BL] = !edgeFlip[BL];
            edgeFlip[DB] = !edgeFlip[DB];

            updateCorner(UBR, 1);
            updateCorner(DRB, 2);
            updateCorner(DBL, 1);
            updateCorner(ULB, 2);
            break;
    }
}

void CubieCube::updateCorner(Corner c, int amount)
{
    cornerOri[c] = (cornerOri[c] + amount) % 3;
}

void CubieCube::multiplyEdges(const CubieCube& cube)
{
    std::array<Edge, EdgeCount> ep;
    std::array<bool, EdgeCount> eo;

    for(int i = 0; i < EdgeCount; i++)
    {
        ep[i] = edgePerm[cube.edgePerm[i]];

        eo[i] = (cube.edgeFlip[i] + edgeFlip[cube.edgePerm[i]]) % 2;
    }

    edgePerm = ep;
    edgeFlip = eo;
}

void CubieCube::multiplyCorners(const CubieCube& cube)
{

    std::array<Corner, CornerCount> cp;
    std::array<int, CornerCount> co;

    for(int i = 0; i < CornerCount; i++)
    {
        cp[i] = cornerPerm[cube.cornerPerm[i]];

        int ori = 0;
        int a = cornerOri[cube.cornerPerm[i]];
        int b = cube.cornerOri[i];
        //both are regular, ori < 3
        if(a < 3 && b < 3)
        {
            ori = a + b;
            if(ori >= 3) {ori -= 3;}
        }
        //one is mirrored
        else if(a < 3 && b >= 3)
        {
            ori = a + b;
            if(ori >= 6) {ori -= 3;};
        }
        //one is mirrored
        else if((a >= 3 && b < 3))
        {
            ori = a - b;
            if(ori < 3) {ori += 3;}
        }
        //both are mirrored, ori < 3
        else if(a >= 3 && b >= 3)
        {
            ori = a - b;
            if(ori < 0) {ori += 3;}
        }
        else
        {
            assert(false);
        }

        co[i] = ori;
    }

    cornerPerm = cp;
    cornerOri = co;
}

void CubieCube::multiply(const CubieCube& cube)
{
    multiplyCorners(cube);
    multiplyEdges(cube);
}


constexpr std::array<int, FaceCount> face_string_index
{
    42,
    48,
    3,
    81,
    45,
    39
};

constexpr std::array<char, FaceCount> face_names
{
    'W',
    'Y',
    'R',
    'O',
    'G',
    'B'
};

constexpr int n_rows = 9;
constexpr int n_columns = 13;

std::ostream& operator<<(std::ostream& os, const CubieCube& cube)
{
    FaceCube f_cube = cube;
    std::string s(n_columns * n_rows, ' ');

    for(int i = 1; i <= n_rows; i++)
    {
        s.at(i * n_columns - 1) = '\n';
    }

    for(int f = 0; f < FaceCount; f++)
    {
        int si = face_string_index[f];
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
                c = f_cube.facelets[f * FACELET_COUNT + i - 1];
            }
            else
            {
                c = f_cube.facelets[f * FACELET_COUNT + i];
            }

            s.at(si + x + y * n_columns) = face_names[c];
        }
    }
    return os << "\n" << s;
}