
//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_HERMITE_HPP
#define BOOST_MATH_SPECIAL_HERMITE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/error_handling.hpp>

namespace boost{
namespace math{

// Recurrence relation for Hermite polynomials:
template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type 
   hermite_next(unsigned n, T1 x, T2 Hn, T3 Hnm1)
{
   return (2 * x * Hn - 2 * n * Hnm1);
}

namespace detail{

// Implement Hermite polynomials via recurrence:
template <class T>
T hermite_imp(unsigned n, T x)
{
   T p0 = 1;
   T p1 = 2 * x;

   if(n == 0)
      return p0;

   unsigned c = 1;

   while(c < n)
   {
      std::swap(p0, p1);
      p1 = hermite_next(c, x, p0, p1);
      ++c;
   }
   return p1;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type 
   hermite(unsigned n, T x, const Policy&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::hermite_imp(n, static_cast<value_type>(x)), "boost::math::hermite<%1%>(unsigned, %1%)");
}

template <class T>
inline typename tools::promote_args<T>::type 
   hermite(unsigned n, T x)
{
   return boost::math::hermite(n, x, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SPECIAL_HERMITE_HPP




/* hermite.hpp
QxwnfVblemC5RQD6hdXX0UfcjN9Wjjix8mcdULVcjfe9AWEs5uS9hdHkqHwRApxA5e1LxOynYU8HXQHDisC9jG2QGBaUJ1akvCeol8JmVMwWjeCUXLebMcpCNOXcXfjmhvnG1UDfim/+zdkcZo6I7aPsxI/LRAZUrEUhVDEFJ/F/TzvAbP81IWK3sCbEKXMtc5nRdmEenxvVNc0CwBGZNu95i5ZNJ8c5J6hP/pKT2I27qsNNdV6rDulTunPvjBGEie5vPPELx8XLrcQHABmzFkI/WH6D23yPInYcDYj21MWWx8ogT+ttGydB1YuqAJuVEIzsEVMk0yfx/61JAF5XaLzE8f6DrudqNThhFNfmMgKLGl8UWS5HIX0PWswclxhBktRLOUk0kDRgoEDGphnbVd1jZ7ftYMo/HsoA5sMK88MbkBnL6DbKyCFJ4zZBiz7qXz1L6/TOY8ftWD8nv7ClXyCtBvC0uKYJl1HRLzNKPoa0WXbQY083b1GhhHuO0nJtlr98ZPdz6QPFrxV3AcQVhpIaSvUHNrD5Ji97R7CQcCr9q08o12/4l/aOww==
*/