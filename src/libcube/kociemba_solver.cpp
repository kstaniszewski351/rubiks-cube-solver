#include "kociemba_solver.h"

std::vector<Move> KociembaSolver::solve(CubieCube cube)
{

    auto phase_1_solution = phase_1_.solve(cube);

    for(Move m : phase_1_solution)
    {
        cube.move(m);
    }

    auto phase_2_solution = phase_2_.solve(cube);

    std::vector<Move> solution;
    solution.reserve(phase_1_solution.size() + phase_2_solution.size());
    solution.insert(solution.end(), phase_1_solution.begin(), phase_1_solution.end());
    solution.insert(solution.end(), phase_2_solution.begin(), phase_2_solution.end());

    return solution;
}