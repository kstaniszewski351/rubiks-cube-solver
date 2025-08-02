#include "phase1.h"
#include <algorithm>
#include <limits>
#include <iostream>
#include "move.h"



Phase1::Phase1() :
    flip_moves_(&flip_gen_),
    slice_pos_moves_(&slice_pos_gen_),
    twist_moves_(&twist_gen_),
    flip_slice_pos_pruning_({&flip_moves_, &slice_pos_moves_}, {&flip_gen_, &slice_pos_gen_}),
    twist_slice_pos_pruning_({&twist_moves_, &slice_pos_moves_}, {&twist_gen_, &slice_pos_gen_})
{

}

bool Phase1Coord::isSolved() const
{
    return flip == 0 && slice_pos == 0 && twist == 0;
}

constexpr int phase1_max_depth = 12;

std::vector<Move> Phase1::solve(const CubieCube& cube)
{
    Phase1Coord coord;
    coord.flip = flip_gen_.getCoord(cube);
    coord.slice_pos = slice_pos_gen_.getCoord(cube);
    coord.twist = twist_gen_.getCoord(cube);

    std::vector<Phase1Coord> coord_stack;
    std::vector<Move> move_stack;

    coord_stack.reserve(phase1_max_depth);
    move_stack.reserve(phase1_max_depth - 1);

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


int Phase1::IDASearch(std::vector<Phase1Coord>& coord_stack, std::vector<Move>& move_stack, int depth, int bound)
{
    const Phase1Coord coord = coord_stack.back();
    const int distance_left = estimateDistanceLeft(coord);
    const int total_distance = depth + distance_left;

    if(total_distance > bound) { return total_distance; }
    if(distance_left == 0) { return 0; }
    
    int min_distance = -1;
    
    for(int move = 0; move < MoveCount; move++)
    {
        if(isMoveRedundant(static_cast<Move>(move), move_stack.begin(), move_stack.end())) {continue;}

        Phase1Coord new_coord = moveCoord(coord, static_cast<Move>(move));
        coord_stack.push_back(new_coord);
        move_stack.push_back(static_cast<Move>(move));

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

int Phase1::estimateDistanceLeft(Phase1Coord coord)
{
    const std::array<int, 2> flip_slice_pos_buff {coord.flip, coord.slice_pos};
    const std::array<int, 2> twist_slice_pos_buff {coord.twist, coord.slice_pos};

    const int flip_slice_pos_distance = flip_slice_pos_pruning_.getDistance(flip_slice_pos_buff.begin());
    const int twist_slice_pos_distance = twist_slice_pos_pruning_.getDistance(twist_slice_pos_buff.begin());
    
    return std::max(flip_slice_pos_distance, twist_slice_pos_distance);
}

Phase1Coord Phase1::moveCoord(Phase1Coord coord, Move move)
{
    Phase1Coord new_coord;

    new_coord.flip = flip_moves_.get(coord.flip, move);
    new_coord.slice_pos = slice_pos_moves_.get(coord.slice_pos, move);
    new_coord.twist = twist_moves_.get(coord.twist, move);

    return new_coord;
}
