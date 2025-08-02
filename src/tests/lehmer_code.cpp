#include <algorithms.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <span>
#include <array>
#include <defs.h>

int main()
{
    std::cout << "input permutation of 6 digits\n";

    std::array<int, 6> perm;

    std::string input;
    for(int i = 0; i < 6; i++)
    {
        std::cin >> input;

        perm[i] = std::stoi(input);
    }

    int code = lehmerEncode(perm.begin(), perm.end());

    std::cout << "code: " << code << "\n";

    lehmerDecode<int>(code, 6, perm.end());

    for(int i : perm)
    {
        std::cout << i << " ";
    }

    std::cout << "\n";
}