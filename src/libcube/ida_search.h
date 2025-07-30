#pragma once
#include "searchable.h"

template<typename Coord>
class IDAsearch
{
public:
    IDAsearch(Searchable<Coord>* searchable) : 
        searchable_(searchable)
    {
        coord_stack_.reserve(searchable_->getMaxDepth() + 1);
        move_stack_.reserve(searchable_->getMaxDepth());
    };
    std::vector<Move> search(Coord coord)
    {
        coord_stack_.clear();
        move_stack_.clear();
        int bound = searchable_->estimateDistanceLeft(coord);
        coord_stack_.push_back(coord);
        
        while(true)
        {
            bound = recursiveSearch(0, bound);
            if(bound == 0) {break;}
        }
        auto solution = move_stack_;
        solution.shrink_to_fit();
        return solution;
    };

private:
    int recursiveSearch(int depth, int bound)
    {
        const Coord coord = coord_stack_.back();
        const int distance_left = searchable_->estimateDistanceLeft(coord);
        const int total_distance = depth + distance_left;

        if(total_distance > bound) { return total_distance; }
        if(distance_left == 0) { return 0; }
        

        int min_distance = -1;
        Move last_move = Invalid;

        if(!move_stack_.empty()) {last_move = move_stack_.back(); }

        const std::vector<Move>& moves = searchable_->getMoves(coord, last_move);

        for(Move move : moves)
        {
            Coord new_coord = searchable_->move(coord, move);
            coord_stack_.push_back(new_coord);
            move_stack_.push_back(move);

            const int distance_left = recursiveSearch(depth + 1, bound);

            if(distance_left == 0)
            {
                return 0;
            }
            if(distance_left < min_distance || min_distance == -1)
            {
                min_distance = distance_left;
            }

            coord_stack_.pop_back();
            move_stack_.pop_back();
        }
        return min_distance;
    };
    Searchable<Coord>* searchable_;
    std::vector<Move> move_stack_;
    std::vector<Coord> coord_stack_;
};