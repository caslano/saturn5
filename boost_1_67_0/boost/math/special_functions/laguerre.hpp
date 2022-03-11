
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
laguerre(unsigned n, T x, const Policy&, const boost::true_type&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::laguerre_imp(n, static_cast<value_type>(x)), "boost::math::laguerre<%1%>(unsigned, %1%)");
}

template <class T>
inline typename tools::promote_args<T>::type 
   laguerre(unsigned n, unsigned m, T x, const boost::false_type&)
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