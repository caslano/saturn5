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
inline typename tools::promote_args<T>::type round(const T& v, const Policy& pol, const std::false_type&)
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
inline typename tools::promote_args<T>::type round(const T& v, const Policy&, const std::true_type&)
{
   return v;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type round(const T& v, const Policy& pol)
{
   return detail::round(v, pol, std::integral_constant<bool, detail::is_integer_for_rounding<T>::value>());
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
// Non-standard numeric limits syntax "(std::numeric_limits<int>::max)()" 
// is to avoid macro substiution from MSVC
// https://stackoverflow.com/questions/27442885/syntax-error-with-stdnumeric-limitsmax
//
template <class T, class Policy>
inline int iround(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   typedef typename tools::promote_args<T>::type result_type;
   T r = boost::math::round(v, pol);
   if(r > static_cast<result_type>((std::numeric_limits<int>::max)()) || r < static_cast<result_type>((std::numeric_limits<int>::min)()))
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
   typedef typename tools::promote_args<T>::type result_type;
   T r = boost::math::round(v, pol);
   if(r > static_cast<result_type>((std::numeric_limits<long>::max)()) || r < static_cast<result_type>((std::numeric_limits<long>::min)()))
      return static_cast<long int>(policies::raise_rounding_error("boost::math::lround<%1%>(%1%)", 0, v, 0L, pol));
   return static_cast<long int>(r);
}
template <class T>
inline long lround(const T& v)
{
   return lround(v, policies::policy<>());
}

template <class T, class Policy>
inline long long llround(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   typedef typename tools::promote_args<T>::type result_type;
   T r = boost::math::round(v, pol);
   if(r > static_cast<result_type>((std::numeric_limits<long long>::max)()) || 
      r < static_cast<result_type>((std::numeric_limits<long long>::min)()))
   {
      return static_cast<long long>(policies::raise_rounding_error("boost::math::llround<%1%>(%1%)", 0, v, static_cast<long long>(0), pol));
   }
   return static_cast<long long>(r);
}
template <class T>
inline long long llround(const T& v)
{
   return llround(v, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_ROUND_HPP

/* round.hpp
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
*/