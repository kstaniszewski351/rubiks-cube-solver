#include <iostream>
#include <array>
#include <algorithms.h>
#include <defs.h>

int main()
{
    std::array<Edge, EdgeCount> perm;

    std::cout << "input 12 ints from 0 to 11\n";
    for(Edge& i : perm)
    {
        int temp;
        std::cin >> temp;
        i = static_cast<Edge>(temp);
    }

    int c = CombinationEncode(perm, [](int i) {return i >= UD_SLICE;});
    auto decode = CombinationDecode<12>(c, 4);
    
    for(bool i : decode)
    {
        std::cout << i << " ";
    }

    std::cout << "\n";
}