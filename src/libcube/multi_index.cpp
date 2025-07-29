#include "multi_index.h"
#include <algorithm>

int calculateMaxIndex(const std::vector<int> indexes)
{
    int max_index = 1;

    for(int i = 0; i < indexes.size(); i++)
    {
        max_index *= indexes[i];
    }

    return max_index;
}

MultiIndex::MultiIndex(std::vector<int> max_indexes) :
    max_indexes_(std::move(max_indexes)),
    max_index_(calculateMaxIndex(max_indexes_))
{

}

int MultiIndex::getMaxIndex() const
{
    return max_index_;
}

