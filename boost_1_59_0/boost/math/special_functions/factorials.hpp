//  Copyright John Maddock 2006, 2010.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SP_FACTORIALS_HPP
#define BOOST_MATH_SP_FACTORIALS_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/detail/unchecked_factorial.hpp>
#include <array>
#ifdef _MSC_VER
#pragma warning(push) // Temporary until lexical cast fixed.
#pragma warning(disable: 4127 4701)
#endif
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include <type_traits>
#include <cmath>

namespace boost { namespace math
{

template <class T, class Policy>
inline T factorial(unsigned i, const Policy& pol)
{
   static_assert(!std::is_integral<T>::value, "Type T must not be an integral type");
   // factorial<unsigned int>(n) is not implemented
   // because it would overflow integral type T for too small n
   // to be useful. Use instead a floating-point type,
   // and convert to an unsigned type if essential, for example:
   // unsigned int nfac = static_cast<unsigned int>(factorial<double>(n));
   // See factorial documentation for more detail.

   BOOST_MATH_STD_USING // Aid ADL for floor.

   if(i <= max_factorial<T>::value)
      return unchecked_factorial<T>(i);
   T result = boost::math::tgamma(static_cast<T>(i+1), pol);
   if(result > tools::max_value<T>())
      return result; // Overflowed value! (But tgamma will have signalled the error already).
   return floor(result + 0.5f);
}

template <class T>
inline T factorial(unsigned i)
{
   return factorial<T>(i, policies::policy<>());
}
/*
// Can't have these in a policy enabled world?
template<>
inline float factorial<float>(unsigned i)
{
   if(i <= max_factorial<float>::value)
      return unchecked_factorial<float>(i);
   return tools::overflow_error<float>(BOOST_CURRENT_FUNCTION);
}

template<>
inline double factorial<double>(unsigned i)
{
   if(i <= max_factorial<double>::value)
      return unchecked_factorial<double>(i);
   return tools::overflow_error<double>(BOOST_CURRENT_FUNCTION);
}
*/
template <class T, class Policy>
T double_factorial(unsigned i, const Policy& pol)
{
   static_assert(!std::is_integral<T>::value, "Type T must not be an integral type");
   BOOST_MATH_STD_USING  // ADL lookup of std names
   if(i & 1)
   {
      // odd i:
      if(i < max_factorial<T>::value)
      {
         unsigned n = (i - 1) / 2;
         return ceil(unchecked_factorial<T>(i) / (ldexp(T(1), (int)n) * unchecked_factorial<T>(n)) - 0.5f);
      }
      //
      // Fallthrough: i is too large to use table lookup, try the
      // gamma function instead.
      //
      T result = boost::math::tgamma(static_cast<T>(i) / 2 + 1, pol) / sqrt(constants::pi<T>());
      if(ldexp(tools::max_value<T>(), -static_cast<int>(i+1) / 2) > result)
         return ceil(result * ldexp(T(1), static_cast<int>(i+1) / 2) - 0.5f);
   }
   else
   {
      // even i:
      unsigned n = i / 2;
      T result = factorial<T>(n, pol);
      if(ldexp(tools::max_value<T>(), -(int)n) > result)
         return result * ldexp(T(1), (int)n);
   }
   //
   // If we fall through to here then the result is infinite:
   //
   return policies::raise_overflow_error<T>("boost::math::double_factorial<%1%>(unsigned)", 0, pol);
}

template <class T>
inline T double_factorial(unsigned i)
{
   return double_factorial<T>(i, policies::policy<>());
}

namespace detail{

template <class T, class Policy>
T rising_factorial_imp(T x, int n, const Policy& pol)
{
   static_assert(!std::is_integral<T>::value, "Type T must not be an integral type");
   if(x < 0)
   {
      //
      // For x less than zero, we really have a falling
      // factorial, modulo a possible change of sign.
      //
      // Note that the falling factorial isn't defined
      // for negative n, so we'll get rid of that case
      // first:
      //
      bool inv = false;
      if(n < 0)
      {
         x += n;
         n = -n;
         inv = true;
      }
      T result = ((n&1) ? -1 : 1) * falling_factorial(-x, n, pol);
      if(inv)
         result = 1 / result;
      return result;
   }
   if(n == 0)
      return 1;
   if(x == 0)
   {
      if(n < 0)
         return -boost::math::tgamma_delta_ratio(x + 1, static_cast<T>(-n), pol);
      else
         return 0;
   }
   if((x < 1) && (x + n < 0))
   {
      T val = boost::math::tgamma_delta_ratio(1 - x, static_cast<T>(-n), pol);
      return (n & 1) ? T(-val) : val;
   }
   //
   // We don't optimise this for small n, because
   // tgamma_delta_ratio is already optimised for that
   // use case:
   //
   return 1 / boost::math::tgamma_delta_ratio(x, static_cast<T>(n), pol);
}

template <class T, class Policy>
inline T falling_factorial_imp(T x, unsigned n, const Policy& pol)
{
   static_assert(!std::is_integral<T>::value, "Type T must not be an integral type");
   BOOST_MATH_STD_USING // ADL of std names
   if(x == 0)
      return 0;
   if(x < 0)
   {
      //
      // For x < 0 we really have a rising factorial
      // modulo a possible change of sign:
      //
      return (n&1 ? -1 : 1) * rising_factorial(-x, n, pol);
   }
   if(n == 0)
      return 1;
   if(x < 0.5f)
   {
      //
      // 1 + x below will throw away digits, so split up calculation:
      //
      if(n > max_factorial<T>::value - 2)
      {
         // If the two end of the range are far apart we have a ratio of two very large
         // numbers, split the calculation up into two blocks:
         T t1 = x * boost::math::falling_factorial(x - 1, max_factorial<T>::value - 2, pol);
         T t2 = boost::math::falling_factorial(x - max_factorial<T>::value + 1, n - max_factorial<T>::value + 1, pol);
         if(tools::max_value<T>() / fabs(t1) < fabs(t2))
            return boost::math::sign(t1) * boost::math::sign(t2) * policies::raise_overflow_error<T>("boost::math::falling_factorial<%1%>", 0, pol);
         return t1 * t2;
      }
      return x * boost::math::falling_factorial(x - 1, n - 1, pol);
   }
   if(x <= n - 1)
   {
      //
      // x+1-n will be negative and tgamma_delta_ratio won't
      // handle it, split the product up into three parts:
      //
      T xp1 = x + 1;
      unsigned n2 = itrunc((T)floor(xp1), pol);
      if(n2 == xp1)
         return 0;
      T result = boost::math::tgamma_delta_ratio(xp1, -static_cast<T>(n2), pol);
      x -= n2;
      result *= x;
      ++n2;
      if(n2 < n)
         result *= falling_factorial(x - 1, n - n2, pol);
      return result;
   }
   //
   // Simple case: just the ratio of two
   // (positive argument) gamma functions.
   // Note that we don't optimise this for small n,
   // because tgamma_delta_ratio is already optimised
   // for that use case:
   //
   return boost::math::tgamma_delta_ratio(x + 1, -static_cast<T>(n), pol);
}

} // namespace detail

template <class RT>
inline typename tools::promote_args<RT>::type
   falling_factorial(RT x, unsigned n)
{
   typedef typename tools::promote_args<RT>::type result_type;
   return detail::falling_factorial_imp(
      static_cast<result_type>(x), n, policies::policy<>());
}

template <class RT, class Policy>
inline typename tools::promote_args<RT>::type
   falling_factorial(RT x, unsigned n, const Policy& pol)
{
   typedef typename tools::promote_args<RT>::type result_type;
   return detail::falling_factorial_imp(
      static_cast<result_type>(x), n, pol);
}

template <class RT>
inline typename tools::promote_args<RT>::type
   rising_factorial(RT x, int n)
{
   typedef typename tools::promote_args<RT>::type result_type;
   return detail::rising_factorial_imp(
      static_cast<result_type>(x), n, policies::policy<>());
}

template <class RT, class Policy>
inline typename tools::promote_args<RT>::type
   rising_factorial(RT x, int n, const Policy& pol)
{
   typedef typename tools::promote_args<RT>::type result_type;
   return detail::rising_factorial_imp(
      static_cast<result_type>(x), n, pol);
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SP_FACTORIALS_HPP


/* factorials.hpp
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
*/