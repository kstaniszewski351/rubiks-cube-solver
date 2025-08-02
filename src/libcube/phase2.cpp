#include "phase2.h"
#include "move.h"

const std::vector<Move> phase_2_moves
{
    U,
    U2,
    UP,
    D,
    D2,
    DP,
    R2,
    L2,
    F2,
    B2
};

constexpr int phase_2_max_depth = 18;

Phase2::Phase2() :
    corner_perm_moves_(&corner_perm_gen_, phase_2_moves),
    ud_perm_moves_(&ud_perm_gen_, phase_2_moves),
    ud_slice_perm_moves_(&ud_slice_perm_gen_, phase_2_moves),
    corner_perm_ud_slice_perm_pruning({&corner_perm_moves_, &ud_slice_perm_moves_}, {&corner_perm_gen_, &ud_slice_perm_gen_}, phase_2_moves.size()),
    ud_perm_ud_slice_perm_pruning({&ud_perm_moves_, &ud_slice_perm_moves_}, {&ud_perm_gen_, &ud_slice_perm_gen_}, phase_2_moves.size())
{
}

std::vector<Move> Phase2::solve(const CubieCube& cube)
{
    Phase2Coord coord;
    coord.corner_perm = corner_perm_gen_.getCoord(cube);
    coord.ud_perm = ud_perm_gen_.getCoord(cube);
    coord.ud_slice_perm = ud_slice_perm_gen_.getCoord(cube);

    std::vector<Phase2Coord> coord_stack;
    std::vector<Move> move_stack;

    coord_stack.reserve(phase_2_max_depth);
    move_stack.reserve(phase_2_max_depth - 1);

    int bound = estimateDistanceLeft(coord);
    coord_stack.push_back(coord);
    
    while(true)
    {
        bound = IDASearch(coord_stack, move_stack, 0, bound);
        if(bound == 0) {break;}
    }
    move_stack.shrink_to_fit();

    return move_stack;
}

int Phase2::IDASearch(std::vector<Phase2Coord>& coord_stack, std::vector<Move>& move_stack, int depth, int bound)
{
    const Phase2Coord coord = coord_stack.back();
    const int distance_left = estimateDistanceLeft(coord);
    const int total_distance = depth + distance_left;

    if(total_distance > bound) { return total_distance; }
    if(distance_left == 0) { return 0; }
    
    int min_distance = -1;
    
    for(int move_index = 0; move_index < phase_2_moves.size(); move_index++)
    {
        Move move = phase_2_moves[move_index];

        if(isMoveRedundant(move, move_stack.begin(), move_stack.end())) {continue;}

        Phase2Coord new_coord = moveCoord(coord, move_index);
        coord_stack.push_back(new_coord);
        move_stack.push_back(move);

        const int distance_left = IDASearch(coord_stack, move_stack, depth + 1, bound);
        if(distance_left == 0)
        {
            return distance_left;
        }
        
        if(distance_left < min_distance || min_distance == -1) {min_distance = distance_left; }

        coord_stack.pop_back();
        move_stack.pop_back();
    }
    return min_distance;
};

int Phase2::estimateDistanceLeft(Phase2Coord coord)
{
    const std::array<int, 2> corner_perm_ud_slice_perm_buff = {coord.corner_perm, coord.ud_slice_perm};
    const std::array<int, 2> ud_perm_ud_slice_perm_buff = {coord.ud_perm, coord.ud_slice_perm};

    const int corner_perm_ud_slice_perm_distance = corner_perm_ud_slice_perm_pruning.getDistance(corner_perm_ud_slice_perm_buff.begin());
    const int ud_perm_ud_slice_perm_distance = ud_perm_ud_slice_perm_pruning.getDistance(ud_perm_ud_slice_perm_buff.begin());

    return std::max(corner_perm_ud_slice_perm_distance, ud_perm_ud_slice_perm_distance);
}

Phase2Coord Phase2::moveCoord(Phase2Coord coord, int move_index)
{
    Phase2Coord new_coord;

    new_coord.corner_perm = corner_perm_moves_.get(coord.corner_perm, move_index);
    new_coord.ud_perm = ud_perm_moves_.get(coord.ud_perm, move_index);
    new_coord.ud_slice_perm = ud_slice_perm_moves_.get(coord.ud_slice_perm, move_index);

    return new_coord;
}

