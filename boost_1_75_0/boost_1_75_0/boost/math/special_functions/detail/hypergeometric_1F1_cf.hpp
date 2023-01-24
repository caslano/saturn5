
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_1F1_CF_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F1_CF_HPP

#include <boost/math/tools/fraction.hpp>

//
// Evaluation of 1F1 by continued fraction
// see http://functions.wolfram.com/HypergeometricFunctions/Hypergeometric1F1/10/0002/
//
// This is not terribly useful, as like the series we're adding a something to 1,
// so only really useful when we know that the result will be > 1.
//


  namespace boost { namespace math { namespace detail {

     template <class T>
     struct hypergeometric_1F1_cf_func
     {
        typedef std::pair<T, T>  result_type;
        hypergeometric_1F1_cf_func(T a_, T b_, T z_) : a(a_), b(b_), z(z_), k(0) {}
        std::pair<T, T> operator()()
        {
           ++k;
           return std::make_pair(-(((a + k) * z) / ((k + 1) * (b + k))), 1 + ((a + k) * z) / ((k + 1) * (b + k)));
        }
        T a, b, z;
        unsigned k;
     };

     template <class T, class Policy>
     T hypergeometric_1F1_cf(const T& a, const T& b, const T& z, const Policy& pol, const char* function)
     {
        hypergeometric_1F1_cf_func<T> func(a, b, z);
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::continued_fraction_a(func, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>(function, max_iter, pol);
        return 1 + a * z / (b * (1 + result));
     }

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_1F1_BESSEL_HPP

/* hypergeometric_1F1_cf.hpp
/GSSMODdvvvCWXhfoOghNcMaBW9NBpzBXzQoe6QEFCN5ea3bJJ4SbM++XYULJp5UNvpuAV+kCx1iT3s2vrNVQb0F4ySm+XYOoYasHx9zUSGoxImUgH3UzoOWlSrM8Um1kuoUNY6U44Xf+dy3tD3pft5sDuLUy13uMoAIXNttAW2tycuhffQ5tKo5LE/5SdhzIUrmGgyftrm27PUYJK5dokQ9oT7pP99eSpvxHvfYMtQ1SexIu17pCbFeK/JNsZo7ZxNZ79f5YWzADLYOt0eNaiWvZB+wmnbavMKst+3v0U9HKzK+owUuquf3jVNPLQyABiaSfX/SaRG7UsYfM+M3uSit0e2vPfo+PMibiCTcSDdMrOQ8OZjEtJo8s0YDUWEipKd9RCYCTDC4KGs/d+1VwK9RWUuPSAKv8Ai3Fv2fVdOZ1q/1olclynAGx3Az6llyils+0MpzRaaz6r3Vy/VKRN1/LLpsi8+09oGYId3aMBbdxFKrh7YjBS8ojiW0I7YLpU06dNYY/T2Hk1jpTwpzAiWybvfGLq93o1q8XZ6tuCjJH5xeXKvSrpmegxCYtRuWVb85dipuTLkNt87bE3gnbh0DOi2fTr59sy5SYgac43i1U3bBwfsjpkjuHwil9MsTmPAMOFtiO5FqYjztaSjKdgZ8b9EiKvx9Mcp2ovOdI2K2dOPBKvpMbUikw6PgvNB2qyktvW0kqLHJte+h
*/