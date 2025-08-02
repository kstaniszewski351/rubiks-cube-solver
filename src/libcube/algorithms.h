#pragma once
#include <array>
#include <concepts>

// encodes values of elements in an array of lenght N
// as a coordinate ranging from 0 to base^(N-1)
// doesnt encode position of element at index 0
template <typename Iterator>
int baseNEncode(int base, Iterator begin, Iterator end) {
  int coord = 0;

  while (begin < end) {
    coord = (base * coord) + *begin;
    begin++;
  }

  return coord;
}

template <typename Iterator>
void baseNDecode(int coord, int base, Iterator begin, Iterator end) {
  end--;

  while (end >= begin) {
    const int digit = coord % base;
    *end = digit;
    coord /= base;

    end--;
  }
}

template <typename T>
  requires std::integral<T>
constexpr T factorial(T value) {
  T result = 1;

  for (T i = 2; i <= value; ++i) {
    result *= i;
  }

  return result;
}

// encodes permutation of N unique elements
// with values ranging from 0 to N - 1
// as a coordinate that ranges from 0 to N! - 1
template <typename Iterator>
int lehmerEncode(Iterator begin, Iterator end) {
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

// decodes coordinate ranging from 0 to N! - 1
// as a permutation of N unique elements with values
// ranging from 0 to N - 1
// works with integral types and enums
template <typename T, typename Iterator>
void lehmerDecode(int coord, int lenght, Iterator end) {
  Iterator it = end - 1;
  for (int max_digit = 1; max_digit <= lenght; max_digit++) {
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

    it--;
  }
}

// calculate binomial coefficient using
// multiplicative formula
template <typename T>
  requires std::integral<T>
constexpr T biCoeff(T n, T k) {
  T result = 1;
  for (T i = 1; i <= k; i++) {
    result = (result * (n + 1 - i)) / i;
  }

  return result;
}

// encodes combination of elements which meet toEncode predicate
// as a coordinate ranging from 0 to bicoeff(N, k) - 1, k = number of elements
// which meet toEncode
// doesnt preserve order
template <typename T, std::size_t N, typename F>
int combinationEncode(const std::array<T, N>& array, F&& predicate) {
  int result = 0;

  int occupied = -1;
  for (int i = 0; i < N; i++) {
    if (predicate(array[i])) {
      occupied++;
    } else if (occupied >= 0) {
      result += biCoeff(i, occupied);
    }
  }

  return result;
}

template <std::size_t N>
std::array<bool, N> combinationDecode(int coord, int n_true) {
  int k = n_true - 1;
  int n = N - 1;

  std::array<bool, N> result{};

  while (k >= 0) {
    int c = biCoeff(n, k);

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
constexpr T power(T base, T exp) {
  int result = 1;
  for (int i = 0; i < exp; ++i) {
    result *= base;
  }
  return result;
}
