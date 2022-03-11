//  Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_PRECISION_INCLUDED
#define BOOST_MATH_TOOLS_PRECISION_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/limits.hpp>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/math/policies/policy.hpp>

// These two are for LDBL_MAN_DIG:
#include <limits.h>
#include <math.h>

namespace boost{ namespace math
{
namespace tools
{
// If T is not specialized, the functions digits, max_value and min_value,
// all get synthesised automatically from std::numeric_limits.
// However, if numeric_limits is not specialised for type RealType,
// for example with NTL::RR type, then you will get a compiler error
// when code tries to use these functions, unless you explicitly specialise them.

// For example if the precision of RealType varies at runtime,
// then numeric_limits support may not be appropriate,
// see boost/math/tools/ntl.hpp  for examples like
// template <> NTL::RR max_value<NTL::RR> ...
// See  Conceptual Requirements for Real Number Types.

template <class T>
inline BOOST_MATH_CONSTEXPR int digits(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(T)) BOOST_NOEXCEPT
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   BOOST_STATIC_ASSERT( ::std::numeric_limits<T>::is_specialized);
   BOOST_STATIC_ASSERT( ::std::numeric_limits<T>::radix == 2 || ::std::numeric_limits<T>::radix == 10);
#else
   BOOST_ASSERT(::std::numeric_limits<T>::is_specialized);
   BOOST_ASSERT(::std::numeric_limits<T>::radix == 2 || ::std::numeric_limits<T>::radix == 10);
#endif
   return std::numeric_limits<T>::radix == 2 
      ? std::numeric_limits<T>::digits
      : ((std::numeric_limits<T>::digits + 1) * 1000L) / 301L;
}

template <class T>
inline BOOST_MATH_CONSTEXPR T max_value(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T))  BOOST_MATH_NOEXCEPT(T)
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   BOOST_STATIC_ASSERT( ::std::numeric_limits<T>::is_specialized);
#else
   BOOST_ASSERT(::std::numeric_limits<T>::is_specialized);
#endif
   return (std::numeric_limits<T>::max)();
} // Also used as a finite 'infinite' value for - and +infinity, for example:
// -max_value<double> = -1.79769e+308, max_value<double> = 1.79769e+308.

template <class T>
inline BOOST_MATH_CONSTEXPR T min_value(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_MATH_NOEXCEPT(T)
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   BOOST_STATIC_ASSERT( ::std::numeric_limits<T>::is_specialized);
#else
   BOOST_ASSERT(::std::numeric_limits<T>::is_specialized);
#endif
   return (std::numeric_limits<T>::min)();
}

namespace detail{
//
// Logarithmic limits come next, note that although
// we can compute these from the log of the max value
// that is not in general thread safe (if we cache the value)
// so it's better to specialise these:
//
// For type float first:
//
template <class T>
inline BOOST_MATH_CONSTEXPR T log_max_value(const boost::integral_constant<int, 128>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_MATH_NOEXCEPT(T)
{
   return 88.0f;
}

template <class T>
inline BOOST_MATH_CONSTEXPR T log_min_value(const boost::integral_constant<int, 128>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_MATH_NOEXCEPT(T)
{
   return -87.0f;
}
//
// Now double:
//
template <class T>
inline BOOST_MATH_CONSTEXPR T log_max_value(const boost::integral_constant<int, 1024>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_MATH_NOEXCEPT(T)
{
   return 709.0;
}

template <class T>
inline BOOST_MATH_CONSTEXPR T log_min_value(const boost::integral_constant<int, 1024>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_MATH_NOEXCEPT(T)
{
   return -708.0;
}
//
// 80 and 128-bit long doubles:
//
template <class T>
inline BOOST_MATH_CONSTEXPR T log_max_value(const boost::integral_constant<int, 16384>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_MATH_NOEXCEPT(T)
{
   return 11356.0L;
}

template <class T>
inline BOOST_MATH_CONSTEXPR T log_min_value(const boost::integral_constant<int, 16384>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_MATH_NOEXCEPT(T)
{
   return -11355.0L;
}

template <class T>
inline T log_max_value(const boost::integral_constant<int, 0>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T))
{
   BOOST_MATH_STD_USING
#ifdef __SUNPRO_CC
   static const T m = boost::math::tools::max_value<T>();
   static const T val = log(m);
#else
   static const T val = log(boost::math::tools::max_value<T>());
#endif
   return val;
}

template <class T>
inline T log_min_value(const boost::integral_constant<int, 0>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T))
{
   BOOST_MATH_STD_USING
#ifdef __SUNPRO_CC
   static const T m = boost::math::tools::min_value<T>();
   static const T val = log(m);
#else
   static const T val = log(boost::math::tools::min_value<T>());
#endif
   return val;
}

template <class T>
inline BOOST_MATH_CONSTEXPR T epsilon(const boost::true_type& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_MATH_NOEXCEPT(T)
{
   return std::numeric_limits<T>::epsilon();
}

#if defined(__GNUC__) && ((LDBL_MANT_DIG == 106) || (__LDBL_MANT_DIG__ == 106))
template <>
inline BOOST_MATH_CONSTEXPR long double epsilon<long double>(const boost::true_type& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(long double)) BOOST_MATH_NOEXCEPT(long double)
{
   // numeric_limits on Darwin (and elsewhere) tells lies here:
   // the issue is that long double on a few platforms is
   // really a "double double" which has a non-contiguous
   // mantissa: 53 bits followed by an unspecified number of
   // zero bits, followed by 53 more bits.  Thus the apparent
   // precision of the type varies depending where it's been.
   // Set epsilon to the value that a 106 bit fixed mantissa
   // type would have, as that will give us sensible behaviour everywhere.
   //
   // This static assert fails for some unknown reason, so
   // disabled for now...
   // BOOST_STATIC_ASSERT(std::numeric_limits<long double>::digits == 106);
   return 2.4651903288156618919116517665087e-32L;
}
#endif

template <class T>
inline T epsilon(const boost::false_type& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T))
{
   // Note: don't cache result as precision may vary at runtime:
   BOOST_MATH_STD_USING  // for ADL of std names
   return ldexp(static_cast<T>(1), 1-policies::digits<T, policies::policy<> >());
}

template <class T>
struct log_limit_traits
{
   typedef typename mpl::if_c<
      (std::numeric_limits<T>::radix == 2) &&
      (std::numeric_limits<T>::max_exponent == 128
         || std::numeric_limits<T>::max_exponent == 1024
         || std::numeric_limits<T>::max_exponent == 16384),
      boost::integral_constant<int, (std::numeric_limits<T>::max_exponent > INT_MAX ? INT_MAX : static_cast<int>(std::numeric_limits<T>::max_exponent))>,
      boost::integral_constant<int, 0>
   >::type tag_type;
   BOOST_STATIC_CONSTANT(bool, value = tag_type::value ? true : false);
   BOOST_STATIC_ASSERT(::std::numeric_limits<T>::is_specialized || (value == 0));
};

template <class T, bool b> struct log_limit_noexcept_traits_imp : public log_limit_traits<T> {};
template <class T> struct log_limit_noexcept_traits_imp<T, false> : public boost::integral_constant<bool, false> {};

template <class T>
struct log_limit_noexcept_traits : public log_limit_noexcept_traits_imp<T, BOOST_MATH_IS_FLOAT(T)> {};

} // namespace detail

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4309)
#endif

template <class T>
inline BOOST_MATH_CONSTEXPR T log_max_value(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_NOEXCEPT_IF(detail::log_limit_noexcept_traits<T>::value)
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   return detail::log_max_value<T>(typename detail::log_limit_traits<T>::tag_type());
#else
   BOOST_ASSERT(::std::numeric_limits<T>::is_specialized);
   BOOST_MATH_STD_USING
   static const T val = log((std::numeric_limits<T>::max)());
   return val;
#endif
}

template <class T>
inline BOOST_MATH_CONSTEXPR T log_min_value(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) BOOST_NOEXCEPT_IF(detail::log_limit_noexcept_traits<T>::value)
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   return detail::log_min_value<T>(typename detail::log_limit_traits<T>::tag_type());
#else
   BOOST_ASSERT(::std::numeric_limits<T>::is_specialized);
   BOOST_MATH_STD_USING
   static const T val = log((std::numeric_limits<T>::min)());
   return val;
#endif
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template <class T>
inline BOOST_MATH_CONSTEXPR T epsilon(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(T)) BOOST_MATH_NOEXCEPT(T)
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   return detail::epsilon<T>(boost::integral_constant<bool, ::std::numeric_limits<T>::is_specialized>());
#else
   return ::std::numeric_limits<T>::is_specialized ?
      detail::epsilon<T>(boost::true_type()) :
      detail::epsilon<T>(boost::false_type());
#endif
}

namespace detail{

template <class T>
inline BOOST_MATH_CONSTEXPR T root_epsilon_imp(const boost::integral_constant<int, 24>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(0.00034526698300124390839884978618400831996329879769945L);
}

template <class T>
inline BOOST_MATH_CONSTEXPR T root_epsilon_imp(const T*, const boost::integral_constant<int, 53>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(0.1490116119384765625e-7L);
}

template <class T>
inline BOOST_MATH_CONSTEXPR T root_epsilon_imp(const T*, const boost::integral_constant<int, 64>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(0.32927225399135962333569506281281311031656150598474e-9L);
}

template <class T>
inline BOOST_MATH_CONSTEXPR T root_epsilon_imp(const T*, const boost::integral_constant<int, 113>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(0.1387778780781445675529539585113525390625e-16L);
}

template <class T, class Tag>
inline T root_epsilon_imp(const T*, const Tag&)
{
   BOOST_MATH_STD_USING
   static const T r_eps = sqrt(tools::epsilon<T>());
   return r_eps;
}

template <class T>
inline T root_epsilon_imp(const T*, const boost::integral_constant<int, 0>&)
{
   BOOST_MATH_STD_USING
   return sqrt(tools::epsilon<T>());
}

template <class T>
inline BOOST_MATH_CONSTEXPR T cbrt_epsilon_imp(const boost::integral_constant<int, 24>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(0.0049215666011518482998719164346805794944150447839903L);
}

template <class T>
inline BOOST_MATH_CONSTEXPR T cbrt_epsilon_imp(const T*, const boost::integral_constant<int, 53>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(6.05545445239333906078989272793696693569753008995e-6L);
}

template <class T>
inline BOOST_MATH_CONSTEXPR T cbrt_epsilon_imp(const T*, const boost::integral_constant<int, 64>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(4.76837158203125e-7L);
}

template <class T>
inline BOOST_MATH_CONSTEXPR T cbrt_epsilon_imp(const T*, const boost::integral_constant<int, 113>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(5.7749313854154005630396773604745549542403508090496e-12L);
}

template <class T, class Tag>
inline T cbrt_epsilon_imp(const T*, const Tag&)
{
   BOOST_MATH_STD_USING;
   static const T cbrt_eps = pow(tools::epsilon<T>(), T(1) / 3);
   return cbrt_eps;
}

template <class T>
inline T cbrt_epsilon_imp(const T*, const boost::integral_constant<int, 0>&)
{
   BOOST_MATH_STD_USING;
   return pow(tools::epsilon<T>(), T(1) / 3);
}

template <class T>
inline BOOST_MATH_CONSTEXPR T forth_root_epsilon_imp(const T*, const boost::integral_constant<int, 24>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(0.018581361171917516667460937040007436176452688944747L);
}

template <class T>
inline BOOST_MATH_CONSTEXPR T forth_root_epsilon_imp(const T*, const boost::integral_constant<int, 53>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(0.0001220703125L);
}

template <class T>
inline BOOST_MATH_CONSTEXPR T forth_root_epsilon_imp(const T*, const boost::integral_constant<int, 64>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(0.18145860519450699870567321328132261891067079047605e-4L);
}

template <class T>
inline BOOST_MATH_CONSTEXPR T forth_root_epsilon_imp(const T*, const boost::integral_constant<int, 113>&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(0.37252902984619140625e-8L);
}

template <class T, class Tag>
inline T forth_root_epsilon_imp(const T*, const Tag&)
{
   BOOST_MATH_STD_USING
   static const T r_eps = sqrt(sqrt(tools::epsilon<T>()));
   return r_eps;
}

template <class T>
inline T forth_root_epsilon_imp(const T*, const boost::integral_constant<int, 0>&)
{
   BOOST_MATH_STD_USING
   return sqrt(sqrt(tools::epsilon<T>()));
}

template <class T>
struct root_epsilon_traits
{
   typedef boost::integral_constant<int, (::std::numeric_limits<T>::radix == 2) && (::std::numeric_limits<T>::digits != INT_MAX) ? std::numeric_limits<T>::digits : 0> tag_type;
   BOOST_STATIC_CONSTANT(bool, has_noexcept = (tag_type::value == 113) || (tag_type::value == 64) || (tag_type::value == 53) || (tag_type::value == 24));
};

}

template <class T>
inline BOOST_MATH_CONSTEXPR T root_epsilon() BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && detail::root_epsilon_traits<T>::has_noexcept)
{
   return detail::root_epsilon_imp(static_cast<T const*>(0), typename detail::root_epsilon_traits<T>::tag_type());
}

template <class T>
inline BOOST_MATH_CONSTEXPR T cbrt_epsilon() BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && detail::root_epsilon_traits<T>::has_noexcept)
{
   return detail::cbrt_epsilon_imp(static_cast<T const*>(0), typename detail::root_epsilon_traits<T>::tag_type());
}

template <class T>
inline BOOST_MATH_CONSTEXPR T forth_root_epsilon() BOOST_NOEXCEPT_IF(BOOST_MATH_IS_FLOAT(T) && detail::root_epsilon_traits<T>::has_noexcept)
{
   return detail::forth_root_epsilon_imp(static_cast<T const*>(0), typename detail::root_epsilon_traits<T>::tag_type());
}

} // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_PRECISION_INCLUDED


/* precision.hpp
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
*/