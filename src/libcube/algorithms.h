#pragma once
#include <array>

template <typename Iterator>
int BaseNEncode(int base, Iterator begin, Iterator end) {
  int coord = 0;

  while (begin < end) {
    coord = (base * coord) + *begin;
    begin++;
  }

  return coord;
}

template <typename Iterator>
void BaseNDecode(int coord, int base, Iterator begin, Iterator end) {
  end--;

  while (end >= begin) {
    const int digit = coord % base;
    *end = digit;
    coord /= base;

    end--;
  }
}

template <typename T>
constexpr T Factorial(T value) {
  T result = 1;

  for (T i = 2; i <= value; ++i) {
    result *= i;
  }

  return result;
}

template <typename Iterator>
int LehmerEncode(Iterator begin, Iterator end) {
  int coord = 0;
  Iterator i = end - 1;
  int factorial = 1;
  int iter = 1;

  while (i >= begin) {
    int digit = 0;

    Iterator j = i + 1;

    while (j < end) {
      if (*j < *i) {
        ++digit;
      }
      ++j;
    }

    // encode factoradic
    coord = factorial * digit + coord;

    factorial = factorial * (iter);
    ++iter;
    --i;
  }

  return coord;
}

template <typename T, typename Iterator>
void LehmerDecode(int coord, Iterator begin, Iterator end) {
  Iterator it = end - 1;
  int max_digit = 1;

  while (it >= begin) {
    // decode factoradic
    int digit = coord % max_digit;
    coord /= max_digit;

    *it = static_cast<T>(digit);
    Iterator j = it + 1;

    while (j < end) {
      if (*j >= *it) {
        *j = static_cast<T>(static_cast<int>(*j + 1));
      }
      j++;
    }

    max_digit++;
    it--;
  }
}

// calculate binomial coefficient using
// multiplicative formula
template <typename T>
constexpr T BiCoeff(T n, T k) {
  T result = 1;
  for (T i = 1; i <= k; i++) {
    result = (result * (n + 1 - i)) / i;
  }

  return result;
}

template <typename F, typename Iterator>
int CombinationEncode(F&& predicate, Iterator begin, Iterator end) {
  int coord = 0;
  int n_occupied = -1;
  int index = 0;
  Iterator it = begin;

  while (it < end) {
    if (predicate(*it)) {
      n_occupied++;
    } else if (n_occupied >= 0) {
      coord += BiCoeff(index, n_occupied);
    }

    it++;
    index++;
  }

  return coord;
}

template <std::size_t N>
std::array<bool, N> CombinationDecode(int coord, int n_true) {
  int k = n_true - 1;
  int n = N - 1;

  std::array<bool, N> result{};

  while (k >= 0) {
    int c = BiCoeff(n, k);

    if (coord < c) {
      result[n] = true;
      k--;
    } else {
      coord = coord - c;
    }
    n--;
  }

  return result;
}

template <typename T>
constexpr T Power(T base, T exp) {
  int result = 1;
  for (int i = 0; i < exp; ++i) {
    result *= base;
  }
  return result;
}
