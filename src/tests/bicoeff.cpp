#include <algorithms.h>
#include <iostream>

int main()
{
    std::cout << "input n and k \n";

    int n;
    int k;

    std::cin >> n;
    std::cin >> k;

    std::cout << biCoeff(n, k) << "\n";
}