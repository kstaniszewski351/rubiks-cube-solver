#pragma once

#include <vector>
#include "cube.h"

enum Move
{
    U,
    U2,
    UP,
    D,
    D2,
    DP,
    R,
    R2,
    RP,
    L,
    L2,
    LP,
    F,
    F2,
    FP,
    B,
    B2,
    BP,
    MoveCount,
    InvalidMove
};


Face getMoveFace(Move move);
Axis getFaceAxis(Face face);

template<typename Iterator>
bool isMoveRedundant(Move move, Iterator sequence_begin, Iterator sequence_end)
{
    Iterator it = sequence_end - 1;

    const Face face = getMoveFace(move);
    const Axis axis = getFaceAxis(face);

    while(it >= sequence_begin)
    {
        const Face last_face = getMoveFace(*it);
        const Axis last_axis = getFaceAxis(last_face);

        if(last_axis != axis)
        {
            return false;
        }
        else if(last_face == face)
        {
           return true;
        }

        it--;
    }

    return false;
}

std::vector<Move> randomScramble(int lenght, int seed);
