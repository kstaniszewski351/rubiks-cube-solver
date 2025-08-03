#include <phase1.h>
#include <iostream>
#include <chrono>
#include <phase2.h>
#include <move.h>
#include <random>
#include <kociemba_solver.h>

bool isPhase1Solved(const CubieCube& cube)
{
    for(bool flip : cube.edge_flip)
    {
        if(flip != 0) {return false; }
    }

    for(int twist : cube.corner_ori)
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

    KociembaSolver solver;

    auto setup_end_time = std::chrono::steady_clock::now();
    auto total_time = setup_begin_time - setup_end_time;
    std::chrono::duration<float, std::milli> setup_duration = setup_end_time - setup_begin_time;

    std::cout << "Set up took " << setup_duration.count() << "ms\n";


    std::cout << "Generate random scramble y/n: \n";
    std::string answer;
    std::cin >> answer;

    std::vector<Move> scramble;

    if(answer == "y")
    {
        scramble = RandomScramble(30, std::random_device()());
        std::cout << "Scramble: ";
        for(Move move : scramble)
        {
            std::cout << move_names[move] << " ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "Input scramble: \n";
        std::string scramble_string;
        
        std::cin.ignore();
        std::getline(std::cin, scramble_string);

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
    }



    CubieCube cube;
    for(Move m : scramble)
    {
        cube.Move(m);
    }
    std::cout << "Scrambled cube: \n";
    std::cout << cube;

    auto solve_begin_time = std::chrono::steady_clock::now();

    auto solution = solver.Solve(cube);

    auto solve_end_time = std::chrono::steady_clock::now();
    std::chrono::duration<float, std::milli> solve_duration = solve_end_time - solve_begin_time;


    for(Move m : solution)
    {
        cube.Move(m);
    }

    std::cout << cube << "\n";
    std::cout << "Solution: ";
    for(Move m : solution)
    {
        std::cout << move_names[m] << " ";
    }
    std::cout << "Lenght: " << solution.size() << "\n";
    std::cout << "Solving took " << solve_duration.count() << "ms\n";

    return 0;
}