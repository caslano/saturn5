/* boost random/detail/signed_unsigned_tools.hpp header file
 *
 * Copyright Jens Maurer 2006
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 */

#ifndef BOOST_RANDOM_DETAIL_SIGNED_UNSIGNED_TOOLS
#define BOOST_RANDOM_DETAIL_SIGNED_UNSIGNED_TOOLS

#include <boost/limits.hpp>
#include <boost/config.hpp>
#include <boost/random/traits.hpp>

namespace boost {
namespace random {
namespace detail {


/*
 * Compute x - y, we know that x >= y, return an unsigned value.
 */

template<class T, bool sgn = std::numeric_limits<T>::is_signed && std::numeric_limits<T>::is_bounded>
struct subtract { };

template<class T>
struct subtract<T, /* signed */ false>
{
  typedef T result_type;
  result_type operator()(T x, T y) { return x - y; }
};

template<class T>
struct subtract<T, /* signed */ true>
{
  typedef typename boost::random::traits::make_unsigned_or_unbounded<T>::type result_type;
  result_type operator()(T x, T y)
  {
    if (y >= 0)   // because x >= y, it follows that x >= 0, too
      return result_type(x) - result_type(y);
    if (x >= 0)   // y < 0
      // avoid the nasty two's complement case for y == min()
      return result_type(x) + result_type(-(y+1)) + 1;
    // both x and y are negative: no signed overflow
    return result_type(x - y);
  }
};

/*
 * Compute x + y, x is unsigned, result fits in type of "y".
 */

template<class T1, class T2, bool sgn = (std::numeric_limits<T2>::is_signed && (std::numeric_limits<T1>::digits >= std::numeric_limits<T2>::digits))>
struct add { };

template<class T1, class T2>
struct add<T1, T2, /* signed or else T2 has more digits than T1 so the cast always works - needed when T2 is a multiprecision type and T1 is a native integer */ false>
{
  typedef T2 result_type;
  result_type operator()(T1 x, T2 y) { return T2(x) + y; }
};

template<class T1, class T2>
struct add<T1, T2, /* signed */ true>
{
  typedef T2 result_type;
  result_type operator()(T1 x, T2 y)
  {
    if (y >= 0)
      return T2(x) + y;
    // y < 0
    if (x > T1(-(y+1)))  // result >= 0 after subtraction
      // avoid the nasty two's complement edge case for y == min()
      return T2(x - T1(-(y+1)) - 1);
    // abs(x) < abs(y), thus T2 able to represent x
    return T2(x) + y;
  }
};

} // namespace detail
} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_DETAIL_SIGNED_UNSIGNED_TOOLS


/* signed_unsigned_tools.hpp
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
*/