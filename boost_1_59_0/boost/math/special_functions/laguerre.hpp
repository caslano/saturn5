
//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_LAGUERRE_HPP
#define BOOST_MATH_SPECIAL_LAGUERRE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/error_handling.hpp>

namespace boost{
namespace math{

// Recurrence relation for Laguerre polynomials:
template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type  
   laguerre_next(unsigned n, T1 x, T2 Ln, T3 Lnm1)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   return ((2 * n + 1 - result_type(x)) * result_type(Ln) - n * result_type(Lnm1)) / (n + 1);
}

namespace detail{

// Implement Laguerre polynomials via recurrence:
template <class T>
T laguerre_imp(unsigned n, T x)
{
   T p0 = 1;
   T p1 = 1 - x;

   if(n == 0)
      return p0;

   unsigned c = 1;

   while(c < n)
   {
      std::swap(p0, p1);
      p1 = laguerre_next(c, x, p0, p1);
      ++c;
   }
   return p1;
}

template <class T, class Policy>
inline typename tools::promote_args<T>::type 
laguerre(unsigned n, T x, const Policy&, const std::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::laguerre_imp(n, static_cast<value_type>(x)), "boost::math::laguerre<%1%>(unsigned, %1%)");
}

template <class T>
inline typename tools::promote_args<T>::type 
   laguerre(unsigned n, unsigned m, T x, const std::false_type&)
{
   return boost::math::laguerre(n, m, x, policies::policy<>());
}

} // namespace detail

template <class T>
inline typename tools::promote_args<T>::type 
   laguerre(unsigned n, T x)
{
   return laguerre(n, x, policies::policy<>());
}

// Recurrence for associated polynomials:
template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type  
   laguerre_next(unsigned n, unsigned l, T1 x, T2 Pl, T3 Plm1)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   return ((2 * n + l + 1 - result_type(x)) * result_type(Pl) - (n + l) * result_type(Plm1)) / (n+1);
}

namespace detail{
// Laguerre Associated Polynomial:
template <class T, class Policy>
T laguerre_imp(unsigned n, unsigned m, T x, const Policy& pol)
{
   // Special cases:
   if(m == 0)
      return boost::math::laguerre(n, x, pol);

   T p0 = 1;
   
   if(n == 0)
      return p0;

   T p1 = m + 1 - x;

   unsigned c = 1;

   while(c < n)
   {
      std::swap(p0, p1);
      p1 = laguerre_next(c, m, x, p0, p1);
      ++c;
   }
   return p1;
}

}

template <class T, class Policy>
inline typename tools::promote_args<T>::type 
   laguerre(unsigned n, unsigned m, T x, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::laguerre_imp(n, m, static_cast<value_type>(x), pol), "boost::math::laguerre<%1%>(unsigned, unsigned, %1%)");
}

template <class T1, class T2>
inline typename laguerre_result<T1, T2>::type 
   laguerre(unsigned n, T1 m, T2 x)
{
   typedef typename policies::is_policy<T2>::type tag_type;
   return detail::laguerre(n, m, x, tag_type());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SPECIAL_LAGUERRE_HPP




/* laguerre.hpp
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
*/