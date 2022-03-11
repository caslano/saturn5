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
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
*/