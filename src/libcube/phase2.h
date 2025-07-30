#include "coords/ud_slice_perm_generator.h"
#include "coords/corner_perm_generator.h"
#include "coords/ud_perm_generator.h"
#include <vector>


class Phase2
{
public:
    Phase2();
    std::vector<Move> solve(const CubieCube& cube);
private:

    struct Phase2Coord
    {
        int flip;
        int slice_pos;
        int twist;
    };

    int Search(std::vector<Phase2Coord>& coord_stack, std::vector<Move>& move_stack, int depth, int bound);
    int estimateDistanceLeft(Phase2Coord coord);
    Phase2Coord moveCoord(Phase2Coord coord, Move m);
};