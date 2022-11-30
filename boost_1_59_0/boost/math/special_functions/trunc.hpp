//  Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TRUNC_HPP
#define BOOST_MATH_TRUNC_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <type_traits>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
inline typename tools::promote_args<T>::type trunc(const T& v, const Policy& pol, const std::false_type&)
{
   BOOST_MATH_STD_USING
   typedef typename tools::promote_args<T>::type result_type;
   if(!(boost::math::isfinite)(v))
      return policies::raise_rounding_error("boost::math::trunc<%1%>(%1%)", 0, static_cast<result_type>(v), static_cast<result_type>(v), pol);
   return (v >= 0) ? static_cast<result_type>(floor(v)) : static_cast<result_type>(ceil(v));
}

template <class T, class Policy>
inline typename tools::promote_args<T>::type trunc(const T& v, const Policy&, const std::true_type&)
{
   return v;
}

}

template <class T, class Policy>
inline typename tools::promote_args<T>::type trunc(const T& v, const Policy& pol)
{
   return detail::trunc(v, pol, std::integral_constant<bool, detail::is_integer_for_rounding<T>::value>());
}
template <class T>
inline typename tools::promote_args<T>::type trunc(const T& v)
{
   return trunc(v, policies::policy<>());
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
inline int itrunc(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   typedef typename tools::promote_args<T>::type result_type;
   result_type r = boost::math::trunc(v, pol);
   if(r > static_cast<result_type>((std::numeric_limits<int>::max)()) || r < static_cast<result_type>((std::numeric_limits<int>::min)()))
      return static_cast<int>(policies::raise_rounding_error("boost::math::itrunc<%1%>(%1%)", 0, static_cast<result_type>(v), 0, pol));
   return static_cast<int>(r);
}
template <class T>
inline int itrunc(const T& v)
{
   return itrunc(v, policies::policy<>());
}

template <class T, class Policy>
inline long ltrunc(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   typedef typename tools::promote_args<T>::type result_type;
   result_type r = boost::math::trunc(v, pol);
   if(r > static_cast<result_type>((std::numeric_limits<long>::max)()) || r < static_cast<result_type>((std::numeric_limits<long>::min)()))
      return static_cast<long>(policies::raise_rounding_error("boost::math::ltrunc<%1%>(%1%)", 0, static_cast<result_type>(v), 0L, pol));
   return static_cast<long>(r);
}
template <class T>
inline long ltrunc(const T& v)
{
   return ltrunc(v, policies::policy<>());
}

template <class T, class Policy>
inline long long lltrunc(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   typedef typename tools::promote_args<T>::type result_type;
   result_type r = boost::math::trunc(v, pol);
   if(r > static_cast<result_type>((std::numeric_limits<long long>::max)()) || 
      r < static_cast<result_type>((std::numeric_limits<long long>::min)()))
   {
      return static_cast<long long>(policies::raise_rounding_error("boost::math::lltrunc<%1%>(%1%)", 0, v, static_cast<long long>(0), pol));
   }
   return static_cast<long long>(r);
}
template <class T>
inline long long lltrunc(const T& v)
{
   return lltrunc(v, policies::policy<>());
}

template <class T, class Policy>
inline typename std::enable_if<std::is_constructible<int, T>::value, int>::type
   iconvert(const T& v, const Policy&) 
{
   return static_cast<int>(v);
}

template <class T, class Policy>
inline typename std::enable_if<!std::is_constructible<int, T>::value, int>::type
   iconvert(const T& v, const Policy& pol) 
{
   using boost::math::itrunc;
   return itrunc(v, pol);
}

template <class T, class Policy>
inline typename std::enable_if<std::is_constructible<long, T>::value, long>::type
   lconvert(const T& v, const Policy&) 
{
   return static_cast<long>(v);
}

template <class T, class Policy>
inline typename std::enable_if<!std::is_constructible<long, T>::value, long>::type
   lconvert(const T& v, const Policy& pol) 
{
   using boost::math::ltrunc;
   return ltrunc(v, pol);
}

template <class T, class Policy>
inline typename std::enable_if<std::is_constructible<long long, T>::value, long long>::type
   llconvertert(const T& v, const Policy&) 
{
   return static_cast<long long>(v);
}

template <class T, class Policy>
inline typename std::enable_if<!std::is_constructible<long long, T>::value, long long>::type
   llconvertert(const T& v, const Policy& pol) 
{
   using boost::math::lltrunc;
   return lltrunc(v, pol);
}

}} // namespaces

#endif // BOOST_MATH_TRUNC_HPP

/* trunc.hpp
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
*/