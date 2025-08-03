#include "kociemba_solver.h"

std::vector<Move> KociembaSolver::Solve(CubieCube cube) {
  auto phase_1_solution = phase_1_.Solve(cube);

  for (Move m : phase_1_solution) {
    cube.Move(m);
  }

  auto phase_2_solution = phase_2_.Solve(cube);

  std::vector<Move> solution;
  solution.reserve(phase_1_solution.size() + phase_2_solution.size());
  solution.insert(solution.end(), phase_1_solution.begin(),
                  phase_1_solution.end());
  solution.insert(solution.end(), phase_2_solution.begin(),
                  phase_2_solution.end());

  return solution;
}