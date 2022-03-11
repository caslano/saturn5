//  Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TRUNC_HPP
#define BOOST_MATH_TRUNC_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/type_traits/is_constructible.hpp>
#include <boost/core/enable_if.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
inline typename tools::promote_args<T>::type trunc(const T& v, const Policy& pol, const boost::false_type&)
{
   BOOST_MATH_STD_USING
   typedef typename tools::promote_args<T>::type result_type;
   if(!(boost::math::isfinite)(v))
      return policies::raise_rounding_error("boost::math::trunc<%1%>(%1%)", 0, static_cast<result_type>(v), static_cast<result_type>(v), pol);
   return (v >= 0) ? static_cast<result_type>(floor(v)) : static_cast<result_type>(ceil(v));
}

template <class T, class Policy>
inline typename tools::promote_args<T>::type trunc(const T& v, const Policy&, const boost::true_type&)
{
   return v;
}

}

template <class T, class Policy>
inline typename tools::promote_args<T>::type trunc(const T& v, const Policy& pol)
{
   return detail::trunc(v, pol, boost::integral_constant<bool, detail::is_integer_for_rounding<T>::value>());
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
template <class T, class Policy>
inline int itrunc(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   typedef typename tools::promote_args<T>::type result_type;
   result_type r = boost::math::trunc(v, pol);
   if((r > (std::numeric_limits<int>::max)()) || (r < (std::numeric_limits<int>::min)()))
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
   if((r > (std::numeric_limits<long>::max)()) || (r < (std::numeric_limits<long>::min)()))
      return static_cast<long>(policies::raise_rounding_error("boost::math::ltrunc<%1%>(%1%)", 0, static_cast<result_type>(v), 0L, pol));
   return static_cast<long>(r);
}
template <class T>
inline long ltrunc(const T& v)
{
   return ltrunc(v, policies::policy<>());
}

#ifdef BOOST_HAS_LONG_LONG

template <class T, class Policy>
inline boost::long_long_type lltrunc(const T& v, const Policy& pol)
{
   BOOST_MATH_STD_USING
   typedef typename tools::promote_args<T>::type result_type;
   result_type r = boost::math::trunc(v, pol);
   if((r > (std::numeric_limits<boost::long_long_type>::max)()) || (r < (std::numeric_limits<boost::long_long_type>::min)()))
      return static_cast<boost::long_long_type>(policies::raise_rounding_error("boost::math::lltrunc<%1%>(%1%)", 0, v, static_cast<boost::long_long_type>(0), pol));
   return static_cast<boost::long_long_type>(r);
}
template <class T>
inline boost::long_long_type lltrunc(const T& v)
{
   return lltrunc(v, policies::policy<>());
}

#endif

template <class T, class Policy>
inline typename boost::enable_if_c<boost::is_constructible<int, T>::value, int>::type
   iconvert(const T& v, const Policy&) 
{
   return static_cast<int>(v);
}

template <class T, class Policy>
inline typename boost::disable_if_c<boost::is_constructible<int, T>::value, int>::type
   iconvert(const T& v, const Policy& pol) 
{
   using boost::math::itrunc;
   return itrunc(v, pol);
}

template <class T, class Policy>
inline typename boost::enable_if_c<boost::is_constructible<long, T>::value, long>::type
   lconvert(const T& v, const Policy&) 
{
   return static_cast<long>(v);
}

template <class T, class Policy>
inline typename boost::disable_if_c<boost::is_constructible<long, T>::value, long>::type
   lconvert(const T& v, const Policy& pol) 
{
   using boost::math::ltrunc;
   return ltrunc(v, pol);
}

#ifdef BOOST_HAS_LONG_LONG

template <class T, class Policy>
inline typename boost::enable_if_c<boost::is_constructible<boost::long_long_type, T>::value, boost::long_long_type>::type
   llconvertert(const T& v, const Policy&) 
{
   return static_cast<boost::long_long_type>(v);
}

template <class T, class Policy>
inline typename boost::disable_if_c<boost::is_constructible<boost::long_long_type, T>::value, boost::long_long_type>::type
   llconvertert(const T& v, const Policy& pol) 
{
   using boost::math::lltrunc;
   return lltrunc(v, pol);
}

#endif

}} // namespaces

#endif // BOOST_MATH_TRUNC_HPP

/* trunc.hpp
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
*/