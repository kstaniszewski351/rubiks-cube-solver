#include <phase1.h>
#include <phase2.h>
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

constexpr std::array<std::string_view, 18> move_names
{
    "U",
    "U2",
    "U'",
    "D",
    "D2",
    "D'",
    "R",
    "R2",
    "R'",
    "L",
    "L2",
    "L'",
    "F",
    "F2",
    "F'",
    "B",
    "B2",
    "B'"
};

int main()
{
    std::cout << "Starting set up\n";
    auto setup_begin_time = std::chrono::steady_clock::now();

    Phase1 phase1;
    Phase2 phase2;

    auto setup_end_time = std::chrono::steady_clock::now();
    auto total_time = setup_begin_time - setup_end_time;
    std::chrono::duration<float, std::milli> setup_duration = setup_end_time - setup_begin_time;

    std::cout << "Set up took " << setup_duration.count() << "ms\n";

    CubieCube cube;

    std::cout << "Input scramble: ";
    std::string scramble_string;
    std::getline(std::cin, scramble_string);

    std::vector<Move> scramble;
    auto scramble_stream = std::istringstream(scramble_string);
    std::string move_string;
    while(scramble_stream >> move_string)
    {
        auto move_iter = std::find(move_names.begin(), move_names.end(), move_string);
        if(move_iter == move_names.end())
        {
            std::cout << "Invalid move: " << move_iter << "\n";
            return 0;
        }
        const int move_index = std::distance(move_names.begin(), move_iter);

        scramble.push_back(static_cast<Move>(move_index));
    }  

    for(Move m : scramble)
    {
        cube.move(m);
    }
    std::cout << "Scrambled cube: \n";
    std::cout << cube;

    auto phase1_begin_time = std::chrono::steady_clock::now();

    std::vector<Move> phase_1_solution = phase1.solve(cube);

    auto phase1_end_time = std::chrono::steady_clock::now();
    std::chrono::duration<float, std::milli> phase1_duration = phase1_end_time - phase1_begin_time;

    for(Move m : phase_1_solution)
    {
        cube.move(m);
    }

    auto phase2_begin_time = std::chrono::steady_clock::now();

    std::vector<Move> phase_2_solution = phase2.solve(cube);

    auto phase2_end_time = std::chrono::steady_clock::now();

    std::chrono::duration<float, std::milli> phase2_duration = phase2_end_time - phase2_begin_time;
    std::chrono::duration<float, std::milli> solve_duration = phase2_end_time - phase1_begin_time;

    for(Move m : phase_2_solution)
    {
        cube.move(m);
    }
    std::cout << "Solved cube: \n";
    std::cout << cube << "\n";
    std::cout << "Solution: ";
    for(Move m : phase_1_solution)
    {
        std::cout << move_names[m] << " ";
    }
    for(Move m : phase_2_solution)
    {
        std::cout << move_names[m] << " ";
    }
    std::cout << "Lenght: " << (phase_1_solution.size() + phase_2_solution.size()) << "\n";
    std::cout <<"\n";
    std::vector test = phase2.getMoves(Phase2Coord(), U);
    std::cout << "Phase 1 took " << phase1_duration.count() << "ms\n";
    std::cout << "Phase 2 took " << phase2_duration.count() << "ms\n";
    std::cout << "Total solve time " << solve_duration.count() << "ms\n";

    return 0;
}