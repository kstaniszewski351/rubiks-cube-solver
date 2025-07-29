#pragma once
#include "move_table.h"
#include "multi_index.h"
#include <cstdint>

class Pruning
{
public:
    Pruning(std::vector< MoveTable const*> move_tables, std::vector<CoordGenerator const*> generators, int n_moves = MOVE_COUNT);

    template<typename Iterator>
    int getDistance(Iterator begin) const
    {
        return table_[indexer_.fromRaw(begin)];
    }

    int getSize() const;
    const std::vector<int>& getDistrib() const;

private:
    const MultiIndex indexer_;
    std::vector<int8_t> table_;
    std::vector<int> distrib_;
};