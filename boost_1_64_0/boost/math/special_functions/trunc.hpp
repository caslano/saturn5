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
PB8MvrYQNKX7TLsLQeRc/aDxdXmku+S/4ecSaXBr6/76C37/YKzb7kvz7HxKHdLmtxaCfWkk7dkkmzoUrEnT/qFNXtr4u3zSfSK30Rc/I61Kz1Bgj9gXFoKpdP3BC8HSbY0Jm65lpJGHeC9QOmTkWuR2xv9C7yNJ1+n4R1m7l6cc+eCCPywVB03HZ6RFqnV1pdz3u8WaND1cCAaHvK5e6ZDv57RhHBI3N143Ncc3c/8cYxS1Nq8sxgX3/nco2KD2JT8v/Mc+K//0PgiFf9jjhtjsUHDGPl0Nwn89FBynzJTjP3btCweDjjT6E+fk2SPUPxQco0CXYxe7R5foT52TI/Iz5cjRYcvXhDpjUr7nj988FFQuT3+hDMuL/q5A2iHmfZCTFJlf3/safvcdGR4yHiF7ZXpPcqheesR+dSg4RYEB8V8rS5Euod/YH5sNKgyJ7xsLcrSZs/xbeagyIfU7a4IifaK/FycZ6oxZGsnDLh2CP/hZmi3qjEn+0V5DFOkRvcS4kGWPYCw+NqgyIvEnfaBAm+BS9bJJjRHJy7RNhQGxif95wg4tgj8rwyZVdnvKsfKjQ/4Hpvn5lriIfUO/vmYM9ty/fK18Ud7POybdFONn5fmcvkrrDWP6cfF9Qh+pMuSoa+WaMST+UXFVHfuaWiq5/3bz8zbj/euFYFvaoLarHrJvNrY03iT/K9W7I2ZCfh+Yl2YfvRCMpKGX+vsSMoT8f47NjBgZEbvI2FEk/jzHtFl8vr6zR/wFYqJBZNsxTWIv9AzQIvoi16kyI/1ibTzHtScZmyeIc81YP+6Q/QWM1yOUuc5CMOfIOd5josmcDd9X1BmSWFwIjpGnwZyl63nGKdAj8Dq1So0BiRsoQ5YmQcLrGNtUmZG6ob81oMKE5I20S5F9ojdeCE6yQ5U+QVI5TpOnyYjYTfSBTcp0CW4qLyfZoc6QyM0WghXOUGCPCcklr7EU6BG++UJwlE3q7BO/hWtsU2XM4i0XglPkaDFhOaUuKkxI30pfaTImce5CcIIcLWakbq0Mu7QJ0l5ryVBjn8RtlCNLgzHx2+o7GVoEt1OODE3mHF42BuwRur1zMrQI7iBezlBmRPqO4qXBnNUV51QZkbqTWCkxJHGeMWCXHrE7i5M8HSKrYmSLBhNSd9EmFUakz18I1qmwz+JdzTNlRiwdlp8iXaJ3UyfbNJiQurv5JkuLOUv3EBtZmsxYPaIuSvSI3lNdZKhz9F5ipcKA6L3VwQ5VesxZOqqf7FBnSPQ+6mKLMl2C++ofp8hSZ8Ti/TwnbFNmQPiYfJTYJ3Z/9ZGhzpj0A8RPgQ7RB4qZHerMSR83R+wyIPYg9bBJmR6hC8w9axRpE3qw54MSPcInjBcblOlz+CHqocKA6IXqZoshsYeKh21q7JM4aT4pMmDxYdqlxJC1y/yt0sPFw2mK9Ik+Qt1s02RC8tRCcJwMVYbEH6lNdmgyI/0oY8kuLcYsPdqcUWdE/LT62aREh/Bj9JlNKgxZfKy5IkODMfHHqYsd6uwTXxMbOzSZkHq8+aLMkNgT5GGHOhNST5SHEj2CM+aBTcr0iD5JH8nSIfxkeVijyoDoU/SHDDX2ia97LsjSZMrSU40NOVrMWX6aeabGhNTTxUSRHpENdZOhyYzlZyhDlRHJZ6qXAh3Cz1KGDA2mpDc961TYJ/FsZSgyYPE5ztmlR+S5+s0OTeasbGmXCvsknqcMu/SJPd8Yk2OPOcsvUIYqIxLbylCgS+SF2iFLm9CLrAO2qDFh+cXmhCojFjPqoECbOamL9I8yQ+IvsU4o0CX8Us8QGVrMWdmxxqkxIv0ydVBmSPzl1h9Z2oReoQ62aTBlKWstUGJA/JU=
*/