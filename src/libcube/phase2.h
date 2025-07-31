#pragma once
#include "defs.h"
#include <vector>
#include "cubie_cube.h"
#include "coords/corner_perm_generator.h"
#include "coords/ud_perm_generator.h"
#include "coords/ud_slice_perm_generator.h"
#include "move_table.h"
#include "pruning.h"
#include <stack>
#include "searchable.h"
#include "ida_search.h"

struct Phase2Coord
{
    int corner_perm;
    int ud_perm;
    int ud_slice_perm;
};

class Phase2 : public Searchable<Phase2Coord>
{
public:
    Phase2();
    std::vector<Move> solve(const CubieCube& cube);
    int estimateDistanceLeft(Phase2Coord coord) const override;
    const std::vector<int>& getMoves(Phase2Coord coord, int last_move) override;
    Phase2Coord move(Phase2Coord coord, int move) const override;
    int getMaxDepth() const override;
private:
    const CornerPermGenerator corner_perm_gen_;
    const UDPermGenerator ud_perm_gen_;
    const UDSlicePermGenerator ud_slice_perm_gen_;
    const MoveTable corner_perm_moves_;
    const MoveTable ud_perm_moves_;
    const MoveTable ud_slice_perm_moves_;
    const Pruning corner_perm_ud_slice_perm_pruning;
    const Pruning ud_perm_ud_slice_perm_pruning;
    std::vector<int> move_buffer_;
    IDAsearch<Phase2Coord> search_;
};