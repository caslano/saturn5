//  Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_PRECISION_INCLUDED
#define BOOST_MATH_TOOLS_PRECISION_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/tools/assert.hpp>
#include <boost/math/policies/policy.hpp>
#include <type_traits>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cfloat> // LDBL_MANT_DIG

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
inline constexpr int digits(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(T)) noexcept
{
   static_assert( ::std::numeric_limits<T>::is_specialized, "Type T must be specialized");
   static_assert( ::std::numeric_limits<T>::radix == 2 || ::std::numeric_limits<T>::radix == 10, "Type T must have a radix of 2 or 10");

   return std::numeric_limits<T>::radix == 2 
      ? std::numeric_limits<T>::digits
      : ((std::numeric_limits<T>::digits + 1) * 1000L) / 301L;
}

template <class T>
inline constexpr T max_value(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T))  noexcept(std::is_floating_point<T>::value)
{
   static_assert( ::std::numeric_limits<T>::is_specialized, "Type T must be specialized");
   return (std::numeric_limits<T>::max)();
} // Also used as a finite 'infinite' value for - and +infinity, for example:
// -max_value<double> = -1.79769e+308, max_value<double> = 1.79769e+308.

template <class T>
inline constexpr T min_value(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(std::is_floating_point<T>::value)
{
   static_assert( ::std::numeric_limits<T>::is_specialized, "Type T must be specialized");

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
inline constexpr T log_max_value(const std::integral_constant<int, 128>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(std::is_floating_point<T>::value)
{
   return 88.0f;
}

template <class T>
inline constexpr T log_min_value(const std::integral_constant<int, 128>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(std::is_floating_point<T>::value)
{
   return -87.0f;
}
//
// Now double:
//
template <class T>
inline constexpr T log_max_value(const std::integral_constant<int, 1024>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(std::is_floating_point<T>::value)
{
   return 709.0;
}

template <class T>
inline constexpr T log_min_value(const std::integral_constant<int, 1024>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(std::is_floating_point<T>::value)
{
   return -708.0;
}
//
// 80 and 128-bit long doubles:
//
template <class T>
inline constexpr T log_max_value(const std::integral_constant<int, 16384>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(std::is_floating_point<T>::value)
{
   return 11356.0L;
}

template <class T>
inline constexpr T log_min_value(const std::integral_constant<int, 16384>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(std::is_floating_point<T>::value)
{
   return -11355.0L;
}

template <class T>
inline T log_max_value(const std::integral_constant<int, 0>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T))
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
inline T log_min_value(const std::integral_constant<int, 0>& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T))
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
inline constexpr T epsilon(const std::true_type& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(std::is_floating_point<T>::value)
{
   return std::numeric_limits<T>::epsilon();
}

#if defined(__GNUC__) && ((LDBL_MANT_DIG == 106) || (__LDBL_MANT_DIG__ == 106))
template <>
inline constexpr long double epsilon<long double>(const std::true_type& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(long double)) noexcept(std::is_floating_point<long double>::value)
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
   // static_assert(std::numeric_limits<long double>::digits == 106);
   return 2.4651903288156618919116517665087e-32L;
}
#endif

template <class T>
inline T epsilon(const std::false_type& BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(T))
{
   // Note: don't cache result as precision may vary at runtime:
   BOOST_MATH_STD_USING  // for ADL of std names
   return ldexp(static_cast<T>(1), 1-policies::digits<T, policies::policy<> >());
}

template <class T>
struct log_limit_traits
{
   typedef typename std::conditional<
      (std::numeric_limits<T>::radix == 2) &&
      (std::numeric_limits<T>::max_exponent == 128
         || std::numeric_limits<T>::max_exponent == 1024
         || std::numeric_limits<T>::max_exponent == 16384),
      std::integral_constant<int, (std::numeric_limits<T>::max_exponent > INT_MAX ? INT_MAX : static_cast<int>(std::numeric_limits<T>::max_exponent))>,
      std::integral_constant<int, 0>
   >::type tag_type;
   static constexpr bool value = tag_type::value ? true : false;
   static_assert(::std::numeric_limits<T>::is_specialized || (value == 0), "Type T must be specialized or equal to 0");
};

template <class T, bool b> struct log_limit_noexcept_traits_imp : public log_limit_traits<T> {};
template <class T> struct log_limit_noexcept_traits_imp<T, false> : public std::integral_constant<bool, false> {};

template <class T>
struct log_limit_noexcept_traits : public log_limit_noexcept_traits_imp<T, std::is_floating_point<T>::value> {};

} // namespace detail

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4309)
#endif

template <class T>
inline constexpr T log_max_value(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(detail::log_limit_noexcept_traits<T>::value)
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   return detail::log_max_value<T>(typename detail::log_limit_traits<T>::tag_type());
#else
   BOOST_MATH_ASSERT(::std::numeric_limits<T>::is_specialized);
   BOOST_MATH_STD_USING
   static const T val = log((std::numeric_limits<T>::max)());
   return val;
#endif
}

template <class T>
inline constexpr T log_min_value(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE(T)) noexcept(detail::log_limit_noexcept_traits<T>::value)
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   return detail::log_min_value<T>(typename detail::log_limit_traits<T>::tag_type());
#else
   BOOST_MATH_ASSERT(::std::numeric_limits<T>::is_specialized);
   BOOST_MATH_STD_USING
   static const T val = log((std::numeric_limits<T>::min)());
   return val;
#endif
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

template <class T>
inline constexpr T epsilon(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(T)) noexcept(std::is_floating_point<T>::value)
{
#ifndef BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS
   return detail::epsilon<T>(std::integral_constant<bool, ::std::numeric_limits<T>::is_specialized>());
#else
   return ::std::numeric_limits<T>::is_specialized ?
      detail::epsilon<T>(std::true_type()) :
      detail::epsilon<T>(std::false_type());
#endif
}

namespace detail{

template <class T>
inline constexpr T root_epsilon_imp(const std::integral_constant<int, 24>&) noexcept(std::is_floating_point<T>::value)
{
   return static_cast<T>(0.00034526698300124390839884978618400831996329879769945L);
}

template <class T>
inline constexpr T root_epsilon_imp(const T*, const std::integral_constant<int, 53>&) noexcept(std::is_floating_point<T>::value)
{
   return static_cast<T>(0.1490116119384765625e-7L);
}

template <class T>
inline constexpr T root_epsilon_imp(const T*, const std::integral_constant<int, 64>&) noexcept(std::is_floating_point<T>::value)
{
   return static_cast<T>(0.32927225399135962333569506281281311031656150598474e-9L);
}

template <class T>
inline constexpr T root_epsilon_imp(const T*, const std::integral_constant<int, 113>&) noexcept(std::is_floating_point<T>::value)
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
inline T root_epsilon_imp(const T*, const std::integral_constant<int, 0>&)
{
   BOOST_MATH_STD_USING
   return sqrt(tools::epsilon<T>());
}

template <class T>
inline constexpr T cbrt_epsilon_imp(const std::integral_constant<int, 24>&) noexcept(std::is_floating_point<T>::value)
{
   return static_cast<T>(0.0049215666011518482998719164346805794944150447839903L);
}

template <class T>
inline constexpr T cbrt_epsilon_imp(const T*, const std::integral_constant<int, 53>&) noexcept(std::is_floating_point<T>::value)
{
   return static_cast<T>(6.05545445239333906078989272793696693569753008995e-6L);
}

template <class T>
inline constexpr T cbrt_epsilon_imp(const T*, const std::integral_constant<int, 64>&) noexcept(std::is_floating_point<T>::value)
{
   return static_cast<T>(4.76837158203125e-7L);
}

template <class T>
inline constexpr T cbrt_epsilon_imp(const T*, const std::integral_constant<int, 113>&) noexcept(std::is_floating_point<T>::value)
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
inline T cbrt_epsilon_imp(const T*, const std::integral_constant<int, 0>&)
{
   BOOST_MATH_STD_USING;
   return pow(tools::epsilon<T>(), T(1) / 3);
}

template <class T>
inline constexpr T forth_root_epsilon_imp(const T*, const std::integral_constant<int, 24>&) noexcept(std::is_floating_point<T>::value)
{
   return static_cast<T>(0.018581361171917516667460937040007436176452688944747L);
}

template <class T>
inline constexpr T forth_root_epsilon_imp(const T*, const std::integral_constant<int, 53>&) noexcept(std::is_floating_point<T>::value)
{
   return static_cast<T>(0.0001220703125L);
}

template <class T>
inline constexpr T forth_root_epsilon_imp(const T*, const std::integral_constant<int, 64>&) noexcept(std::is_floating_point<T>::value)
{
   return static_cast<T>(0.18145860519450699870567321328132261891067079047605e-4L);
}

template <class T>
inline constexpr T forth_root_epsilon_imp(const T*, const std::integral_constant<int, 113>&) noexcept(std::is_floating_point<T>::value)
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
inline T forth_root_epsilon_imp(const T*, const std::integral_constant<int, 0>&)
{
   BOOST_MATH_STD_USING
   return sqrt(sqrt(tools::epsilon<T>()));
}

template <class T>
struct root_epsilon_traits
{
   typedef std::integral_constant<int, (::std::numeric_limits<T>::radix == 2) && (::std::numeric_limits<T>::digits != INT_MAX) ? std::numeric_limits<T>::digits : 0> tag_type;
   static constexpr bool has_noexcept = (tag_type::value == 113) || (tag_type::value == 64) || (tag_type::value == 53) || (tag_type::value == 24);
};

}

template <class T>
inline constexpr T root_epsilon() noexcept(std::is_floating_point<T>::value && detail::root_epsilon_traits<T>::has_noexcept)
{
   return detail::root_epsilon_imp(static_cast<T const*>(0), typename detail::root_epsilon_traits<T>::tag_type());
}

template <class T>
inline constexpr T cbrt_epsilon() noexcept(std::is_floating_point<T>::value && detail::root_epsilon_traits<T>::has_noexcept)
{
   return detail::cbrt_epsilon_imp(static_cast<T const*>(0), typename detail::root_epsilon_traits<T>::tag_type());
}

template <class T>
inline constexpr T forth_root_epsilon() noexcept(std::is_floating_point<T>::value && detail::root_epsilon_traits<T>::has_noexcept)
{
   return detail::forth_root_epsilon_imp(static_cast<T const*>(0), typename detail::root_epsilon_traits<T>::tag_type());
}

} // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_PRECISION_INCLUDED


/* precision.hpp
CEYPb3WW31E50QUDu5ztBtgMA5ERGWhbwrYJPxVLysjP3EwbPtuRCZapvv/HEa8xNL2gp0McSqnHm2gcZ4xLZvm0Y/3iOlSQ7MEFRDpGDV4m2CghfpO9ccTR20FOuuRqGC9mToOghZXKAgXqanfqK0reTL/OFEVO4ReWjASto9cTIkZUCsUceOi6cPeQ6bxYlur8qZ0NYkuODouzdNsOlwgoSML54SeZvgNDjkqdgc+tzfu7eRUPRQCc7RxUA6uzckNkgS4ypE9CmQdQT3gBI3QIyF7B0xsn1CNB3WIpWa0M3nFaPL4wxoNFcM1JQLOV9XnU3dbYOJUir1Lo8XJWzOIeW1nYAfX9PvKZg+e6uirFou3p4Garq3U5ZAYDb0NGUK7gtMsVoWNDTXdIlm+dFl8NjRU88FMWRi+vuwUZZsa5TUvXuUzAEeGQ9LC2D2z2yX6lj0nJBqTDe1mkQt7VopflJVoS7c7eq1pIWsKQZnVFb0r8a8lUfMvzYb7dmskbhXeIRT67ntk7iyrboIkwHWxLMW9w1Lp1Vbkf63TG7w+2iTZhSS/sNO3roE/noujtNWVbl0sc9R8vKLSSZtPbUh5wdiQBYmZjaOhjeY32YE8FS56OXdFSy+V8uf4Gbvdu2QOlgCbMkWXR+BtEjXAC9A+uhdKK5Yth/EU849r7e02Z3E+Ds6yf2X+oXZpksXhDpTDB+qNo5OhW3sixqwkROfHMVxESVhO72JZwkKBm6NcCzF24h8+Yl6Mk8k1fyuQqomYWTU+DqkXGxNN4M5d86p2uCfhSVILO5vR+N1RPvVDNz/Sv+ZYfcpzoQeOdCDyXof8sHstX7cyjj4WSJb8XKewB5JzPk6nbOufzlD+nJKL9WFWjMh1dwlnsSyVdORuP65R7IcS1myI1FFCLO1eEKPDhm4s1oStqWxDBtzEb9UiXjsyTEoQHd3enb8sjoKQ0L2g0uO2wEo9HGN8LYvGn2nd6wpRr12P62S4ZXdVIJ2sIS/77AdCjsD+1/MQGdP3NBUi125TG42GNAYlxSKdiOzpbnlocZ99/JVz1EnebOcenkii9atFj6vW3Yva5Ot3pzNQK5XSdgBV+0tQrzrXYUpgEHadnsUV8dnDFTBKvOHhjeKUAIDcJnV+8bWqSw0+S9n+KS0kRpKv8zjs6DCwsiZAhsUMv7bn0m0PwDrAuKox6eF5kEtNWunempiBUSEe93Vd1GODGdTQbHa2ihGv8pRlKiX7/96uQ1Tv3LWW7gD2VjeoaLomJHfB9iiD8Cbve88h33BIqxhrSgKczr6RVa7oWIt4Fp7PD8J/lolED/ASH+MULeISw+63xarALVewKLuw1EhSvhzOY0wYSE98O+2dDZ9zU+ifbzfW9bjlXdPubA0NFDI5IZ2bFGPI/+gS/sDeaxIK76dwj9fUAIouqYTTwM6DU9bgFY9/1ArornILTblXBrw2zR6+bg3Zh/iRMb+VkKDd+7g2zFyw7erx8x5NCR89fBYf/YKaj4qQLJ/L0j3mswrfv8hCC0q6Gy6cjgoVKyBj4zdoawfT0m9C8EukBV02mn5G4bb7TbRZ4g50SoB5fllVYvVq66hGiVDDEGFhTHbmnFZ7BaYigYdsePwo8wQspvZGUeBlwVv5FdEYc+jx+cF7G0ebVocIo3K5BQDT0HiM/7sThsey2R4DnfJq8JIXit6/Q/0dt2N0lwy3wBjQGWonoCdPIwep2Z2gDi8M2vTcGCPLfsTkHPgOxE/g9jg8hyhNUANbsVtighG5f4V4mrd9x9nv+aMCd3F3voJpSYQB70dFgGObKvKPkWOGIVh7wIFfpI5nvFjSPrfY94wLzf8Cpu+CertgHugXZpKuImNZgSutmDbz2YpxWV8KHGwxHyF9bSvZsxKEHUhBK1EvNIkfpNiFW4jFm53fiipQQKCsr/lTc4olI0pM+RR/X3EJNB+rPDK2fyIk9gDLdlBbDONrep8uJPFiBvPU88MN6bG9R8rBKlIkcbVc9N3aIgPZ1Vpi797z6rgQdnkrVION48fJ220WFKELs1YCF38XHSuO5cmgFj1ba6YI4g8VUpIJA23hdYHRnQd/x+ycFpt0cor7Vx+stvatj5QYG4l6K1vh6b+qrc6CACbN0sMDESSKOR3FBW3f/ZpZqdc3nNTPitaenng+gEKduBWzYp29NKp1xP9aCtbugn4sVAxKb13sysFlCK8GrcKkIRvRSspvVjWdU/rkA33Q10Dkf1bQx2UjSFAqaaafakyYIg7pUKiFqQbnyhcuoGbGI2sMZX/EQz2sl7PzyhhFFFwDwJq9zd2fFwo6wyNiaYvfUfUtHBgRaEtzuNAC5ei7eEx3rdiybAtbsFsx/thEAUCcFN0DI1wJ/T9G+hsRMqLXxzZ4Oe2c2jrc7LlINZtPJ05CvR23cfNljEYLIb3xDbnUQW7+MSmPLmww4L3qAPXWMIYKmf2p2fjF2Nd9yWMrgVchWmfpRO4GV1HpdwtuhqdmRauLwcM82vau5bKv/uId6nbZPXfP9l3nDFwjanGMGeDnEWVNDZSeSaEZoEPzzcj0eNtn29GPmF+CJGVQFekChVI2x3EfpjbIIcmh6X70QI+tORz4TU2B653v673CxOKMr3T1AzkyVcnGVoMNaZAptWlPWJ781BY1zbZ+131pm+lk3PVwG0pKybTL+bD/66uoup6o5nYrijLGSSuCmzZOneJT88wHmvNy6ROPRxN9S2lLCRaaQjcv062utxmMIjY9/5O05VqVKescJ2/WaI1omWEmoA4ateYeH0oo0Bp02VEFZ6odx1JRXKNzHrMnvrWp2WIB0BAWSvslnevUFgQh6/vlN5uqSM36YxxmmS6QaSimfO2GTvl5XO1afMe50Bp/fLYnxUerCXqjWgYmQERwnf3TSN1+l7mx73mz+mQ61R3PwVnrZS2b5HLeHCKLbR3qV2a4bVbECrDUn4Zea8Z8l2nE6JlLCP/FiU18ZEBrtllShNrnnto0cKNVmE7QyrEw3f0iptG22gf/OqsuTtv4Tm+IrOYpMizQH89cr0mpDnsEkdux9RArrG0LQy5cDgt3HQJSYgUZIW0Sr0yxuOQ79QTVcTQI1mnCsfB5UlW6pIraZzvlm7vWwBUNk0z/2KgIbNsJurTKk7PIedIgCFhL0/lH4LzEXzp/jdt0GRsTHAbF+iicNRVxLmNXRWA/j7aLLQHv//pLcS3ncmumrnHpVQ32F7LtGCukoFCII3jpwQaVCnw7o/R5XpO+ID+CeEdOH7Tek6YZdkTgSUYq7U1M1O3vE7rndsmCYgkg/GkHdC6E7TQUEexNIvV6veui7hMcvJwkqKnCAFTd0HYdhChCfrSEELLK/5cHsNMTO+kq86/iLbgWBS3vP4fohFRYN2Da45XPbIehHg/OhNjQUyMnFEJxKyqRmkltOCONgwYcvdPIBmKs8dlkNLw7/LoO+mhisMiLxZ0LT2XLg2+ljCSci3gVfm3D+etKKkL7cid/Sy+yzCiSRpLsMTZrYUu0IGThctLESjT1zlqmzMLu6WFy5xhO/+tAvELJd3eWLxld35YpPC4sNiwLr9q7QEGi+obMVhkTZPVJ1Z1X/OHWsBwWvfulnYrxwS39jhszckF9WtRQ9gz4BzeJGGZjLVzeiPmgZImFezFotQn7EuNz4ajQ0DN1axrdCfZoIrTKKzqFKSEE+lfIRMV+Q2IoyfG+B4F1TzGxKMrHs86c9/QLrmmRP93Q7BVMGe05WEvwBXeHB5+C1fG82vQ2Zb0cIV04RMqEO9sbW9+G8PB/wkzS0Y/dGlXaraxiWJmm5CiCfDsfsZ8q5b3Kw8lZSaqdmf+as1N1t8B85fcEMExQwpqK9zJrE4z4A8X8kbPa2iOAzawmLBcqA1A36s8cfLkNtioi9/YkHpoJTqF1a8gL0qaXDhWZ3NsCHEctDrm++QhgLVsDflfErUy2o8Yn3Ilt3cu126/rUsN7k07CiH6H+vT8sRrvRP64icaJAKj6+1BjTasZ+JIp0tnMHSHkd3xkE1q1pN6tpzxzLqzcyJA6d2WIeuGg+3S51+tDT/71xnd8X5q7ttAUWf33wETBNxhQe2XwHzaWNAFCg+ee7tgC750Fz6cA51B4uzd+FIIei5OYeruIWTdRos4+T/WeMnkXYs/yfj81QVWg4gR6vb1WDzH5/WFTkf9SQz2Brpkoq9VIW3x4x6HSdhtubvqGe7SGC35oDuydotpLMx+t9Jm+3M0tRTsRaOk6sa5uc94MI1Lmn/4HjkBUSzzQbNvYOlFkQcqofahg/Bb9XRGDWl4e/EVa58BJeRttV4/kezBBFATJyBoGbI6gupND/BvdLrU7jdha1Yr+fpGhp3eZRdQ8YTcG2F50Mnv8bzTFxmgbf1Oai5jshBmssg3/bFWToe9Sa+x4PXESL1BNXt4CC7pkw/f1G8zxkMvV+4ULwVKvnGcUXFoRuwuvB91zwo3M/G/ydIFwsKBcY7pIz7NDt1k9pssL9aS+ranXDsFfLnss6tP6Q0XvAc9eA1vlZ5ODinc4tMG3zNLVKkThjqaMqcm2EYp2tJLeyRg7099St/FJ0HJN3/JdJYBvWOPLNmAAYQ7q+CnO95iGVfYZgeY9WM26+MDHFwvm2WA41fN6u9cFaxa0WbIbhbbFbdpDy0cD1zDP5ZDwnhIcTxyocGKNulXC2EaVW4zQbW9qyXCT5Yh+gx1AzurBbf7IzzWhEsrSkYt0rvlWwfTu6R3wnQepJI2e2TEtN+tzhqvzzcGOqw6iEPEd7o1XJfJI8Vtv2zL8RbNXF/z6+mE91pFtgnyTHXSPQIvosPhLNq14mJua12QqqA8EsjyCrmojjhqg1rDMXE3Ne4VwBp0q25oQ7icFcWQDtoXJgnMeZrJOZzPEWrP5j2GHAehThNo1I3VyNCdzTfOYOgIeOp6EMu6ZbyxxIgd0Com7nJ4qiysVA7zyqHKPXGk5zVg+nZQ6wFA2O6bKzsgM4LnYM02CYkCOLCj5ewcxkfnq3T6Mx1FFaRFJgJWvkYERioWp77ZY+xYR84sXw0C77H66ZVxdYn7HF7Qlec7HBvHeCe/JPnM5RCIIxPazGfagRPzdbdlQk0Xph/VrWMBT42hGGYlbBW+eE5XITGzkJuskl0seaMhY0lNUV9YbnSmfHha3bSy6rgCzt/MlwnBie/0B62CksBTzSXHsiSn5JZKLlF/AHS/PyEkK+w6boTEf9a9HlclSOaPHyJ12DyXoL2V1lP9lD3MRAQYCxYOtFX4l7tM8UuaxKXx9o9SSaoUymnBjXDlkQ6qVbM5cvjBx0k2sHYgPwAWLA2c88oK/9yv7eQeCGwasOxOcGOkZhX0N3nyw8PQ+fH+fI2clO48P7jvu9sUhV8x5NZ6RIOQRQOn7RqEcJqw2dhGm29E4S+ON6TJqqc4LCbazKZjI5AmlEAQZslgVNUTr2xxS6scs70Ra3qUUnBRDZm5YIF+QGcjBUK5FvRb3jhvs9AauPUerSpSWZrc29v8l5jw9XLCsmdoN7sMR1rtyllroLVYkCh1uoNmvilq6clnF97y6SYX2X1sC+XJ1qZqIKS0LhzZQas7iGCVWfy1pNBNKvYv5MTb2Mf7a4DNzs6QkYZ6tx5/SDkrgBHy+ad7HFyOHe9OEEoeh8gNJUrdUjR1gAVUUUCIOZCDxzfskk8lqF4gIzo8o8w8nYqU+Vk4Mzbq3Zh0btUfihGiO1RQuSmT4j09OOvuLPMBuEVMvTicQ59gacAiRvY8A3ZJ/cN6K1URaKamGT4JBuV689hftcXkRSiN7fc+pFyQU1liJx6/y95hnMoS6TsS9grTuxM4VfZTO4pSjspGgEuqHW2O4Yft8rJZjcV+VTVV6vHGE8hhcQUFxID71tHgS7BmeKghR4h33L2tr5n2hEyLcBDJKYmEVrosU0lnk96CQ0FCgSVLe2CSRgz9qsXqFPOPxa+kZhChU1enc0D5URG5QKiMN5FFGyxtCRoOwZOrF7+KkdmU9G6SD2KF5NGMdY93kVTL81+qlLvbU9m95tiiLk4pODfEbmQgJEz3qV83ivuW1Z/1AkfE+YeHCiuHOXPPeSV+Cf2P3F0tYLAPfihk2tyR8lKZeh9sY0yVxyuvFpWVm5xZmlxeEGHg5jtlZHkL6c/xuqHyqcOSob3mLP+1ZwcPKzHk4lda9s50cvDnC3myuFFWCuVEJGvqbAjF5TkfFuq2bX/dc3/lFNNZwi65sM/xFLlq+GdLpValE9LewyNiSGADeBNXYlrOmyM7NPSFw1ienPFiPrnS0sIIrAmazrp4p9CaOvOnP+wiBbROoOqMM1Cxum4qwSPzIQ1gFTAOPv8dsOoQdL25TUOR5mb05zcMOmve9jvKXvp2m7pjo5G6XktRHgO91S9s8QAeMrTe4T1wc8Cv3g5TGuVyabIgoj+3N09t8HA8ewUvmLgcPyPbbXbXODV2FCvytNKqwHKWSc12+QR8rvKx1leJbqSco/PzudXitjmwNA5RacoQJn0kNptcL+Dc/xzypeQCD66TxMQjAbVMadhektDewaEZS5UMc4XBULPu5aRRkgmNyubx5KiyV7Z1Ix7k3rgCTWCsOloRCJAdAr1US15iPH9SI5GNW1CxI4+md42ANQ+tygXHYd6raqp3DM8ipr68KuoPTLIZACoJFrkXHyQxcFf4pzMnhzBOYCSCTXOgD9zI96dpDZ/8KQwEXc0dLg/bOXGJ/NsJn2Ehsd4EA3wgOSjU185fPB3rUhuDphKO2gRe2+4yzpkq6sfJxjLhyuGUCgoHz+uzMivzq/M6G9V2+5+ErgXozo0Z0JYtbBnDmu/aBHK6brMeA2+DbH2dHwi2gEb/Wuu/z1npBqZ84LA5Nwm7lfAYC2CdmgHuZ+f3uYbgE/APpCNmiY8LOso1zdWPkHDDXRfaZeoAdQU1Q9QX1blCug++HxzwHlOzsuorwxbYWKMBT3gn1NceVk+qdpcizr2iq10FxsgwttVeafzr8F6lCtCHFBHthg0BZg3QY6ax6LeewL4s+gbw/WsnZewrZV1QfB0B3bkNFHVMjNXQjvb2G8yKQLAk02aHOcZR3nxWx2YSp2cECoNGTpuiErvNt7hiS0HGMi52ugo1oq9030sI5M7eebzGVCA87K68COryITLlEbpWYA7PC5NpvETDtikeFnGvp3QXhAOF75kyFlol0HMCpJ7gtOtBH6VJn6YI+PwYkQ1vLj+Oq76wjCShnHxF8FJWjropVpE7Bz14/iG96sfpuzocMxklkxGsDgcEBm0dVJ9fOu7iC5fx8n8JhN0iHQtM7LgOPCIAX3lOdH48KYS2UvRTdGHVFWP4RRLKVO+BNX2Z/QiQm7dZb0V7N21z2fyWhsfSRL2f7jxbCCLVVKLiZAvcD9T4BGZSiZNq9lxJtckcA8B9lrGFuKChGealU7Dfbwtz6c+ZzzILfW7rtI2iHhKXAczP3Yg+XJJeeUWzU4VGVXnqa0dJ5igKNxwhShHJP5hwPD65VesmsKIJzjsfEtUqbZcaZ6zn2JkYKFeMdn4DiNkN8fSb4/D0qlcu+kfjHQ526hLufR5pkzxuI5HCmWikNLp49rxf9tTbZSx2W5CxAsQllVSDMSMclny76Q
*/