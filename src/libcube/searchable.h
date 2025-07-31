#pragma once
#include <vector>
#include "defs.h"

template<typename Coord>
class Searchable
{
public:
    virtual int estimateDistanceLeft(Coord coord) const = 0;
    virtual const std::vector<int>& getMoves(Coord coord, int last_move) = 0;
    virtual Coord move(Coord coord, int move) const = 0;
    virtual int getMaxDepth() const = 0;
};