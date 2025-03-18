#include "cubie_cube.h"
#include "coord_cube.h"
#include "face_cube.h"
#include "defs.h"
#include "util.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

CubieCube::CubieCube()
{
    reset();
}

CubieCube::CubieCube(const CoordCube& c)
{
    invEdgePermCoord(c.edgePermCoord);
    invCornerPermCoord(c.cornerPermCoord);
    invEdgeOriCoord(c.edgeOriCoord);
    invCornerOriCoord(c.cornerOriCoord);
}

CubieCube::CubieCube(const FaceCube& c)
{
    for(int i = 0; i < CORNER_COUNT; i++)
    {
        std::array<Face, 3> colors;

        for(int j = 0; j < 3; j++)
        {
            colors[j] = c.facelets[CORNER_COLORS[i][j]][CORNER_POSITIONS[i][j]];
        }

        int r;
        int j;

        for(r = 0; r < 3; r++)
        {
            for(j = 0; j < CORNER_COUNT; j++)
            {
                if(std::ranges::equal(CORNER_COLORS[j], colors)) {break; }
            }

            if(j != CORNER_COUNT) {break; }

            std::ranges::rotate(colors, colors.end() - 1);
        }

        cornerPerm[i] = static_cast<Corner>(j);
        cornerOri[i] = r;

    }

    for(int i = 0; i < EDGE_COUNT; i++)
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
            for(j = 0; j < EDGE_COUNT; j++)
            {
                if(std::ranges::equal(EDGE_COLORS[j], colors)) {break; }
            }

            if(j != EDGE_COUNT) {break; }

            std::ranges::rotate(colors, colors.end() - 1);
        }

        edgePerm[i] = static_cast<Edge>(j);
        edgeOri[i] = r;

    }
}

void CubieCube::reset()
{
    for (int i = 0; i < CORNER_COUNT; i++)
    {
        cornerPerm[i] = static_cast<Corner>(i);
    }

    for (int i = 0; i < EDGE_COUNT; i++)
    {
        edgePerm[i] = static_cast<Edge>(i);
    }

}

bool CubieCube::isSolved()
{
    for (int i = 0; i < CORNER_COUNT; i++)
    {
        if(cornerPerm[i] != i | cornerOri[i] != 0)
        {
            return false;
        }
    }

    for (int i = 0; i < EDGE_COUNT; i++)
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
    int amount = m % 3 + 1;
    Face face = static_cast<Face>(m / 3);

    std::array<Edge, 4> ep;
    std::array<Corner, 4> cp;
    std::array<bool, 4> eo;
    std::array<int, 4> co;
    for (int i = 0; i < 4; i++)
    {
        ep[i] = edgePerm[FACE_EDGES[face][i]];
        cp[i] = cornerPerm[FACE_CORNERS[face][i]];
        eo[i] = edgeOri[FACE_EDGES[face][i]];
        co[i] = cornerOri[FACE_CORNERS[face][i]];
    }

    int mod = 4 - (amount % 4);

    for (int i = 0; i < 4; i++)
    {
        int j = (mod + i) % 4;
        edgePerm[FACE_EDGES[face][i]] = ep[j];
        cornerPerm[FACE_CORNERS[face][i]] = cp[j];
        edgeOri[FACE_EDGES[face][i]] = eo[j];
        cornerOri[FACE_CORNERS[face][i]] = co[j];
    }

    if (amount % 2 == 0) {return;}

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
    std::array<bool, EDGE_COUNT> perms = {};
    
    int factorial = 479001600;
    for(int i = EDGE_COUNT; i > 0; i--)
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
    std::array<bool, CORNER_COUNT> perms = {};
    
    int factorial = 40320;
    for(int i = CORNER_COUNT; i > 0; i--)
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
    for (int i = EDGE_COUNT - 1; i > 0; i--)
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
    for (int i = CORNER_COUNT - 1; i > 0; i--)
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

    for (int i = 1; i < CORNER_COUNT; i++)
    {
        coord = (3 * coord) + cornerOri[i];
    }

    return coord;
}

int CubieCube::toEdgeOriCoord()
{
    int coord = 0;

    for (int i = 1; i < EDGE_COUNT; i++)
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
    std::array<bool, EDGE_COUNT> occupied {};
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

    for(int i = 0; i < EDGE_COUNT; i++)
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

void CubieCube::multiplyEdges(CubieCube& cube)
{
    for(int i = 0; i < EDGE_COUNT; i++)
    {
        edgePerm[i] = static_cast<Edge>((edgePerm[i] + cube.edgePerm[i]) % EDGE_COUNT);

        edgeOri[i] = (edgeOri[i] + cube.edgeOri[i]) % 2;
    }
}

void CubieCube::multiplyCorners(CubieCube& cube)
{
    for(int i = 0; i < CORNER_COUNT; i++)
    {
        cornerPerm[i] = static_cast<Corner>((cornerPerm[i] = cube.cornerPerm[i]) % CORNER_COUNT);

        cornerOri[i] = (cornerOri[i] + cube.cornerOri[i] % 3);
    }
}