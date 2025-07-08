#include "cubie_cube.h"
#include "coord_cube.h"
#include "face_cube.h"
#include "defs.h"
#include "assert.h"
#include "util.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

CubieCube::CubieCube()
{
    reset();
}

CubieCube::CubieCube(const std::array<Edge, EdgeCount>& ep, const std::array<Corner, CornerCount>& cp, const std::array<bool, EdgeCount>& eo, const std::array<int, CornerCount>& co)
    :edgePerm(ep), cornerPerm(cp), edgeOri(eo), cornerOri(co)
{}

CubieCube::CubieCube(const CoordCube& c)
{
    invEdgePermCoord(c.edgePermCoord);
    invCornerPermCoord(c.cornerPermCoord);
    invEdgeOriCoord(c.edgeOriCoord);
    invCornerOriCoord(c.cornerOriCoord);
}

CubieCube::CubieCube(const FaceCube& c)
{
    for(int i = 0; i < CornerCount; i++)
    {
        std::array<Face, 3> colors;

        for(int j = 0; j < 3; j++)
        {
            colors[j] = c.facelets[CORNER_COLORS[i][j]][CORNER_POSITIONS[i][j]];
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
            colors[j] = c.facelets[EDGE_COLORS[i][j]][EDGE_POSITIONS[i][j]];
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
        edgeOri[i] = r;

    }
}

bool CubieCube::operator==(const CubieCube& c)
{
    return edgePerm == c.edgePerm && cornerPerm == c.cornerPerm && edgeOri == c.edgeOri && cornerOri == c.cornerOri;
}

bool CubieCube::operator!=(const CubieCube& c)
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
        edgeOri[i] = 0;
    }

}

bool CubieCube::isSolved()
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
        if(edgePerm[i] != i | edgeOri[i] != 0)
        {
            return false;
        }
    }

    return true;
}

void CubieCube::move(Move m)
{

    std::array<Edge, 4> ep;
    std::array<Corner, 4> cp;
    std::array<bool, 4> eo;
    std::array<int, 4> co;
    for (int i = 0; i < 4; i++)
    {
        ep[i] = edgePerm[FACE_EDGES[m.face][i]];
        cp[i] = cornerPerm[FACE_CORNERS[m.face][i]];
        eo[i] = edgeOri[FACE_EDGES[m.face][i]];
        co[i] = cornerOri[FACE_CORNERS[m.face][i]];
    }

    int mod = 4 - (m.rotations % 4);

    for (int i = 0; i < 4; i++)
    {
        int j = (mod + i) % 4;
        edgePerm[FACE_EDGES[m.face][i]] = ep[j];
        cornerPerm[FACE_CORNERS[m.face][i]] = cp[j];
        edgeOri[FACE_EDGES[m.face][i]] = eo[j];
        cornerOri[FACE_CORNERS[m.face][i]] = co[j];
    }

    if (m.rotations % 2 == 0) {return;}

    switch (m.face)
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
            edgeOri[UF] = !edgeOri[UF];
            edgeOri[FR] = !edgeOri[FR];
            edgeOri[FL] = !edgeOri[FL];
            edgeOri[DF]= !edgeOri[DF];
            updateCorner(URF, 2);
            updateCorner(DFR, 1);
            updateCorner(DLF, 2);
            updateCorner(UFL, 1);
            break;
        case Back:
            edgeOri[UB] = !edgeOri[UB];
            edgeOri[BR] = !edgeOri[BR];
            edgeOri[BL] = !edgeOri[BL];
            edgeOri[DB] = !edgeOri[DB];

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

void CubieCube::invEdgePermCoord(int coord)
{
    //tracks which digits were already used
    std::array<bool, EdgeCount> perms = {};
    
    int factorial = 479001600;
    for(int i = EdgeCount; i > 0; i--)
    {
        //get lehnmer code digit
        factorial /= i;
        int code = coord / factorial;
        coord %= factorial;

        int j = -1;
        while(code >= 0)
        {
            j++;
            if(perms[j] == false)
            {
                code -= 1;
            }

        }

        perms[j] = true;
        edgePerm[i - 1] = static_cast<Edge>(j);
    }

}

void CubieCube::invCornerPermCoord(int coord)
{
    //tracks which digits were already used
    std::array<bool, CornerCount> perms = {};
    
    int factorial = 40320;
    for(int i = CornerCount; i > 0; i--)
    {
        //get lehnmer code digit
        factorial /= i;
        int code = coord / factorial;
        coord %= factorial;

        int j = -1;
        while(code >= 0)
        {
            j++;
            if(perms[j] == false)
            {
                code -= 1;
            }

        }

        perms[j] = true;
        cornerPerm[i - 1] = static_cast<Corner>(j);
    }
}

void CubieCube::invEdgeOriCoord(int coord)
{
    int sum = 0;
    for (int i = EdgeCount - 1; i > 0; i--)
    {
        int eo = coord % 2;
        edgeOri[i] = eo;
        sum += eo;
        coord /= 2;
    }
    edgeOri[0] = sum % 2;
}

void CubieCube::invCornerOriCoord(int coord)
{
    int sum = 0;
    for (int i = CornerCount - 1; i > 0; i--)
    {
        int co = coord % 3;
        cornerOri[i] = co;
        
        sum += co;
        coord /= 3;
    }

    cornerOri[0] = (3 - sum % 3) % 3;
}

int CubieCube::toCornerOriCoord()
{
    int coord = 0;

    for (int i = 1; i < CornerCount; i++)
    {
        coord = (3 * coord) + cornerOri[i];
    }

    return coord;
}

int CubieCube::toEdgeOriCoord()
{
    int coord = 0;

    for (int i = 1; i < EdgeCount; i++)
    {
        coord = (2 * coord) + edgeOri[i];
    }


    return coord;
}

int CubieCube::toCornerPermCoord()
{
    int coord = 0;

    for(int i = 7; i > 0; i--)
    {
        int code = 0;
        for(int j = i; j >= 0; j--)
        {
            if(cornerPerm[j] < cornerPerm[i])
            {
                code++;
            }
        }

        coord = i * (code + coord);
    }

    return coord;
}

int CubieCube::toEdgePermCoord()
{
    int coord = 0;

    for(int i = 11; i > 0; i--)
    {
        int code = 0;
        for(int j = i; j >= 0; j--)
        {
            if(edgePerm[j] < edgePerm[i])
            {
                code++;
            }
        }

        coord = i * (code + coord);
    }

    return coord;
}

int CubieCube::toUDSliceCoord()
{
    int coord = 0;
    int k = 3;
    int n = 11;
    while(k >= 0)
    {
        if(edgePerm[n] >= UD_SLICE)
        {
            k -= 1;
        }
        else
        {
            coord += biCoeff(n, k);
        }
        n --;
    }

    return coord;
}

void CubieCube::invUDSliceCoord(int coord)
{
    std::array<bool, EdgeCount> occupied {};
    int k = 3;
    int n = 11;


    while(k >= 0)
    {
        int c = biCoeff(n, k);

        if(coord < c)
        {
            occupied[n] = true;
            k --;
        }
        else
        {
            coord = coord - c;
        }
        n --;
    }

    int slice = UD_SLICE;
    int other = 0;

    for(int i = 0; i < EdgeCount; i++)
    {
        if(occupied[i])
        {
            edgePerm[i] = static_cast<Edge>(slice);
            slice ++;
        }
        else
        {
            edgePerm[i] = static_cast<Edge>(other);
            other ++;
        }
    }
}

void CubieCube::multiplyEdges(const CubieCube& cube)
{
    std::array<Edge, EdgeCount> ep;
    std::array<bool, EdgeCount> eo;

    for(int i = 0; i < EdgeCount; i++)
    {
        ep[i] = edgePerm[cube.edgePerm[i]];

        eo[i] = (cube.edgeOri[i] + edgeOri[cube.edgePerm[i]]) % 2;
    }

    edgePerm = ep;
    edgeOri = eo;
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

        //regular multiply, 0 <= ori < 3
        if(a < 3 && b < 3)
        {
            ori = (a + b) % 3;
        }
        //multiply by mirrored, 3 <= ori < 6
        else if((a >= 3 && b < 3) || (a < 3 && b >= 3))
        {
            ori = (a + b - 3) % 3 + 3;
        }
        //multiply mirrored cube by mirrored cube, 0 <= ori < 3
        else if(a >= 3 && b >= 3)
        {
            ori = (a + b - 6) % 3;
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