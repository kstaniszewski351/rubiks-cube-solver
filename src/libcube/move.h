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


Face GetMoveFace(Move move);
Axis GetFaceAxis(Face face);

template<typename Iterator>
bool IsMoveRedundant(Move move, Iterator sequence_begin, Iterator sequence_end)
{
    Iterator it = sequence_end - 1;

    const Face face = GetMoveFace(move);
    const Axis axis = GetFaceAxis(face);

    while(it >= sequence_begin)
    {
        const Face last_face = GetMoveFace(*it);
        const Axis last_axis = GetFaceAxis(last_face);

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

std::vector<Move> RandomScramble(int lenght, int seed);
