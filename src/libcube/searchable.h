#pragma once
#include <vector>
#include "defs.h"

template<typename Coord, typename Implementation>
class Searchable
{
public:
    int estimateDistanceLeft(Coord coord) const
    {
        return (static_cast<Implementation const*>(this))->estimateDistanceLeft(coord);
    };
    const std::vector<Move>& getMoves(Coord coord, Move last_move)
    {
        return (static_cast<Implementation*>(this))->getMoves(coord, last_move);
    };
    Coord move(Coord coord, Move move) const
    {
        return (static_cast<Implementation const*>(this))->move(coord, move);
    }
    int getMaxDepth() const
    {
        return (static_cast<Implementation const*>(this))->getMaxDepth();
    }
};