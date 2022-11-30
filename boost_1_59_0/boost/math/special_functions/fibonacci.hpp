// Copyright 2020, Madhur Chauhan

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_FIBO_HPP
#define BOOST_MATH_SPECIAL_FIBO_HPP

#include <boost/math/constants/constants.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <cmath>
#include <limits>

#ifdef _MSC_VER
#pragma once
#endif

namespace boost {
namespace math {

namespace detail {
   constexpr double fib_bits_phi = 0.69424191363061730173879026;
   constexpr double fib_bits_deno = 1.1609640474436811739351597;
} // namespace detail

template <typename T>
inline BOOST_CXX14_CONSTEXPR T unchecked_fibonacci(unsigned long long n) noexcept(std::is_fundamental<T>::value) {
    // This function is called by the rest and computes the actual nth fibonacci number
    // First few fibonacci numbers: 0 (0th), 1 (1st), 1 (2nd), 2 (3rd), ...
    if (n <= 2) return n == 0 ? 0 : 1;
    /* 
     * This is based on the following identities by Dijkstra:
     *   F(2*n)   = F(n)^2 + F(n+1)^2
     *   F(2*n+1) = (2 * F(n) + F(n+1)) * F(n+1)
     * The implementation is iterative and is unrolled version of trivial recursive implementation.
     */
    unsigned long long mask = 1;
    for (int ct = 1; ct != std::numeric_limits<unsigned long long>::digits && (mask << 1) <= n; ++ct, mask <<= 1)
        ;
    T a{1}, b{1};
    for (mask >>= 1; mask; mask >>= 1) {
        T t1 = a * a;
        a = 2 * a * b - t1, b = b * b + t1;
        if (mask & n) 
            t1 = b, b = b + a, a = t1; // equivalent to: swap(a,b), b += a;
    }
    return a;
}

template <typename T, class Policy>
T inline BOOST_CXX14_CONSTEXPR fibonacci(unsigned long long n, const Policy &pol) {
    // check for overflow using approximation to binet's formula: F_n ~ phi^n / sqrt(5)
    if (n > 20 && n * detail::fib_bits_phi - detail::fib_bits_deno > std::numeric_limits<T>::digits)
        return policies::raise_overflow_error<T>("boost::math::fibonacci<%1%>(unsigned long long)", "Possible overflow detected.", pol);
    return unchecked_fibonacci<T>(n);
}

template <typename T>
T inline BOOST_CXX14_CONSTEXPR fibonacci(unsigned long long n) {
    return fibonacci<T>(n, policies::policy<>());
}

// generator for next fibonacci number (see examples/reciprocal_fibonacci_constant.hpp)
template <typename T>
class fibonacci_generator {
  public:
    // return next fibonacci number
    T operator()() noexcept(std::is_fundamental<T>::value) {
        T ret = a;
        a = b, b = b + ret; // could've simply: swap(a, b), b += a;
        return ret;
    }

    // after set(nth), subsequent calls to the generator returns consecutive
    // fibonacci numbers starting with the nth fibonacci number
    void set(unsigned long long nth) noexcept(std::is_fundamental<T>::value) {
        n = nth;
        a = unchecked_fibonacci<T>(n);
        b = unchecked_fibonacci<T>(n + 1);
    }

  private:
    unsigned long long n = 0;
    T a = 0, b = 1;
};

} // namespace math
} // namespace boost

#endif

/* fibonacci.hpp
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
*/