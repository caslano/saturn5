//  (C) Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_SERIES_INCLUDED
#define BOOST_MATH_TOOLS_SERIES_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config/no_tr1/cmath.hpp>
#include <boost/cstdint.hpp>
#include <boost/limits.hpp>
#include <boost/math/tools/config.hpp>

namespace boost{ namespace math{ namespace tools{

//
// Simple series summation come first:
//
template <class Functor, class U, class V>
inline typename Functor::result_type sum_series(Functor& func, const U& factor, boost::uintmax_t& max_terms, const V& init_value) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   boost::uintmax_t counter = max_terms;

   result_type result = init_value;
   result_type next_term;
   do{
      next_term = func();
      result += next_term;
   }
   while((abs(factor * result) < abs(next_term)) && --counter);

   // set max_terms to the actual number of terms of the series evaluated:
   max_terms = max_terms - counter;

   return result;
}

template <class Functor, class U>
inline typename Functor::result_type sum_series(Functor& func, const U& factor, boost::uintmax_t& max_terms) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   typename Functor::result_type init_value = 0;
   return sum_series(func, factor, max_terms, init_value);
}

template <class Functor, class U>
inline typename Functor::result_type sum_series(Functor& func, int bits, boost::uintmax_t& max_terms, const U& init_value) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   typedef typename Functor::result_type result_type;
   result_type factor = ldexp(result_type(1), 1 - bits);
   return sum_series(func, factor, max_terms, init_value);
}

template <class Functor>
inline typename Functor::result_type sum_series(Functor& func, int bits) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   typedef typename Functor::result_type result_type;
   boost::uintmax_t iters = (std::numeric_limits<boost::uintmax_t>::max)();
   result_type init_val = 0;
   return sum_series(func, bits, iters, init_val);
}

template <class Functor>
inline typename Functor::result_type sum_series(Functor& func, int bits, boost::uintmax_t& max_terms) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   typedef typename Functor::result_type result_type;
   result_type init_val = 0;
   return sum_series(func, bits, max_terms, init_val);
}

template <class Functor, class U>
inline typename Functor::result_type sum_series(Functor& func, int bits, const U& init_value) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   boost::uintmax_t iters = (std::numeric_limits<boost::uintmax_t>::max)();
   return sum_series(func, bits, iters, init_value);
}
//
// Checked summation:
//
template <class Functor, class U, class V>
inline typename Functor::result_type checked_sum_series(Functor& func, const U& factor, boost::uintmax_t& max_terms, const V& init_value, V& norm) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   boost::uintmax_t counter = max_terms;

   result_type result = init_value;
   result_type next_term;
   do {
      next_term = func();
      result += next_term;
      norm += fabs(next_term);
   } while ((abs(factor * result) < abs(next_term)) && --counter);

   // set max_terms to the actual number of terms of the series evaluated:
   max_terms = max_terms - counter;

   return result;
}


//
// Algorithm kahan_sum_series invokes Functor func until the N'th
// term is too small to have any effect on the total, the terms
// are added using the Kahan summation method.
//
// CAUTION: Optimizing compilers combined with extended-precision
// machine registers conspire to render this algorithm partly broken:
// double rounding of intermediate terms (first to a long double machine
// register, and then to a double result) cause the rounding error computed
// by the algorithm to be off by up to 1ulp.  However this occurs rarely, and
// in any case the result is still much better than a naive summation.
//
template <class Functor>
inline typename Functor::result_type kahan_sum_series(Functor& func, int bits) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   result_type factor = pow(result_type(2), bits);
   result_type result = func();
   result_type next_term, y, t;
   result_type carry = 0;
   do{
      next_term = func();
      y = next_term - carry;
      t = result + y;
      carry = t - result;
      carry -= y;
      result = t;
   }
   while(fabs(result) < fabs(factor * next_term));
   return result;
}

template <class Functor>
inline typename Functor::result_type kahan_sum_series(Functor& func, int bits, boost::uintmax_t& max_terms) BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   boost::uintmax_t counter = max_terms;

   result_type factor = ldexp(result_type(1), bits);
   result_type result = func();
   result_type next_term, y, t;
   result_type carry = 0;
   do{
      next_term = func();
      y = next_term - carry;
      t = result + y;
      carry = t - result;
      carry -= y;
      result = t;
   }
   while((fabs(result) < fabs(factor * next_term)) && --counter);

   // set max_terms to the actual number of terms of the series evaluated:
   max_terms = max_terms - counter;

   return result;
}

} // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_SERIES_INCLUDED


/* series.hpp
NUhjzart4rP4IhogzZ/xTep5wmsSR9FfXzMW7U4A+rZPVQm7jDW73yVEiVl6Rqfrz8ddm5HMSxvBz7355VH+A1BLAwQKAAAACAAtZ0pS8kZbvHcBAACMAgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwMzhVVAUAAbZIJGCVUtFKwzAUfQ/0Hy4TEQYzDh+UEasyK+7JutaJvsX21hXbpCSZOr/em7Rz+GgoNLk55+TckwiH1hXSYsxErSpNv3fcfmpT2pjd5ilL0mzFrtM0YUu0mxaZ4HuA4D3nADI0H2gmti4JYbBrtrRr62/SnZ4Rrp8KPmwRY97UqNzAKMLCU4JOzCrXedawAqFki8EQpNfZCjZdo2UJJliCyugWUJWgK6jqBgnPewKIQretVGVQnHF+eHef5Yt0dkhS6f0y59OT03OY5NDoN96r9pU5TMjAL1t4XfCiF6O/0FHM3Lq2QJ9bI4z9KMxVNx4GVaWDTzwyCG9aKTmYZ4xC/LqkQ7y0z2YXAoWzQlNXWyilkyArhyZo+7uCtbTwiqhgZNfajZj4CFgS6Ix2utBNzB6zZAlSabVt9cZGjDLLgAK4wi/Zdg0eU19UfbqJwv1GLH9OE1hELFu8JOC7isKdD9OHx0UekcH9
*/