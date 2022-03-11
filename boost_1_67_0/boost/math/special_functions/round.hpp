//  Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_ROUND_HPP
#define BOOST_MATH_ROUND_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/config.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost{ namespace math{

namespace detail{

template <class T, class Policy>
inline typename tools::promote_args<T>::type round(const T& v, const Policy& pol, const boost::false_type&)
{
   BOOST_MATH_STD_USING
      typedef typename tools::promote_args<T>::type result_type;
   if(!(boost::math::isfinite)(v))
      return policies::raise_rounding_error("boost::math::round<%1%>(%1%)", 0, static_cast<result_type>(v), static_cast<result_type>(v), pol);
   //
   // The logic here is rather convoluted, but avoids a number of traps,
   // see discussion here https://github.com/boostorg/math/pull/8
   //
   if (-0.5 < v && v < 0.5)
   {
      // special case to avoid rounding error on the direct
      // predecessor of +0.5 resp. the direct successor of -0.5 in
      // IEEE floating point types
      return static_cast<result_type>(0);
   }
   else if (v > 0)
   {
      // subtract v from ceil(v) first in order to avoid rounding
      // errors on largest representable integer numbers
      result_type c(ceil(v));
      return 0.5 < c - v ? c - 1 : c;
   }
   else
   {
      // see former branch
      result_type f(floor(v));
      return 0.5 < v - f ? f + 1 : f;
   }
}
template <class T, class Policy>
inline typename tools::promote_args<T>::type round(const T& v, const Policy&, const boost::true_type&)
{
   return v;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type round(const T& v, const Policy& pol)
{
   return detail::round(v, pol, boost::integral_constant<bool, detail::is_integer_for_rounding<T>::value>());
}
template <class T>
inline typename tools::promote_args<T>::type round(const T& v)
{
   return round(v, policies::policy<>());
}
//
// The following functions will not compile unless T has an
// implicit conversion to the integer types.  For user-defined
// number types this will likely not be the case.  In that case
// these functions should either be specialized for the UDT in
// question, or else overloads should be placed in the same 
// namespace as the UDT: these will then be found via argument
// dependent lookup.  See our concept archetypes for examples.
//
template <class T, class Policy>
inline int iround(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   T r = boost::math::round(v, pol);
   if((r > (std::numeric_limits<int>::max)()) || (r < (std::numeric_limits<int>::min)()))
      return static_cast<int>(policies::raise_rounding_error("boost::math::iround<%1%>(%1%)", 0, v, 0, pol));
   return static_cast<int>(r);
}
template <class T>
inline int iround(const T& v)
{
   return iround(v, policies::policy<>());
}

template <class T, class Policy>
inline long lround(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   T r = boost::math::round(v, pol);
   if((r > (std::numeric_limits<long>::max)()) || (r < (std::numeric_limits<long>::min)()))
      return static_cast<long int>(policies::raise_rounding_error("boost::math::lround<%1%>(%1%)", 0, v, 0L, pol));
   return static_cast<long int>(r);
}
template <class T>
inline long lround(const T& v)
{
   return lround(v, policies::policy<>());
}

#ifdef BOOST_HAS_LONG_LONG

template <class T, class Policy>
inline boost::long_long_type llround(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   T r = boost::math::round(v, pol);
   if((r > (std::numeric_limits<boost::long_long_type>::max)()) || (r < (std::numeric_limits<boost::long_long_type>::min)()))
      return static_cast<boost::long_long_type>(policies::raise_rounding_error("boost::math::llround<%1%>(%1%)", 0, v, static_cast<boost::long_long_type>(0), pol));
   return static_cast<boost::long_long_type>(r);
}
template <class T>
inline boost::long_long_type llround(const T& v)
{
   return llround(v, policies::policy<>());
}

#endif

}} // namespaces

#endif // BOOST_MATH_ROUND_HPP

/* round.hpp
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
*/