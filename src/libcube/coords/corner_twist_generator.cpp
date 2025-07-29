#include "corner_twist_generator.h"
#include <numeric>

int CornerTwistGenerator::getCoord(const CubieCube& cube) const
{
    return baseNEncode(3, cube.cornerOri.begin() + 1, cube.cornerOri.end());
}
void CornerTwistGenerator::invertCoord(int coord, CubieCube& cube) const
{
    baseNDecode(coord, 3, cube.cornerOri.begin() + 1, cube.cornerOri.end());

    const int sum = std::accumulate(cube.cornerOri.begin() + 1, cube.cornerOri.end(), 0);

    const int first = (3 - (sum % 3)) % 3;
    cube.cornerOri[0] = first;
}
int CornerTwistGenerator::getMaxCoord() const
{
    return n_coords_;
}