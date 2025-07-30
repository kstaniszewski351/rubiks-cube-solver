#pragma once
#include <vector>
#include "defs.h"

template<typename Coord>
class Searchable
{
public:
    virtual int estimateDistanceLeft(Coord coord) const;
    virtual const std::vector<Move>& getMoves(Coord coord, Move last_move);
    virtual Coord move(Coord coord, Move move) const;
    virtual int getMaxDepth() const;
};