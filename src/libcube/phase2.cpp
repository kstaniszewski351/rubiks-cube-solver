#include "phase2.h"

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

Phase2::Phase2() :
    corner_perm_moves_(&corner_perm_gen_, phase_2_moves),
    ud_perm_moves_(&ud_perm_gen_, phase_2_moves),
    ud_slice_perm_moves_(&ud_slice_perm_gen_, phase_2_moves),
    corner_perm_ud_slice_perm_pruning({&corner_perm_moves_, &ud_slice_perm_moves_}, {&corner_perm_gen_, &ud_slice_perm_gen_}, phase_2_moves.size()),
    ud_perm_ud_slice_perm_pruning({&ud_perm_moves_, &ud_slice_perm_moves_}, {&ud_perm_gen_, &ud_slice_perm_gen_}, phase_2_moves.size()),
    search_(this)
{
    move_buffer_.reserve(phase_2_moves.size());
}

std::vector<Move> Phase2::solve(const CubieCube& cube)
{
    Phase2Coord coord;
    coord.corner_perm = corner_perm_gen_.getCoord(cube);
    coord.ud_perm = ud_perm_gen_.getCoord(cube);
    coord.ud_slice_perm = ud_slice_perm_gen_.getCoord(cube);

    std::vector<int> solution_move_indexes = search_.search(coord);
    std::vector<Move> solution;
    solution.reserve(solution_move_indexes.size());

    for(int index : solution_move_indexes)
    {
        solution.push_back(phase_2_moves[index]);
    }

    return solution;
}

int Phase2::estimateDistanceLeft(Phase2Coord coord) const
{
    const std::array<int, 2> corner_perm_ud_slice_perm_buff = {coord.corner_perm, coord.ud_slice_perm};
    const std::array<int, 2> ud_perm_ud_slice_perm_buff = {coord.ud_perm, coord.ud_slice_perm};

    const int corner_perm_ud_slice_perm_distance = corner_perm_ud_slice_perm_pruning.getDistance(corner_perm_ud_slice_perm_buff.begin());
    const int ud_perm_ud_slice_perm_distance = ud_perm_ud_slice_perm_pruning.getDistance(ud_perm_ud_slice_perm_buff.begin());

    return std::max(corner_perm_ud_slice_perm_distance, ud_perm_ud_slice_perm_distance);
}

const std::vector<int>& Phase2::getMoves(Phase2Coord coord, int last_move = -1)
{
    move_buffer_.clear();

    int last_face = -1;
    if(last_move != -1)
    {
        last_face = phase_2_moves[last_move] / 3;
    }

    for(int move = 0; move < phase_2_moves.size(); move++)
    {
        int face = phase_2_moves[move] / 3;

        if(face == last_face) {continue; }

        move_buffer_.push_back(move);
    }

    return move_buffer_;
}

Phase2Coord Phase2::move(Phase2Coord coord, int move) const
{
    Phase2Coord new_coord;

    new_coord.corner_perm = corner_perm_moves_.get(coord.corner_perm, move);
    new_coord.ud_perm = ud_perm_moves_.get(coord.ud_perm, move);
    new_coord.ud_slice_perm = ud_slice_perm_moves_.get(coord.ud_slice_perm, move);

    return new_coord;
}

constexpr int phase_2_max_depth = 18;

int Phase2::getMaxDepth() const
{
    return phase_2_max_depth;
}