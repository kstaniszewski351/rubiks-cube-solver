#include "util.h"

int biCoeff(int n, int k)
{
    if (k > n)
        return 0;
  
    if (k == 0 || k == n)
        return 1;

    return biCoeff(n - 1, k - 1)
           + biCoeff(n - 1, k);
}