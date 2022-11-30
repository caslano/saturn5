//  Copyright John Maddock 2005-2008.
//  Copyright (c) 2006-2008 Johan Rade
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_FPCLASSIFY_HPP
#define BOOST_MATH_FPCLASSIFY_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <limits>
#include <type_traits>
#include <cmath>
#include <boost/math/tools/real_cast.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/detail/fp_traits.hpp>
/*!
  \file fpclassify.hpp
  \brief Classify floating-point value as normal, subnormal, zero, infinite, or NaN.
  \version 1.0
  \author John Maddock
 */

/*

1. If the platform is C99 compliant, then the native floating point
classification functions are used.  However, note that we must only
define the functions which call std::fpclassify etc if that function
really does exist: otherwise a compiler may reject the code even though
the template is never instantiated.

2. If the platform is not C99 compliant, and the binary format for
a floating point type (float, double or long double) can be determined
at compile time, then the following algorithm is used:

        If all exponent bits, the flag bit (if there is one),
        and all significand bits are 0, then the number is zero.

        If all exponent bits and the flag bit (if there is one) are 0,
        and at least one significand bit is 1, then the number is subnormal.

        If all exponent bits are 1 and all significand bits are 0,
        then the number is infinity.

        If all exponent bits are 1 and at least one significand bit is 1,
        then the number is a not-a-number.

        Otherwise the number is normal.

        This algorithm works for the IEEE 754 representation,
        and also for several non IEEE 754 formats.

    Most formats have the structure
        sign bit + exponent bits + significand bits.

    A few have the structure
        sign bit + exponent bits + flag bit + significand bits.
    The flag bit is 0 for zero and subnormal numbers,
        and 1 for normal numbers and NaN.
        It is 0 (Motorola 68K) or 1 (Intel) for infinity.

    To get the bits, the four or eight most significant bytes are copied
    into an uint32_t or uint64_t and bit masks are applied.
    This covers all the exponent bits and the flag bit (if there is one),
    but not always all the significand bits.
    Some of the functions below have two implementations,
    depending on whether all the significand bits are copied or not.

3. If the platform is not C99 compliant, and the binary format for
a floating point type (float, double or long double) can not be determined
at compile time, then comparison with std::numeric_limits values
is used.

*/

#if defined(_MSC_VER) || defined(BOOST_BORLANDC)
#include <float.h>
#endif
#ifdef BOOST_MATH_USE_FLOAT128
#ifdef __has_include
#if  __has_include("quadmath.h")
#include "quadmath.h"
#define BOOST_MATH_HAS_QUADMATH_H
#endif
#endif
#endif

#ifdef BOOST_NO_STDC_NAMESPACE
  namespace std{ using ::abs; using ::fabs; }
#endif

namespace boost{

//
// This must not be located in any namespace under boost::math
// otherwise we can get into an infinite loop if isnan is
// a #define for "isnan" !
//
namespace math_detail{

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4800)
#endif

template <class T>
inline bool is_nan_helper(T t, const std::true_type&)
{
#ifdef isnan
   return isnan(t);
#elif defined(BOOST_MATH_DISABLE_STD_FPCLASSIFY) || !defined(BOOST_HAS_FPCLASSIFY)
   (void)t;
   return false;
#else // BOOST_HAS_FPCLASSIFY
   return (BOOST_FPCLASSIFY_PREFIX fpclassify(t) == (int)FP_NAN);
#endif
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

template <class T>
inline bool is_nan_helper(T, const std::false_type&)
{
   return false;
}
#if defined(BOOST_MATH_USE_FLOAT128) 
#if defined(BOOST_MATH_HAS_QUADMATH_H)
inline bool is_nan_helper(__float128 f, const std::true_type&) { return ::isnanq(f); }
inline bool is_nan_helper(__float128 f, const std::false_type&) { return ::isnanq(f); }
#elif defined(BOOST_GNU_STDLIB) && BOOST_GNU_STDLIB && \
      _GLIBCXX_USE_C99_MATH && !_GLIBCXX_USE_C99_FP_MACROS_DYNAMIC
inline bool is_nan_helper(__float128 f, const std::true_type&) { return std::isnan(static_cast<double>(f)); }
inline bool is_nan_helper(__float128 f, const std::false_type&) { return std::isnan(static_cast<double>(f)); }
#else
inline bool is_nan_helper(__float128 f, const std::true_type&) { return boost::math::isnan(static_cast<double>(f)); }
inline bool is_nan_helper(__float128 f, const std::false_type&) { return boost::math::isnan(static_cast<double>(f)); }
#endif
#endif
}

namespace math{

namespace detail{

#ifdef BOOST_MATH_USE_STD_FPCLASSIFY
template <class T>
inline int fpclassify_imp BOOST_NO_MACRO_EXPAND(T t, const native_tag&)
{
   return (std::fpclassify)(t);
}
#endif

template <class T>
inline int fpclassify_imp BOOST_NO_MACRO_EXPAND(T t, const generic_tag<true>&)
{
   BOOST_MATH_INSTRUMENT_VARIABLE(t);

   // whenever possible check for Nan's first:
#if defined(BOOST_HAS_FPCLASSIFY)  && !defined(BOOST_MATH_DISABLE_STD_FPCLASSIFY)
   if(::boost::math_detail::is_nan_helper(t, typename std::is_floating_point<T>::type()))
      return FP_NAN;
#elif defined(isnan)
   if(boost::math_detail::is_nan_helper(t, typename std::is_floating_point<T>::type()))
      return FP_NAN;
#elif defined(_MSC_VER) || defined(BOOST_BORLANDC)
   if(::_isnan(boost::math::tools::real_cast<double>(t)))
      return FP_NAN;
#endif
   // std::fabs broken on a few systems especially for long long!!!!
   T at = (t < T(0)) ? -t : t;

   // Use a process of exclusion to figure out
   // what kind of type we have, this relies on
   // IEEE conforming reals that will treat
   // Nan's as unordered.  Some compilers
   // don't do this once optimisations are
   // turned on, hence the check for nan's above.
   if(at <= (std::numeric_limits<T>::max)())
   {
      if(at >= (std::numeric_limits<T>::min)())
         return FP_NORMAL;
      return (at != 0) ? FP_SUBNORMAL : FP_ZERO;
   }
   else if(at > (std::numeric_limits<T>::max)())
      return FP_INFINITE;
   return FP_NAN;
}

template <class T>
inline int fpclassify_imp BOOST_NO_MACRO_EXPAND(T t, const generic_tag<false>&)
{
#ifdef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   if(std::numeric_limits<T>::is_specialized)
      return fpclassify_imp(t, generic_tag<true>());
#endif
   //
   // An unknown type with no numeric_limits support,
   // so what are we supposed to do we do here?
   //
   BOOST_MATH_INSTRUMENT_VARIABLE(t);

   return t == 0 ? FP_ZERO : FP_NORMAL;
}

template<class T>
int fpclassify_imp BOOST_NO_MACRO_EXPAND(T x, ieee_copy_all_bits_tag)
{
   typedef typename fp_traits<T>::type traits;

   BOOST_MATH_INSTRUMENT_VARIABLE(x);

   typename traits::bits a;
   traits::get_bits(x,a);
   BOOST_MATH_INSTRUMENT_VARIABLE(a);
   a &= traits::exponent | traits::flag | traits::significand;
   BOOST_MATH_INSTRUMENT_VARIABLE((traits::exponent | traits::flag | traits::significand));
   BOOST_MATH_INSTRUMENT_VARIABLE(a);

   if(a <= traits::significand) {
      if(a == 0)
         return FP_ZERO;
      else
         return FP_SUBNORMAL;
   }

   if(a < traits::exponent) return FP_NORMAL;

   a &= traits::significand;
   if(a == 0) return FP_INFINITE;

   return FP_NAN;
}

template<class T>
int fpclassify_imp BOOST_NO_MACRO_EXPAND(T x, ieee_copy_leading_bits_tag)
{
   typedef typename fp_traits<T>::type traits;

   BOOST_MATH_INSTRUMENT_VARIABLE(x);

   typename traits::bits a;
   traits::get_bits(x,a);
   a &= traits::exponent | traits::flag | traits::significand;

   if(a <= traits::significand) {
      if(x == 0)
         return FP_ZERO;
      else
         return FP_SUBNORMAL;
   }

   if(a < traits::exponent) return FP_NORMAL;

   a &= traits::significand;
   traits::set_bits(x,a);
   if(x == 0) return FP_INFINITE;

   return FP_NAN;
}

#if defined(BOOST_MATH_USE_STD_FPCLASSIFY) && (defined(BOOST_MATH_NO_NATIVE_LONG_DOUBLE_FP_CLASSIFY) || defined(BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS))
inline int fpclassify_imp BOOST_NO_MACRO_EXPAND(long double t, const native_tag&)
{
   return boost::math::detail::fpclassify_imp(t, generic_tag<true>());
}
#endif

}  // namespace detail

template <class T>
inline int fpclassify BOOST_NO_MACRO_EXPAND(T t)
{
   typedef typename detail::fp_traits<T>::type traits;
   typedef typename traits::method method;
   typedef typename tools::promote_args_permissive<T>::type value_type;
#ifdef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   if(std::numeric_limits<T>::is_specialized && detail::is_generic_tag_false(static_cast<method*>(0)))
      return detail::fpclassify_imp(static_cast<value_type>(t), detail::generic_tag<true>());
   return detail::fpclassify_imp(static_cast<value_type>(t), method());
#else
   return detail::fpclassify_imp(static_cast<value_type>(t), method());
#endif
}

#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
template <>
inline int fpclassify<long double> BOOST_NO_MACRO_EXPAND(long double t)
{
   typedef detail::fp_traits<long double>::type traits;
   typedef traits::method method;
   typedef long double value_type;
#ifdef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   if(std::numeric_limits<long double>::is_specialized && detail::is_generic_tag_false(static_cast<method*>(0)))
      return detail::fpclassify_imp(static_cast<value_type>(t), detail::generic_tag<true>());
   return detail::fpclassify_imp(static_cast<value_type>(t), method());
#else
   return detail::fpclassify_imp(static_cast<value_type>(t), method());
#endif
}
#endif

namespace detail {

#ifdef BOOST_MATH_USE_STD_FPCLASSIFY
    template<class T>
    inline bool isfinite_impl(T x, native_tag const&)
    {
        return (std::isfinite)(x);
    }
#endif

    template<class T>
    inline bool isfinite_impl(T x, generic_tag<true> const&)
    {
        return x >= -(std::numeric_limits<T>::max)()
            && x <= (std::numeric_limits<T>::max)();
    }

    template<class T>
    inline bool isfinite_impl(T x, generic_tag<false> const&)
    {
#ifdef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
      if(std::numeric_limits<T>::is_specialized)
         return isfinite_impl(x, generic_tag<true>());
#endif
       (void)x; // warning suppression.
       return true;
    }

    template<class T>
    inline bool isfinite_impl(T x, ieee_tag const&)
    {
        typedef typename detail::fp_traits<T>::type traits;
        typename traits::bits a;
        traits::get_bits(x,a);
        a &= traits::exponent;
        return a != traits::exponent;
    }

#if defined(BOOST_MATH_USE_STD_FPCLASSIFY) && defined(BOOST_MATH_NO_NATIVE_LONG_DOUBLE_FP_CLASSIFY)
inline bool isfinite_impl BOOST_NO_MACRO_EXPAND(long double t, const native_tag&)
{
   return boost::math::detail::isfinite_impl(t, generic_tag<true>());
}
#endif

}

template<class T>
inline bool (isfinite)(T x)
{ //!< \brief return true if floating-point type t is finite.
   typedef typename detail::fp_traits<T>::type traits;
   typedef typename traits::method method;
   // typedef typename boost::is_floating_point<T>::type fp_tag;
   typedef typename tools::promote_args_permissive<T>::type value_type;
   return detail::isfinite_impl(static_cast<value_type>(x), method());
}

#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
template<>
inline bool (isfinite)(long double x)
{ //!< \brief return true if floating-point type t is finite.
   typedef detail::fp_traits<long double>::type traits;
   typedef traits::method method;
   //typedef boost::is_floating_point<long double>::type fp_tag;
   typedef long double value_type;
   return detail::isfinite_impl(static_cast<value_type>(x), method());
}
#endif

//------------------------------------------------------------------------------

namespace detail {

#ifdef BOOST_MATH_USE_STD_FPCLASSIFY
    template<class T>
    inline bool isnormal_impl(T x, native_tag const&)
    {
        return (std::isnormal)(x);
    }
#endif

    template<class T>
    inline bool isnormal_impl(T x, generic_tag<true> const&)
    {
        if(x < 0) x = -x;
        return x >= (std::numeric_limits<T>::min)()
            && x <= (std::numeric_limits<T>::max)();
    }

    template<class T>
    inline bool isnormal_impl(T x, generic_tag<false> const&)
    {
#ifdef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
      if(std::numeric_limits<T>::is_specialized)
         return isnormal_impl(x, generic_tag<true>());
#endif
       return !(x == 0);
    }

    template<class T>
    inline bool isnormal_impl(T x, ieee_tag const&)
    {
        typedef typename detail::fp_traits<T>::type traits;
        typename traits::bits a;
        traits::get_bits(x,a);
        a &= traits::exponent | traits::flag;
        return (a != 0) && (a < traits::exponent);
    }

#if defined(BOOST_MATH_USE_STD_FPCLASSIFY) && defined(BOOST_MATH_NO_NATIVE_LONG_DOUBLE_FP_CLASSIFY)
inline bool isnormal_impl BOOST_NO_MACRO_EXPAND(long double t, const native_tag&)
{
   return boost::math::detail::isnormal_impl(t, generic_tag<true>());
}
#endif

}

template<class T>
inline bool (isnormal)(T x)
{
   typedef typename detail::fp_traits<T>::type traits;
   typedef typename traits::method method;
   //typedef typename boost::is_floating_point<T>::type fp_tag;
   typedef typename tools::promote_args_permissive<T>::type value_type;
   return detail::isnormal_impl(static_cast<value_type>(x), method());
}

#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
template<>
inline bool (isnormal)(long double x)
{
   typedef detail::fp_traits<long double>::type traits;
   typedef traits::method method;
   //typedef boost::is_floating_point<long double>::type fp_tag;
   typedef long double value_type;
   return detail::isnormal_impl(static_cast<value_type>(x), method());
}
#endif

//------------------------------------------------------------------------------

namespace detail {

#ifdef BOOST_MATH_USE_STD_FPCLASSIFY
    template<class T>
    inline bool isinf_impl(T x, native_tag const&)
    {
        return (std::isinf)(x);
    }
#endif

    template<class T>
    inline bool isinf_impl(T x, generic_tag<true> const&)
    {
        (void)x; // in case the compiler thinks that x is unused because std::numeric_limits<T>::has_infinity is false
        return std::numeric_limits<T>::has_infinity
            && ( x == std::numeric_limits<T>::infinity()
                 || x == -std::numeric_limits<T>::infinity());
    }

    template<class T>
    inline bool isinf_impl(T x, generic_tag<false> const&)
    {
#ifdef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
      if(std::numeric_limits<T>::is_specialized)
         return isinf_impl(x, generic_tag<true>());
#endif
        (void)x; // warning suppression.
        return false;
    }

    template<class T>
    inline bool isinf_impl(T x, ieee_copy_all_bits_tag const&)
    {
        typedef typename fp_traits<T>::type traits;

        typename traits::bits a;
        traits::get_bits(x,a);
        a &= traits::exponent | traits::significand;
        return a == traits::exponent;
    }

    template<class T>
    inline bool isinf_impl(T x, ieee_copy_leading_bits_tag const&)
    {
        typedef typename fp_traits<T>::type traits;

        typename traits::bits a;
        traits::get_bits(x,a);
        a &= traits::exponent | traits::significand;
        if(a != traits::exponent)
            return false;

        traits::set_bits(x,0);
        return x == 0;
    }

#if defined(BOOST_MATH_USE_STD_FPCLASSIFY) && defined(BOOST_MATH_NO_NATIVE_LONG_DOUBLE_FP_CLASSIFY)
inline bool isinf_impl BOOST_NO_MACRO_EXPAND(long double t, const native_tag&)
{
   return boost::math::detail::isinf_impl(t, generic_tag<true>());
}
#endif

}   // namespace detail

template<class T>
inline bool (isinf)(T x)
{
   typedef typename detail::fp_traits<T>::type traits;
   typedef typename traits::method method;
   // typedef typename boost::is_floating_point<T>::type fp_tag;
   typedef typename tools::promote_args_permissive<T>::type value_type;
   return detail::isinf_impl(static_cast<value_type>(x), method());
}

#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
template<>
inline bool (isinf)(long double x)
{
   typedef detail::fp_traits<long double>::type traits;
   typedef traits::method method;
   //typedef boost::is_floating_point<long double>::type fp_tag;
   typedef long double value_type;
   return detail::isinf_impl(static_cast<value_type>(x), method());
}
#endif
#if defined(BOOST_MATH_USE_FLOAT128) && defined(BOOST_MATH_HAS_QUADMATH_H)
template<>
inline bool (isinf)(__float128 x)
{
   return ::isinfq(x);
}
#endif

//------------------------------------------------------------------------------

namespace detail {

#ifdef BOOST_MATH_USE_STD_FPCLASSIFY
    template<class T>
    inline bool isnan_impl(T x, native_tag const&)
    {
        return (std::isnan)(x);
    }
#endif

    template<class T>
    inline bool isnan_impl(T x, generic_tag<true> const&)
    {
        return std::numeric_limits<T>::has_infinity
            ? !(x <= std::numeric_limits<T>::infinity())
            : x != x;
    }

    template<class T>
    inline bool isnan_impl(T x, generic_tag<false> const&)
    {
#ifdef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
      if(std::numeric_limits<T>::is_specialized)
         return isnan_impl(x, generic_tag<true>());
#endif
        (void)x; // warning suppression
        return false;
    }

    template<class T>
    inline bool isnan_impl(T x, ieee_copy_all_bits_tag const&)
    {
        typedef typename fp_traits<T>::type traits;

        typename traits::bits a;
        traits::get_bits(x,a);
        a &= traits::exponent | traits::significand;
        return a > traits::exponent;
    }

    template<class T>
    inline bool isnan_impl(T x, ieee_copy_leading_bits_tag const&)
    {
        typedef typename fp_traits<T>::type traits;

        typename traits::bits a;
        traits::get_bits(x,a);

        a &= traits::exponent | traits::significand;
        if(a < traits::exponent)
            return false;

        a &= traits::significand;
        traits::set_bits(x,a);
        return x != 0;
    }

}   // namespace detail

template<class T>
inline bool (isnan)(T x)
{ //!< \brief return true if floating-point type t is NaN (Not A Number).
   typedef typename detail::fp_traits<T>::type traits;
   typedef typename traits::method method;
   // typedef typename boost::is_floating_point<T>::type fp_tag;
   return detail::isnan_impl(x, method());
}

#ifdef isnan
template <> inline bool isnan BOOST_NO_MACRO_EXPAND<float>(float t){ return ::boost::math_detail::is_nan_helper(t, std::true_type()); }
template <> inline bool isnan BOOST_NO_MACRO_EXPAND<double>(double t){ return ::boost::math_detail::is_nan_helper(t, std::true_type()); }
template <> inline bool isnan BOOST_NO_MACRO_EXPAND<long double>(long double t){ return ::boost::math_detail::is_nan_helper(t, std::true_type()); }
#elif defined(BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS)
template<>
inline bool (isnan)(long double x)
{ //!< \brief return true if floating-point type t is NaN (Not A Number).
   typedef detail::fp_traits<long double>::type traits;
   typedef traits::method method;
   //typedef boost::is_floating_point<long double>::type fp_tag;
   return detail::isnan_impl(x, method());
}
#endif
#if defined(BOOST_MATH_USE_FLOAT128) && defined(BOOST_MATH_HAS_QUADMATH_H)
template<>
inline bool (isnan)(__float128 x)
{
   return ::isnanq(x);
}
#endif

} // namespace math
} // namespace boost
#endif // BOOST_MATH_FPCLASSIFY_HPP


/* fpclassify.hpp
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
*/