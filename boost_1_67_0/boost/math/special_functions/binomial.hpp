//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SF_BINOMIAL_HPP
#define BOOST_MATH_SF_BINOMIAL_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/beta.hpp>
#include <boost/math/policies/error_handling.hpp>

namespace boost{ namespace math{

template <class T, class Policy>
T binomial_coefficient(unsigned n, unsigned k, const Policy& pol)
{
   BOOST_STATIC_ASSERT(!boost::is_integral<T>::value);
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::binomial_coefficient<%1%>(unsigned, unsigned)";
   if(k > n)
      return policies::raise_domain_error<T>(
         function, 
         "The binomial coefficient is undefined for k > n, but got k = %1%.",
         static_cast<T>(k), pol);
   T result;
   if((k == 0) || (k == n))
      return static_cast<T>(1);
   if((k == 1) || (k == n-1))
      return static_cast<T>(n);

   if(n <= max_factorial<T>::value)
   {
      // Use fast table lookup:
      result = unchecked_factorial<T>(n);
      result /= unchecked_factorial<T>(n-k);
      result /= unchecked_factorial<T>(k);
   }
   else
   {
      // Use the beta function:
      if(k < n - k)
         result = k * beta(static_cast<T>(k), static_cast<T>(n-k+1), pol);
      else
         result = (n - k) * beta(static_cast<T>(k+1), static_cast<T>(n-k), pol);
      if(result == 0)
         return policies::raise_overflow_error<T>(function, 0, pol);
      result = 1 / result;
   }
   // convert to nearest integer:
   return ceil(result - 0.5f);
}
//
// Type float can only store the first 35 factorials, in order to
// increase the chance that we can use a table driven implementation
// we'll promote to double:
//
template <>
inline float binomial_coefficient<float, policies::policy<> >(unsigned n, unsigned k, const policies::policy<>& pol)
{
   return policies::checked_narrowing_cast<float, policies::policy<> >(binomial_coefficient<double>(n, k, pol), "boost::math::binomial_coefficient<%1%>(unsigned,unsigned)");
}

template <class T>
inline T binomial_coefficient(unsigned n, unsigned k)
{
   return binomial_coefficient<T>(n, k, policies::policy<>());
}

} // namespace math
} // namespace boost


#endif // BOOST_MATH_SF_BINOMIAL_HPP




/* binomial.hpp
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
*/