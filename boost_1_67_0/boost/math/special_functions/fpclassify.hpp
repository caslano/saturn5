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

#include <math.h>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/limits.hpp>
#include <boost/math/tools/real_cast.hpp>
#include <boost/type_traits/is_floating_point.hpp>
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

#if defined(_MSC_VER) || defined(__BORLANDC__)
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

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4800)
#endif

template <class T>
inline bool is_nan_helper(T t, const boost::true_type&)
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

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template <class T>
inline bool is_nan_helper(T, const boost::false_type&)
{
   return false;
}
#if defined(BOOST_MATH_USE_FLOAT128) 
#if defined(BOOST_MATH_HAS_QUADMATH_H)
inline bool is_nan_helper(__float128 f, const boost::true_type&) { return ::isnanq(f); }
inline bool is_nan_helper(__float128 f, const boost::false_type&) { return ::isnanq(f); }
#elif defined(BOOST_GNU_STDLIB) && BOOST_GNU_STDLIB && \
      _GLIBCXX_USE_C99_MATH && !_GLIBCXX_USE_C99_FP_MACROS_DYNAMIC
inline bool is_nan_helper(__float128 f, const boost::true_type&) { return std::isnan(static_cast<double>(f)); }
inline bool is_nan_helper(__float128 f, const boost::false_type&) { return std::isnan(static_cast<double>(f)); }
#else
inline bool is_nan_helper(__float128 f, const boost::true_type&) { return ::isnan(static_cast<double>(f)); }
inline bool is_nan_helper(__float128 f, const boost::false_type&) { return ::isnan(static_cast<double>(f)); }
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
   if(::boost::math_detail::is_nan_helper(t, ::boost::is_floating_point<T>()))
      return FP_NAN;
#elif defined(isnan)
   if(boost::math_detail::is_nan_helper(t, ::boost::is_floating_point<T>()))
      return FP_NAN;
#elif defined(_MSC_VER) || defined(__BORLANDC__)
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
   typedef BOOST_DEDUCED_TYPENAME fp_traits<T>::type traits;

   BOOST_MATH_INSTRUMENT_VARIABLE(x);

   BOOST_DEDUCED_TYPENAME traits::bits a;
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
   typedef BOOST_DEDUCED_TYPENAME fp_traits<T>::type traits;

   BOOST_MATH_INSTRUMENT_VARIABLE(x);

   BOOST_DEDUCED_TYPENAME traits::bits a;
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
        typedef BOOST_DEDUCED_TYPENAME detail::fp_traits<T>::type traits;
        BOOST_DEDUCED_TYPENAME traits::bits a;
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
        typedef BOOST_DEDUCED_TYPENAME detail::fp_traits<T>::type traits;
        BOOST_DEDUCED_TYPENAME traits::bits a;
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
        typedef BOOST_DEDUCED_TYPENAME fp_traits<T>::type traits;

        BOOST_DEDUCED_TYPENAME traits::bits a;
        traits::get_bits(x,a);
        a &= traits::exponent | traits::significand;
        return a == traits::exponent;
    }

    template<class T>
    inline bool isinf_impl(T x, ieee_copy_leading_bits_tag const&)
    {
        typedef BOOST_DEDUCED_TYPENAME fp_traits<T>::type traits;

        BOOST_DEDUCED_TYPENAME traits::bits a;
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
        typedef BOOST_DEDUCED_TYPENAME fp_traits<T>::type traits;

        BOOST_DEDUCED_TYPENAME traits::bits a;
        traits::get_bits(x,a);
        a &= traits::exponent | traits::significand;
        return a > traits::exponent;
    }

    template<class T>
    inline bool isnan_impl(T x, ieee_copy_leading_bits_tag const&)
    {
        typedef BOOST_DEDUCED_TYPENAME fp_traits<T>::type traits;

        BOOST_DEDUCED_TYPENAME traits::bits a;
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
template <> inline bool isnan BOOST_NO_MACRO_EXPAND<float>(float t){ return ::boost::math_detail::is_nan_helper(t, boost::true_type()); }
template <> inline bool isnan BOOST_NO_MACRO_EXPAND<double>(double t){ return ::boost::math_detail::is_nan_helper(t, boost::true_type()); }
template <> inline bool isnan BOOST_NO_MACRO_EXPAND<long double>(long double t){ return ::boost::math_detail::is_nan_helper(t, boost::true_type()); }
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