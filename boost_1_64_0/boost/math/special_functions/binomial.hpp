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
tWON6h/+5WQyCHtvP5xEpTpaLqRrSSAfwGKdOQ8T8dNehbpHrYvPplwD0Thpv25XmDaeUX3id/ief8IgUKuzKEY4g0XEPgY5DHRDoSdRa803de2+XhVKZrY1BXj4SCQHNAL6Nt4hTApGnjXziH8SRAzITpw81URXFfJs/SbcpzV+y8XCR+ub6fa/Yqez561zj0z8rRFiGgm9Ndx+105pWX6JRppTP/TEQnjfwx2NVhQAbHozox8emKtpIRc/5aV8hFNsUoLfV41I+cKdmV3vYSiyic6SZGmnxdz0YhWapyBg4VOLV6iDtRCFSS0HmmHJaXCWH6SvA/vJYjEqPKCbREHMb55GMx51t3XWjcCi7GBTff3c9uhqAQIJOGCIO88EJVJFN1u0kmb+vy+vkpnnkd79bArwI/TAXr7RJwjXrk19Opdk4rAYTef4uwFfEZfjmsNdsfvMzfrw+6uwnRJFgQB3O2mUcpDE8OCxpuhMYWK6I7StxRS8cx7U1kjKHf7kllGnAKVTJN1fxmStnbYtbhI5E757OkDkBlOeK/IPw6oBf4asb3fRifljXA==
*/