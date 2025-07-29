#include "multi_coord.h"
#include <vector>
#include <cassert>

MultiCoord::MultiCoord(std::vector<CoordGenerator*> generators) :
    generators_(std::move(generators)),
    n_coords_(generators_.size()),
    coord_count_(1)
{
    coord_sizes_.reserve(n_coords_);

    for(int i = 0; i < n_coords_; i++)
    {
        coord_sizes_.push_back(generators_[i]->getMaxCoord());

        coord_count_ *= coord_sizes_[i];
    }
    
}

int MultiCoord::getCoord(const CubieCube& cube) const
{
    int coord = 0;
    for(int i = 0; i < n_coords_; i++)
    {
        int raw = generators_[i]->getCoord(cube);
        int size = coord_sizes_[i];
        coord *= size;
        coord += raw;
    }
    return coord;
}

void MultiCoord::invertCoord(int coord, CubieCube& cube) const
{
    for(int i = n_coords_ - 1; i >= 0; i--)
    {
        int size = coord_sizes_[i];
        int raw = coord % size;
        coord /= size;
        generators_[i]->invertCoord(raw, cube);
    }
}





int MultiCoord::getMaxCoord() const
{
    return coord_count_;
}