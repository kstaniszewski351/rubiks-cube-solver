#pragma once
#include <cstdint>

#include "move_table.h"
#include "multi_index.h"

class Pruning {
 public:
  Pruning(std::vector<MoveTable const*> move_tables,
          std::vector<CoordGenerator const*> generators,
          int n_moves = MoveCount);

  template <typename Iterator>
  int GetDistance(Iterator begin) const {
    return table_[indexer_.FromRaw(begin)];
  }

  int GetSize() const;
  const std::vector<int>& GetDistrib() const;

 private:
  const MultiIndex indexer_;
  std::vector<int8_t> table_;
  std::vector<int> distrib_;
};