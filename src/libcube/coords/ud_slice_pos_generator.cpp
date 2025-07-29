#include "ud_slice_pos_generator.h"

constexpr int ud_slice_start = 8;

int UDSlicePosGenerator::getCoord(const CubieCube& cube) const
{
    return combinationEncode(cube.edgePerm, [](Edge e) {return e >= ud_slice_start; });
}

void UDSlicePosGenerator::invertCoord(int coord, CubieCube& cube) const
{
    auto combination = combinationDecode<12>(coord, 4);
    std::array<Edge, EdgeCount> edge_perm;

    int index = 0;
    int ud_slice_index = ud_slice_start;

    for(int i = 0; i < EdgeCount; i++)
    {
        if(combination[i])
        {
            edge_perm[i] = static_cast<Edge>(ud_slice_index);
            ud_slice_index ++;
        }
        else
        {
            edge_perm[i] = static_cast<Edge>(index);
            index ++;
        }
    }
    cube.edgePerm = edge_perm;
}
int UDSlicePosGenerator::getMaxCoord() const
{
    return n_coords_;
}