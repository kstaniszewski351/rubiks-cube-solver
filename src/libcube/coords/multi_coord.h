#pragma once
#include "coord_generator.h"
#include <vector>
#include <memory>

class MultiCoord : public CoordGenerator
{
public:
    MultiCoord(std::vector<CoordGenerator*> generators);
    int getCoord(const CubieCube& cube) const override;
    void invertCoord(int coord, CubieCube& cube) const override;
    int getMaxCoord() const override;
    void getRaw(int coord, std::vector<int>& coords) const;

    template<typename Iterator>
    void getRaw(int coord, Iterator coords) const
    {
        for(int i = n_coords_ - 1; i >= 0; i--)
        {
            int size = coord_sizes_[i];
            int raw = coord % size;
            coord /= size;
            coords[i] = raw;
        }
    }

    template<typename Iterator>
    int invRaw(Iterator coords) const
    {
        int coord = 0;
        for(int i = 0; i < n_coords_; i++)
        {
            int raw = coords[i];
            int size = coord_sizes_[i];
            coord *= size;
            coord += raw;
        }
        return coord;
    }
private:
    std::vector<CoordGenerator*> generators_;
    std::vector<int> coord_sizes_;
    int n_coords_;
    int coord_count_;
};