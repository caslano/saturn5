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
lJ7ri9GhTser3i7u5DvPzcuwu9gHq0XltXt5JC220cE/tWBjGcqL/XC6rnusceI4ljgK5R4JOotbmFnwHp82q17utSe3eOUTz21f1tL2Gu0Yb7Vr8jZymDqc7Wv/7t6Hs0kA327+zr0NnfXPb8P2+F3oPyJv/dvQf0TeGk682v0ROoPNkr8NOxCePK7T1M1+TyQbzxlTPMupGa73W+wEmR/byXlmjZ9WtjGUjeRcbvgyLaS7us/uYa2NeSxd2dzaTme+d8y7vb14Ps67L8M1S1td0dC2N/PlWax3RScamNZk/UqSVZz6s+di6Ht1unnWp+VEF9P9MHVzthrc38rxuSi9ST6xW2f7OvST/HyZBzzdR+vYeGZTy4zI67V6XhOzPy7TyiT22o6zTncYOYOOPZjdom6xftpex6MWqXtjI0mt7b3fH0SLra2d58Zg+PpCDkdzX8TxzGHr12gemKofzSdstFY8M8zv43hVuNVu1FqFymt8eS1ya7cauD7PJoO3+YtX1R2ysdTDEi7YMe7X080i/lM+XZ7sdTkzrHTb329HY9Nt9Ueznbs67k9klnmjTrxZTLOeuDnmzDuydGgx1tml63Wdrod1G6s1IROLkdpWvF7YMXet9fLtFMo+GbKyw8R57NRjF3rCOTts
*/