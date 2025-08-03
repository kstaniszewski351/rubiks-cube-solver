#include "pruning.h"

#include "multi_index.h"

std::vector<int> getMaxCoords(
    const std::vector<CoordGenerator const*>& generators) {
  std::vector<int> result;
  result.reserve(generators.size());

  for (auto generator : generators) {
    result.push_back(generator->GetMaxCoord());
  }

  return result;
}

Pruning::Pruning(std::vector<MoveTable const*> move_tables,
                 std::vector<CoordGenerator const*> generators, int n_moves)
    : indexer_(getMaxCoords(generators)), table_(indexer_.GetMaxIndex(), -1) {
  auto coord_buffer = std::vector<int>(move_tables.size(), 0);
  int n_set = 0;
  int iter = 0;

  table_[0] = 0;
  n_set++;
  iter++;
  distrib_.push_back(1);

  while (n_set < indexer_.GetMaxIndex()) {
    int n_set_this_iter = 0;
    for (int index = 0; index < indexer_.GetMaxIndex(); index++) {
      if (table_[index] == iter - 1) {
        indexer_.ToRaw(index, coord_buffer.end());

        for (int move = 0; move < n_moves; move++) {
          for (int i = 0; i < coord_buffer.size(); i++) {
            coord_buffer[i] = move_tables[i]->Get(coord_buffer[i], move);
          }

          const int new_coord = indexer_.FromRaw(coord_buffer.begin());

          if (table_[new_coord] == -1) {
            table_[new_coord] = iter;
            n_set_this_iter++;
            n_set++;
          }
        }
      }
    }
    iter++;
    distrib_.push_back(n_set_this_iter);
  }
  distrib_.shrink_to_fit();
}

const std::vector<int>& Pruning::GetDistrib() const { return distrib_; }

int Pruning::GetSize() const { return indexer_.GetMaxIndex(); }
