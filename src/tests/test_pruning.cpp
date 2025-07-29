#include <coords/multi_coord.h>
#include <coords/ud_slice_pos_generator.h>
#include <coords/edge_flip_generator.h>
#include <coords/corner_twist_generator.h>
#include <coords/sym_coord.h>
#include <coords/coord_generator.h>
#include <coords/ud_slice_perm_generator.h>
#include <coords/corner_perm_generator.h>
#include <coords/ud_perm_generator.h>
#include <pruning.h>
#include <move_table.h>
#include <sym_conj.h>
#include <symmetries.h>
#include <iostream>
#include <vector>
#include <defs.h>

void printPruning(const Pruning& pruning)
{
    std::cout << "size: " << pruning.getSize() << "\n";
    std::cout << "distrib: \n";
    for(int i : pruning.getDistrib())
    {
        std::cout << i << "\n";
    }
}

const auto phase_2_moves = std::vector<Move>
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


int main()
{

    //phase 1 coords
    EdgeFlipGenerator flip_gen;
    UDSlicePosGenerator slice_pos_gen;
    CornerTwistGenerator twist_gen;

    //phase 2 coords
    UDPermGenerator ud_perm;
    CornerPermGenerator corner_perm;
    UDSlicePermGenerator slice_perm;
    
    auto flip_moves = MoveTable(&flip_gen);
    auto slice_pos_moves = MoveTable(&slice_pos_gen);
    auto twist_moves = MoveTable(&twist_gen);

    auto ud_perm_moves = MoveTable(&ud_perm, phase_2_moves);
    auto corner_perm_moves = MoveTable(&corner_perm, phase_2_moves);
    auto slice_perm_moves = MoveTable(&slice_perm, phase_2_moves);

    auto flip_slice_pruning = Pruning({&flip_moves, &slice_pos_moves}, {&flip_gen, &slice_pos_gen});
    auto twist_slice_pruning = Pruning({&twist_moves, &slice_pos_moves}, {&twist_gen, &slice_pos_gen});

    auto slice_perm_corner_perm_pruning = Pruning({&slice_perm_moves, &corner_perm_moves}, {&slice_perm, &corner_perm}, phase_2_moves.size());
    auto slice_perm_ud_perm_pruning = Pruning({&slice_perm_moves, &ud_perm_moves}, {&slice_perm, &ud_perm}, phase_2_moves.size());

    std::cout << "\n\nflip-slice pruning: \n";
    printPruning(flip_slice_pruning);

    std::cout << "\n\ntwist-slice pruning: \n";
    printPruning(twist_slice_pruning);

    std::cout << "\n\nslice perm - corner perm pruning: \n";
    printPruning(slice_perm_corner_perm_pruning);

    std::cout << "\n\nslice perm - ud perm pruning: \n";
    printPruning(slice_perm_ud_perm_pruning);



}