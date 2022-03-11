//  (C) Copyright John Maddock 2008.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_NEXT_HPP
#define BOOST_MATH_SPECIAL_NEXT_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/math/special_functions/trunc.hpp>

#include <float.h>

#if !defined(_CRAYC) && !defined(__CUDACC__) && (!defined(__GNUC__) || (__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ > 3)))
#if (defined(_M_IX86_FP) && (_M_IX86_FP >= 2)) || defined(__SSE2__)
#include "xmmintrin.h"
#define BOOST_MATH_CHECK_SSE2
#endif
#endif

namespace boost{ namespace math{

   namespace concepts {

      class real_concept;
      class std_real_concept;

   }

namespace detail{

template <class T>
struct has_hidden_guard_digits;
template <>
struct has_hidden_guard_digits<float> : public boost::false_type {};
template <>
struct has_hidden_guard_digits<double> : public boost::false_type {};
template <>
struct has_hidden_guard_digits<long double> : public boost::false_type {};
#ifdef BOOST_HAS_FLOAT128
template <>
struct has_hidden_guard_digits<__float128> : public boost::false_type {};
#endif
template <>
struct has_hidden_guard_digits<boost::math::concepts::real_concept> : public boost::false_type {};
template <>
struct has_hidden_guard_digits<boost::math::concepts::std_real_concept> : public boost::false_type {};

template <class T, bool b>
struct has_hidden_guard_digits_10 : public boost::false_type {};
template <class T>
struct has_hidden_guard_digits_10<T, true> : public boost::integral_constant<bool, (std::numeric_limits<T>::digits10 != std::numeric_limits<T>::max_digits10)> {};

template <class T>
struct has_hidden_guard_digits 
   : public has_hidden_guard_digits_10<T, 
   std::numeric_limits<T>::is_specialized
   && (std::numeric_limits<T>::radix == 10) >
{};

template <class T>
inline const T& normalize_value(const T& val, const boost::false_type&) { return val; }
template <class T>
inline T normalize_value(const T& val, const boost::true_type&) 
{
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_specialized);
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::radix != 2);

   boost::intmax_t shift = (boost::intmax_t)std::numeric_limits<T>::digits - (boost::intmax_t)ilogb(val) - 1;
   T result = scalbn(val, shift);
   result = round(result);
   return scalbn(result, -shift); 
}

template <class T>
inline T get_smallest_value(boost::true_type const&)
{
   //
   // numeric_limits lies about denorms being present - particularly
   // when this can be turned on or off at runtime, as is the case
   // when using the SSE2 registers in DAZ or FTZ mode.
   //
   static const T m = std::numeric_limits<T>::denorm_min();
#ifdef BOOST_MATH_CHECK_SSE2
   return (_mm_getcsr() & (_MM_FLUSH_ZERO_ON | 0x40)) ? tools::min_value<T>() : m;;
#else
   return ((tools::min_value<T>() / 2) == 0) ? tools::min_value<T>() : m;
#endif
}

template <class T>
inline T get_smallest_value(boost::false_type const&)
{
   return tools::min_value<T>();
}

template <class T>
inline T get_smallest_value()
{
#if defined(BOOST_MSVC) && (BOOST_MSVC <= 1310)
   return get_smallest_value<T>(boost::integral_constant<bool, std::numeric_limits<T>::is_specialized && (std::numeric_limits<T>::has_denorm == 1)>());
#else
   return get_smallest_value<T>(boost::integral_constant<bool, std::numeric_limits<T>::is_specialized && (std::numeric_limits<T>::has_denorm == std::denorm_present)>());
#endif
}

//
// Returns the smallest value that won't generate denorms when
// we calculate the value of the least-significant-bit:
//
template <class T>
T get_min_shift_value();

template <class T>
struct min_shift_initializer
{
   struct init
   {
      init()
      {
         do_init();
      }
      static void do_init()
      {
         get_min_shift_value<T>();
      }
      void force_instantiate()const{}
   };
   static const init initializer;
   static void force_instantiate()
   {
      initializer.force_instantiate();
   }
};

template <class T>
const typename min_shift_initializer<T>::init min_shift_initializer<T>::initializer;

template <class T>
inline T calc_min_shifted(const boost::true_type&)
{
   BOOST_MATH_STD_USING
   return ldexp(tools::min_value<T>(), tools::digits<T>() + 1);
}
template <class T>
inline T calc_min_shifted(const boost::false_type&)
{
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_specialized);
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::radix != 2);

   return scalbn(tools::min_value<T>(), std::numeric_limits<T>::digits + 1);
}


template <class T>
inline T get_min_shift_value()
{
   static const T val = calc_min_shifted<T>(boost::integral_constant<bool, !std::numeric_limits<T>::is_specialized || std::numeric_limits<T>::radix == 2>());
   min_shift_initializer<T>::force_instantiate();

   return val;
}

template <class T, class Policy>
T float_next_imp(const T& val, const boost::true_type&, const Policy& pol)
{
   BOOST_MATH_STD_USING
   int expon;
   static const char* function = "float_next<%1%>(%1%)";

   int fpclass = (boost::math::fpclassify)(val);

   if((fpclass == (int)FP_NAN) || (fpclass == (int)FP_INFINITE))
   {
      if(val < 0)
         return -tools::max_value<T>();
      return policies::raise_domain_error<T>(
         function,
         "Argument must be finite, but got %1%", val, pol);
   }

   if(val >= tools::max_value<T>())
      return policies::raise_overflow_error<T>(function, 0, pol);

   if(val == 0)
      return detail::get_smallest_value<T>();

   if((fpclass != (int)FP_SUBNORMAL) && (fpclass != (int)FP_ZERO) && (fabs(val) < detail::get_min_shift_value<T>()) && (val != -tools::min_value<T>()))
   {
      //
      // Special case: if the value of the least significant bit is a denorm, and the result
      // would not be a denorm, then shift the input, increment, and shift back.
      // This avoids issues with the Intel SSE2 registers when the FTZ or DAZ flags are set.
      //
      return ldexp(float_next(T(ldexp(val, 2 * tools::digits<T>())), pol), -2 * tools::digits<T>());
   }

   if(-0.5f == frexp(val, &expon))
      --expon; // reduce exponent when val is a power of two, and negative.
   T diff = ldexp(T(1), expon - tools::digits<T>());
   if(diff == 0)
      diff = detail::get_smallest_value<T>();
   return val + diff;
} // float_next_imp
//
// Special version for some base other than 2:
//
template <class T, class Policy>
T float_next_imp(const T& val, const boost::false_type&, const Policy& pol)
{
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_specialized);
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::radix != 2);

   BOOST_MATH_STD_USING
   boost::intmax_t expon;
   static const char* function = "float_next<%1%>(%1%)";

   int fpclass = (boost::math::fpclassify)(val);

   if((fpclass == (int)FP_NAN) || (fpclass == (int)FP_INFINITE))
   {
      if(val < 0)
         return -tools::max_value<T>();
      return policies::raise_domain_error<T>(
         function,
         "Argument must be finite, but got %1%", val, pol);
   }

   if(val >= tools::max_value<T>())
      return policies::raise_overflow_error<T>(function, 0, pol);

   if(val == 0)
      return detail::get_smallest_value<T>();

   if((fpclass != (int)FP_SUBNORMAL) && (fpclass != (int)FP_ZERO) && (fabs(val) < detail::get_min_shift_value<T>()) && (val != -tools::min_value<T>()))
   {
      //
      // Special case: if the value of the least significant bit is a denorm, and the result
      // would not be a denorm, then shift the input, increment, and shift back.
      // This avoids issues with the Intel SSE2 registers when the FTZ or DAZ flags are set.
      //
      return scalbn(float_next(T(scalbn(val, 2 * std::numeric_limits<T>::digits)), pol), -2 * std::numeric_limits<T>::digits);
   }

   expon = 1 + ilogb(val);
   if(-1 == scalbn(val, -expon) * std::numeric_limits<T>::radix)
      --expon; // reduce exponent when val is a power of base, and negative.
   T diff = scalbn(T(1), expon - std::numeric_limits<T>::digits);
   if(diff == 0)
      diff = detail::get_smallest_value<T>();
   return val + diff;
} // float_next_imp

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type float_next(const T& val, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   return detail::float_next_imp(detail::normalize_value(static_cast<result_type>(val), typename detail::has_hidden_guard_digits<result_type>::type()), boost::integral_constant<bool, !std::numeric_limits<result_type>::is_specialized || (std::numeric_limits<result_type>::radix == 2)>(), pol);
}

#if 0 //def BOOST_MSVC
//
// We used to use ::_nextafter here, but doing so fails when using
// the SSE2 registers if the FTZ or DAZ flags are set, so use our own
// - albeit slower - code instead as at least that gives the correct answer.
//
template <class Policy>
inline double float_next(const double& val, const Policy& pol)
{
   static const char* function = "float_next<%1%>(%1%)";

   if(!(boost::math::isfinite)(val) && (val > 0))
      return policies::raise_domain_error<double>(
         function,
         "Argument must be finite, but got %1%", val, pol);

   if(val >= tools::max_value<double>())
      return policies::raise_overflow_error<double>(function, 0, pol);

   return ::_nextafter(val, tools::max_value<double>());
}
#endif

template <class T>
inline typename tools::promote_args<T>::type float_next(const T& val)
{
   return float_next(val, policies::policy<>());
}

namespace detail{

template <class T, class Policy>
T float_prior_imp(const T& val, const boost::true_type&, const Policy& pol)
{
   BOOST_MATH_STD_USING
   int expon;
   static const char* function = "float_prior<%1%>(%1%)";

   int fpclass = (boost::math::fpclassify)(val);

   if((fpclass == (int)FP_NAN) || (fpclass == (int)FP_INFINITE))
   {
      if(val > 0)
         return tools::max_value<T>();
      return policies::raise_domain_error<T>(
         function,
         "Argument must be finite, but got %1%", val, pol);
   }

   if(val <= -tools::max_value<T>())
      return -policies::raise_overflow_error<T>(function, 0, pol);

   if(val == 0)
      return -detail::get_smallest_value<T>();

   if((fpclass != (int)FP_SUBNORMAL) && (fpclass != (int)FP_ZERO) && (fabs(val) < detail::get_min_shift_value<T>()) && (val != tools::min_value<T>()))
   {
      //
      // Special case: if the value of the least significant bit is a denorm, and the result
      // would not be a denorm, then shift the input, increment, and shift back.
      // This avoids issues with the Intel SSE2 registers when the FTZ or DAZ flags are set.
      //
      return ldexp(float_prior(T(ldexp(val, 2 * tools::digits<T>())), pol), -2 * tools::digits<T>());
   }

   T remain = frexp(val, &expon);
   if(remain == 0.5f)
      --expon; // when val is a power of two we must reduce the exponent
   T diff = ldexp(T(1), expon - tools::digits<T>());
   if(diff == 0)
      diff = detail::get_smallest_value<T>();
   return val - diff;
} // float_prior_imp
//
// Special version for bases other than 2:
//
template <class T, class Policy>
T float_prior_imp(const T& val, const boost::false_type&, const Policy& pol)
{
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_specialized);
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::radix != 2);

   BOOST_MATH_STD_USING
   boost::intmax_t expon;
   static const char* function = "float_prior<%1%>(%1%)";

   int fpclass = (boost::math::fpclassify)(val);

   if((fpclass == (int)FP_NAN) || (fpclass == (int)FP_INFINITE))
   {
      if(val > 0)
         return tools::max_value<T>();
      return policies::raise_domain_error<T>(
         function,
         "Argument must be finite, but got %1%", val, pol);
   }

   if(val <= -tools::max_value<T>())
      return -policies::raise_overflow_error<T>(function, 0, pol);

   if(val == 0)
      return -detail::get_smallest_value<T>();

   if((fpclass != (int)FP_SUBNORMAL) && (fpclass != (int)FP_ZERO) && (fabs(val) < detail::get_min_shift_value<T>()) && (val != tools::min_value<T>()))
   {
      //
      // Special case: if the value of the least significant bit is a denorm, and the result
      // would not be a denorm, then shift the input, increment, and shift back.
      // This avoids issues with the Intel SSE2 registers when the FTZ or DAZ flags are set.
      //
      return scalbn(float_prior(T(scalbn(val, 2 * std::numeric_limits<T>::digits)), pol), -2 * std::numeric_limits<T>::digits);
   }

   expon = 1 + ilogb(val);
   T remain = scalbn(val, -expon);
   if(remain * std::numeric_limits<T>::radix == 1)
      --expon; // when val is a power of two we must reduce the exponent
   T diff = scalbn(T(1), expon - std::numeric_limits<T>::digits);
   if(diff == 0)
      diff = detail::get_smallest_value<T>();
   return val - diff;
} // float_prior_imp

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type float_prior(const T& val, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   return detail::float_prior_imp(detail::normalize_value(static_cast<result_type>(val), typename detail::has_hidden_guard_digits<result_type>::type()), boost::integral_constant<bool, !std::numeric_limits<result_type>::is_specialized || (std::numeric_limits<result_type>::radix == 2)>(), pol);
}

#if 0 //def BOOST_MSVC
//
// We used to use ::_nextafter here, but doing so fails when using
// the SSE2 registers if the FTZ or DAZ flags are set, so use our own
// - albeit slower - code instead as at least that gives the correct answer.
//
template <class Policy>
inline double float_prior(const double& val, const Policy& pol)
{
   static const char* function = "float_prior<%1%>(%1%)";

   if(!(boost::math::isfinite)(val) && (val < 0))
      return policies::raise_domain_error<double>(
         function,
         "Argument must be finite, but got %1%", val, pol);

   if(val <= -tools::max_value<double>())
      return -policies::raise_overflow_error<double>(function, 0, pol);

   return ::_nextafter(val, -tools::max_value<double>());
}
#endif

template <class T>
inline typename tools::promote_args<T>::type float_prior(const T& val)
{
   return float_prior(val, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type nextafter(const T& val, const U& direction, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   return val < direction ? boost::math::float_next<result_type>(val, pol) : val == direction ? val : boost::math::float_prior<result_type>(val, pol);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type nextafter(const T& val, const U& direction)
{
   return nextafter(val, direction, policies::policy<>());
}

namespace detail{

template <class T, class Policy>
T float_distance_imp(const T& a, const T& b, const boost::true_type&, const Policy& pol)
{
   BOOST_MATH_STD_USING
   //
   // Error handling:
   //
   static const char* function = "float_distance<%1%>(%1%, %1%)";
   if(!(boost::math::isfinite)(a))
      return policies::raise_domain_error<T>(
         function,
         "Argument a must be finite, but got %1%", a, pol);
   if(!(boost::math::isfinite)(b))
      return policies::raise_domain_error<T>(
         function,
         "Argument b must be finite, but got %1%", b, pol);
   //
   // Special cases:
   //
   if(a > b)
      return -float_distance(b, a, pol);
   if(a == b)
      return T(0);
   if(a == 0)
      return 1 + fabs(float_distance(static_cast<T>((b < 0) ? T(-detail::get_smallest_value<T>()) : detail::get_smallest_value<T>()), b, pol));
   if(b == 0)
      return 1 + fabs(float_distance(static_cast<T>((a < 0) ? T(-detail::get_smallest_value<T>()) : detail::get_smallest_value<T>()), a, pol));
   if(boost::math::sign(a) != boost::math::sign(b))
      return 2 + fabs(float_distance(static_cast<T>((b < 0) ? T(-detail::get_smallest_value<T>()) : detail::get_smallest_value<T>()), b, pol))
         + fabs(float_distance(static_cast<T>((a < 0) ? T(-detail::get_smallest_value<T>()) : detail::get_smallest_value<T>()), a, pol));
   //
   // By the time we get here, both a and b must have the same sign, we want
   // b > a and both positive for the following logic:
   //
   if(a < 0)
      return float_distance(static_cast<T>(-b), static_cast<T>(-a), pol);

   BOOST_ASSERT(a >= 0);
   BOOST_ASSERT(b >= a);

   int expon;
   //
   // Note that if a is a denorm then the usual formula fails
   // because we actually have fewer than tools::digits<T>()
   // significant bits in the representation:
   //
   (void)frexp(((boost::math::fpclassify)(a) == (int)FP_SUBNORMAL) ? tools::min_value<T>() : a, &expon);
   T upper = ldexp(T(1), expon);
   T result = T(0);
   //
   // If b is greater than upper, then we *must* split the calculation
   // as the size of the ULP changes with each order of magnitude change:
   //
   if(b > upper)
   {
      int expon2;
      (void)frexp(b, &expon2);
      T upper2 = ldexp(T(0.5), expon2);
      result = float_distance(upper2, b);
      result += (expon2 - expon - 1) * ldexp(T(1), tools::digits<T>() - 1);
   }
   //
   // Use compensated double-double addition to avoid rounding
   // errors in the subtraction:
   //
   expon = tools::digits<T>() - expon;
   T mb, x, y, z;
   if(((boost::math::fpclassify)(a) == (int)FP_SUBNORMAL) || (b - a < tools::min_value<T>()))
   {
      //
      // Special case - either one end of the range is a denormal, or else the difference is.
      // The regular code will fail if we're using the SSE2 registers on Intel and either
      // the FTZ or DAZ flags are set.
      //
      T a2 = ldexp(a, tools::digits<T>());
      T b2 = ldexp(b, tools::digits<T>());
      mb = -(std::min)(T(ldexp(upper, tools::digits<T>())), b2);
      x = a2 + mb;
      z = x - a2;
      y = (a2 - (x - z)) + (mb - z);

      expon -= tools::digits<T>();
   }
   else
   {
      mb = -(std::min)(upper, b);
      x = a + mb;
      z = x - a;
      y = (a - (x - z)) + (mb - z);
   }
   if(x < 0)
   {
      x = -x;
      y = -y;
   }
   result += ldexp(x, expon) + ldexp(y, expon);
   //
   // Result must be an integer:
   //
   BOOST_ASSERT(result == floor(result));
   return result;
} // float_distance_imp
//
// Special versions for bases other than 2:
//
template <class T, class Policy>
T float_distance_imp(const T& a, const T& b, const boost::false_type&, const Policy& pol)
{
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_specialized);
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::radix != 2);

   BOOST_MATH_STD_USING
   //
   // Error handling:
   //
   static const char* function = "float_distance<%1%>(%1%, %1%)";
   if(!(boost::math::isfinite)(a))
      return policies::raise_domain_error<T>(
         function,
         "Argument a must be finite, but got %1%", a, pol);
   if(!(boost::math::isfinite)(b))
      return policies::raise_domain_error<T>(
         function,
         "Argument b must be finite, but got %1%", b, pol);
   //
   // Special cases:
   //
   if(a > b)
      return -float_distance(b, a, pol);
   if(a == b)
      return T(0);
   if(a == 0)
      return 1 + fabs(float_distance(static_cast<T>((b < 0) ? T(-detail::get_smallest_value<T>()) : detail::get_smallest_value<T>()), b, pol));
   if(b == 0)
      return 1 + fabs(float_distance(static_cast<T>((a < 0) ? T(-detail::get_smallest_value<T>()) : detail::get_smallest_value<T>()), a, pol));
   if(boost::math::sign(a) != boost::math::sign(b))
      return 2 + fabs(float_distance(static_cast<T>((b < 0) ? T(-detail::get_smallest_value<T>()) : detail::get_smallest_value<T>()), b, pol))
         + fabs(float_distance(static_cast<T>((a < 0) ? T(-detail::get_smallest_value<T>()) : detail::get_smallest_value<T>()), a, pol));
   //
   // By the time we get here, both a and b must have the same sign, we want
   // b > a and both positive for the following logic:
   //
   if(a < 0)
      return float_distance(static_cast<T>(-b), static_cast<T>(-a), pol);

   BOOST_ASSERT(a >= 0);
   BOOST_ASSERT(b >= a);

   boost::intmax_t expon;
   //
   // Note that if a is a denorm then the usual formula fails
   // because we actually have fewer than tools::digits<T>()
   // significant bits in the representation:
   //
   expon = 1 + ilogb(((boost::math::fpclassify)(a) == (int)FP_SUBNORMAL) ? tools::min_value<T>() : a);
   T upper = scalbn(T(1), expon);
   T result = T(0);
   //
   // If b is greater than upper, then we *must* split the calculation
   // as the size of the ULP changes with each order of magnitude change:
   //
   if(b > upper)
   {
      boost::intmax_t expon2 = 1 + ilogb(b);
      T upper2 = scalbn(T(1), expon2 - 1);
      result = float_distance(upper2, b);
      result += (expon2 - expon - 1) * scalbn(T(1), std::numeric_limits<T>::digits - 1);
   }
   //
   // Use compensated double-double addition to avoid rounding
   // errors in the subtraction:
   //
   expon = std::numeric_limits<T>::digits - expon;
   T mb, x, y, z;
   if(((boost::math::fpclassify)(a) == (int)FP_SUBNORMAL) || (b - a < tools::min_value<T>()))
   {
      //
      // Special case - either one end of the range is a denormal, or else the difference is.
      // The regular code will fail if we're using the SSE2 registers on Intel and either
      // the FTZ or DAZ flags are set.
      //
      T a2 = scalbn(a, std::numeric_limits<T>::digits);
      T b2 = scalbn(b, std::numeric_limits<T>::digits);
      mb = -(std::min)(T(scalbn(upper, std::numeric_limits<T>::digits)), b2);
      x = a2 + mb;
      z = x - a2;
      y = (a2 - (x - z)) + (mb - z);

      expon -= std::numeric_limits<T>::digits;
   }
   else
   {
      mb = -(std::min)(upper, b);
      x = a + mb;
      z = x - a;
      y = (a - (x - z)) + (mb - z);
   }
   if(x < 0)
   {
      x = -x;
      y = -y;
   }
   result += scalbn(x, expon) + scalbn(y, expon);
   //
   // Result must be an integer:
   //
   BOOST_ASSERT(result == floor(result));
   return result;
} // float_distance_imp

} // namespace detail

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type float_distance(const T& a, const U& b, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   return detail::float_distance_imp(detail::normalize_value(static_cast<result_type>(a), typename detail::has_hidden_guard_digits<result_type>::type()), detail::normalize_value(static_cast<result_type>(b), typename detail::has_hidden_guard_digits<result_type>::type()), boost::integral_constant<bool, !std::numeric_limits<result_type>::is_specialized || (std::numeric_limits<result_type>::radix == 2)>(), pol);
}

template <class T, class U>
typename tools::promote_args<T, U>::type float_distance(const T& a, const U& b)
{
   return boost::math::float_distance(a, b, policies::policy<>());
}

namespace detail{

template <class T, class Policy>
T float_advance_imp(T val, int distance, const boost::true_type&, const Policy& pol)
{
   BOOST_MATH_STD_USING
   //
   // Error handling:
   //
   static const char* function = "float_advance<%1%>(%1%, int)";

   int fpclass = (boost::math::fpclassify)(val);

   if((fpclass == (int)FP_NAN) || (fpclass == (int)FP_INFINITE))
      return policies::raise_domain_error<T>(
         function,
         "Argument val must be finite, but got %1%", val, pol);

   if(val < 0)
      return -float_advance(-val, -distance, pol);
   if(distance == 0)
      return val;
   if(distance == 1)
      return float_next(val, pol);
   if(distance == -1)
      return float_prior(val, pol);

   if(fabs(val) < detail::get_min_shift_value<T>())
   {
      //
      // Special case: if the value of the least significant bit is a denorm,
      // implement in terms of float_next/float_prior.
      // This avoids issues with the Intel SSE2 registers when the FTZ or DAZ flags are set.
      //
      if(distance > 0)
      {
         do{ val = float_next(val, pol); } while(--distance);
      }
      else
      {
         do{ val = float_prior(val, pol); } while(++distance);
      }
      return val;
   }

   int expon;
   (void)frexp(val, &expon);
   T limit = ldexp((distance < 0 ? T(0.5f) : T(1)), expon);
   if(val <= tools::min_value<T>())
   {
      limit = sign(T(distance)) * tools::min_value<T>();
   }
   T limit_distance = float_distance(val, limit);
   while(fabs(limit_distance) < abs(distance))
   {
      distance -= itrunc(limit_distance);
      val = limit;
      if(distance < 0)
      {
         limit /= 2;
         expon--;
      }
      else
      {
         limit *= 2;
         expon++;
      }
      limit_distance = float_distance(val, limit);
      if(distance && (limit_distance == 0))
      {
         return policies::raise_evaluation_error<T>(function, "Internal logic failed while trying to increment floating point value %1%: most likely your FPU is in non-IEEE conforming mode.", val, pol);
      }
   }
   if((0.5f == frexp(val, &expon)) && (distance < 0))
      --expon;
   T diff = 0;
   if(val != 0)
      diff = distance * ldexp(T(1), expon - tools::digits<T>());
   if(diff == 0)
      diff = distance * detail::get_smallest_value<T>();
   return val += diff;
} // float_advance_imp
//
// Special version for bases other than 2:
//
template <class T, class Policy>
T float_advance_imp(T val, int distance, const boost::false_type&, const Policy& pol)
{
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_specialized);
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::radix != 2);

   BOOST_MATH_STD_USING
   //
   // Error handling:
   //
   static const char* function = "float_advance<%1%>(%1%, int)";

   int fpclass = (boost::math::fpclassify)(val);

   if((fpclass == (int)FP_NAN) || (fpclass == (int)FP_INFINITE))
      return policies::raise_domain_error<T>(
         function,
         "Argument val must be finite, but got %1%", val, pol);

   if(val < 0)
      return -float_advance(-val, -distance, pol);
   if(distance == 0)
      return val;
   if(distance == 1)
      return float_next(val, pol);
   if(distance == -1)
      return float_prior(val, pol);

   if(fabs(val) < detail::get_min_shift_value<T>())
   {
      //
      // Special case: if the value of the least significant bit is a denorm,
      // implement in terms of float_next/float_prior.
      // This avoids issues with the Intel SSE2 registers when the FTZ or DAZ flags are set.
      //
      if(distance > 0)
      {
         do{ val = float_next(val, pol); } while(--distance);
      }
      else
      {
         do{ val = float_prior(val, pol); } while(++distance);
      }
      return val;
   }

   boost::intmax_t expon = 1 + ilogb(val);
   T limit = scalbn(T(1), distance < 0 ? expon - 1 : expon);
   if(val <= tools::min_value<T>())
   {
      limit = sign(T(distance)) * tools::min_value<T>();
   }
   T limit_distance = float_distance(val, limit);
   while(fabs(limit_distance) < abs(distance))
   {
      distance -= itrunc(limit_distance);
      val = limit;
      if(distance < 0)
      {
         limit /= std::numeric_limits<T>::radix;
         expon--;
      }
      else
      {
         limit *= std::numeric_limits<T>::radix;
         expon++;
      }
      limit_distance = float_distance(val, limit);
      if(distance && (limit_distance == 0))
      {
         return policies::raise_evaluation_error<T>(function, "Internal logic failed while trying to increment floating point value %1%: most likely your FPU is in non-IEEE conforming mode.", val, pol);
      }
   }
   /*expon = 1 + ilogb(val);
   if((1 == scalbn(val, 1 + expon)) && (distance < 0))
      --expon;*/
   T diff = 0;
   if(val != 0)
      diff = distance * scalbn(T(1), expon - std::numeric_limits<T>::digits);
   if(diff == 0)
      diff = distance * detail::get_smallest_value<T>();
   return val += diff;
} // float_advance_imp

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type float_advance(T val, int distance, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   return detail::float_advance_imp(detail::normalize_value(static_cast<result_type>(val), typename detail::has_hidden_guard_digits<result_type>::type()), distance, boost::integral_constant<bool, !std::numeric_limits<result_type>::is_specialized || (std::numeric_limits<result_type>::radix == 2)>(), pol);
}

template <class T>
inline typename tools::promote_args<T>::type float_advance(const T& val, int distance)
{
   return boost::math::float_advance(val, distance, policies::policy<>());
}

}} // boost math namespaces

#endif // BOOST_MATH_SPECIAL_NEXT_HPP


/* next.hpp
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
*/