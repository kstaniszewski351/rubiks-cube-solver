#include "phase1.h"
#include <algorithm>
#include <limits>
#include <iostream>


Phase1::Phase1() :
    flip_moves_(&flip_gen_),
    slice_pos_moves_(&slice_pos_gen_),
    twist_moves_(&twist_gen_),
    flip_slice_pos_pruning_({&flip_moves_, &slice_pos_moves_}, {&flip_gen_, &slice_pos_gen_}),
    twist_slice_pos_pruning_({&twist_moves_, &slice_pos_moves_}, {&twist_gen_, &slice_pos_gen_}),
    search_(this)
{
    move_buffer_.reserve(18);
}


std::vector<Move> Phase1::solve(const CubieCube& cube)
{
    Phase1Coord coord;
    coord.flip = flip_gen_.getCoord(cube);
    coord.slice_pos = slice_pos_gen_.getCoord(cube);
    coord.twist = twist_gen_.getCoord(cube);

    std::vector<int> solution_move_indexes = search_.search(coord);
    std::vector<Move> solution;

    for(int i : solution_move_indexes)
    {
        solution.push_back(static_cast<Move>(i));
    }

    return solution;
}

constexpr int phase1_max_depth = 12;

int Phase1::getMaxDepth() const
{
    return phase1_max_depth;
}

const std::vector<int>& Phase1::getMoves(Phase1Coord coord, int last_move = -1)
{
    move_buffer_.clear();

    int last_face = -1;
    if(last_move != -1)
    {
        last_face = last_move / 3;
    }
    for(int move = 0; move < MOVE_COUNT; move++)
    {
        int face = move / 3;

        if(face == last_face) {continue;}

        move_buffer_.push_back(move);
    }

    return move_buffer_;
}

int Phase1::estimateDistanceLeft(Phase1Coord coord) const
{
    const std::array<int, 2> flip_slice_pos_buff {coord.flip, coord.slice_pos};
    const std::array<int, 2> twist_slice_pos_buff {coord.twist, coord.slice_pos};

    const int flip_slice_pos_distance = flip_slice_pos_pruning_.getDistance(flip_slice_pos_buff.begin());
    const int twist_slice_pos_distance = twist_slice_pos_pruning_.getDistance(twist_slice_pos_buff.begin());
    
    return std::max(flip_slice_pos_distance, twist_slice_pos_distance);
}

Phase1Coord Phase1::move(Phase1Coord coord, int move) const
{
    Phase1Coord new_coord;

    new_coord.flip = flip_moves_.get(coord.flip, move);
    new_coord.slice_pos = slice_pos_moves_.get(coord.slice_pos, move);
    new_coord.twist = twist_moves_.get(coord.twist, move);

    return new_coord;
}
