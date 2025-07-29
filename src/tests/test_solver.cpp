#include <phase1.h>
#include <iostream>
#include <chrono>

bool isPhase1Solved(const CubieCube& cube)
{
    for(bool flip : cube.edgeFlip)
    {
        if(flip != 0) {return false; }
    }

    for(int twist : cube.cornerOri)
    {
        if(twist != 0) {return false; }
    }

    return true;
}

int main()
{
    std::cout << "Starting set up\n";
    auto setup_begin_time = std::chrono::steady_clock::now();

    Phase1 phase1;

    auto setup_end_time = std::chrono::steady_clock::now();
    auto total_time = setup_begin_time - setup_end_time;
    std::chrono::duration<float, std::milli> setup_duration = setup_end_time - setup_begin_time;

    std::cout << "Set up took " << setup_duration.count() << "ms\n";

    CubieCube cube;

    std::vector<Move> scramble = {LP, F2, L, D, FP, U, RP, U, F2, UP, B, D2, U, B, RP, B, F2, R2, U, DP, LP, F, U, B, FP};

    for(Move m : scramble)
    {
        cube.move(m);
    }


    auto solve_begin_time = std::chrono::steady_clock::now();

    auto solution = phase1.solve(cube);

    auto solve_end_time = std::chrono::steady_clock::now();
    std::chrono::duration<float, std::milli> solve_duration = solve_end_time - solve_begin_time;

    for(Move m : solution)
    {
        cube.move(m);
    }

    std::cout << cube << "\n";
    std::cout << "Solving took " << solve_duration.count() << "ms\n";

    return 0;
}