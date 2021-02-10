
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
1K+pS8d2cnjdHdKuVYuAl0uH0olDwcGTw/TWLtxorvY0cOX9YH4Nht78KV5Ws94acJ85b5th1zf6NLfGUjK5ZtXwlorm9VXq9+SRvs89seWeX6n5vHD4k3TZFlouz/lp80L9bVBo2zwzT8tR77kTbyU7Px/aE/Xcma2nWb0Kjfm80Mx2S/TtdP7S24sTf+RHrJ9VJaR+bhh8/NpnHW2ajKWe6HVvI8mxz2E8NkNnuRsluZbeemMraM3qxLeGi82YVU/BNJoPWL0e2V7ZtQ5vxVtajONMPD2d8om1aC974jY56vvDtW28rLfiNJ8UrcHyOPL8ydZL2uO+q9e3yeRF1NnbWjGM1+FWXIrBNTmPy7p/TN36OdZn4vT1ic/bq+Fw9vwst7LDYaf7HeOpt1u9tP3NgX779p1EvbH7O4X+B1BLAwQKAAAACAAtZ0pS1WMoNPYCAADUAwAAMgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2NlcnRzL1NlcnZlci1sb2NhbGhvc3Qubm4tc3YuY3NyVVQFAAG2SCRgdVPHrptQFNzzFdmjJ2OKgeUFLnDBYDqGnSmmm2bTvj5Oss6sjjTS0WjKz88XAlSQ+UuEjodkJAIP/nKg7UPX+0P+YAZC4ksSRRDZIrDBGhzwaoBG
*/