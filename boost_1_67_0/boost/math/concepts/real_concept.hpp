//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Test real concept.

// real_concept is an archetype for User defined Real types.

// This file defines the features, constructors, operators, functions...
// that are essential to use mathematical and statistical functions.
// The template typename "RealType" is used where this type
// (as well as the normal built-in types, float, double & long double)
// can be used.
// That this is the minimum set is confirmed by use as a type
// in tests of all functions & distributions, for example:
//   test_spots(0.F); & test_spots(0.);  for float and double, but also
//   test_spots(boost::math::concepts::real_concept(0.));
// NTL quad_float type is an example of a type meeting the requirements,
// but note minor additions are needed - see ntl.diff and documentation
// "Using With NTL - a High-Precision Floating-Point Library".

#ifndef BOOST_MATH_REAL_CONCEPT_HPP
#define BOOST_MATH_REAL_CONCEPT_HPP

#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/special_functions/modf.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/special_functions/asinh.hpp>
#include <boost/math/special_functions/atanh.hpp>
#if defined(__SGI_STL_PORT)
#  include <boost/math/tools/real_cast.hpp>
#endif
#include <ostream>
#include <istream>
#include <boost/config/no_tr1/cmath.hpp>
#include <math.h> // fmodl

#if defined(__SGI_STL_PORT) || defined(_RWSTD_VER) || defined(__LIBCOMO__)
#  include <cstdio>
#endif

namespace boost{ namespace math{

namespace concepts
{

#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
   typedef double real_concept_base_type;
#else
   typedef long double real_concept_base_type;
#endif

class real_concept
{
public:
   // Constructors:
   real_concept() : m_value(0){}
   real_concept(char c) : m_value(c){}
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
   real_concept(wchar_t c) : m_value(c){}
#endif
   real_concept(unsigned char c) : m_value(c){}
   real_concept(signed char c) : m_value(c){}
   real_concept(unsigned short c) : m_value(c){}
   real_concept(short c) : m_value(c){}
   real_concept(unsigned int c) : m_value(c){}
   real_concept(int c) : m_value(c){}
   real_concept(unsigned long c) : m_value(c){}
   real_concept(long c) : m_value(c){}
#if defined(__DECCXX) || defined(__SUNPRO_CC)
   real_concept(unsigned long long c) : m_value(static_cast<real_concept_base_type>(c)){}
   real_concept(long long c) : m_value(static_cast<real_concept_base_type>(c)){}
#elif defined(BOOST_HAS_LONG_LONG)
   real_concept(boost::ulong_long_type c) : m_value(static_cast<real_concept_base_type>(c)){}
   real_concept(boost::long_long_type c) : m_value(static_cast<real_concept_base_type>(c)){}
#elif defined(BOOST_HAS_MS_INT64)
   real_concept(unsigned __int64 c) : m_value(static_cast<real_concept_base_type>(c)){}
   real_concept(__int64 c) : m_value(static_cast<real_concept_base_type>(c)){}
#endif
   real_concept(float c) : m_value(c){}
   real_concept(double c) : m_value(c){}
   real_concept(long double c) : m_value(c){}
#ifdef BOOST_MATH_USE_FLOAT128
   real_concept(BOOST_MATH_FLOAT128_TYPE c) : m_value(c){}
#endif

   // Assignment:
   real_concept& operator=(char c) { m_value = c; return *this; }
   real_concept& operator=(unsigned char c) { m_value = c; return *this; }
   real_concept& operator=(signed char c) { m_value = c; return *this; }
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
   real_concept& operator=(wchar_t c) { m_value = c; return *this; }
#endif
   real_concept& operator=(short c) { m_value = c; return *this; }
   real_concept& operator=(unsigned short c) { m_value = c; return *this; }
   real_concept& operator=(int c) { m_value = c; return *this; }
   real_concept& operator=(unsigned int c) { m_value = c; return *this; }
   real_concept& operator=(long c) { m_value = c; return *this; }
   real_concept& operator=(unsigned long c) { m_value = c; return *this; }
#ifdef BOOST_HAS_LONG_LONG
   real_concept& operator=(boost::long_long_type c) { m_value = static_cast<real_concept_base_type>(c); return *this; }
   real_concept& operator=(boost::ulong_long_type c) { m_value = static_cast<real_concept_base_type>(c); return *this; }
#endif
   real_concept& operator=(float c) { m_value = c; return *this; }
   real_concept& operator=(double c) { m_value = c; return *this; }
   real_concept& operator=(long double c) { m_value = c; return *this; }

   // Access:
   real_concept_base_type value()const{ return m_value; }

   // Member arithmetic:
   real_concept& operator+=(const real_concept& other)
   { m_value += other.value(); return *this; }
   real_concept& operator-=(const real_concept& other)
   { m_value -= other.value(); return *this; }
   real_concept& operator*=(const real_concept& other)
   { m_value *= other.value(); return *this; }
   real_concept& operator/=(const real_concept& other)
   { m_value /= other.value(); return *this; }
   real_concept operator-()const
   { return -m_value; }
   real_concept const& operator+()const
   { return *this; }
   real_concept& operator++()
   { ++m_value;  return *this; }
   real_concept& operator--()
   { --m_value;  return *this; }

private:
   real_concept_base_type m_value;
};

// Non-member arithmetic:
inline real_concept operator+(const real_concept& a, const real_concept& b)
{
   real_concept result(a);
   result += b;
   return result;
}
inline real_concept operator-(const real_concept& a, const real_concept& b)
{
   real_concept result(a);
   result -= b;
   return result;
}
inline real_concept operator*(const real_concept& a, const real_concept& b)
{
   real_concept result(a);
   result *= b;
   return result;
}
inline real_concept operator/(const real_concept& a, const real_concept& b)
{
   real_concept result(a);
   result /= b;
   return result;
}

// Comparison:
inline bool operator == (const real_concept& a, const real_concept& b)
{ return a.value() == b.value(); }
inline bool operator != (const real_concept& a, const real_concept& b)
{ return a.value() != b.value();}
inline bool operator < (const real_concept& a, const real_concept& b)
{ return a.value() < b.value(); }
inline bool operator <= (const real_concept& a, const real_concept& b)
{ return a.value() <= b.value(); }
inline bool operator > (const real_concept& a, const real_concept& b)
{ return a.value() > b.value(); }
inline bool operator >= (const real_concept& a, const real_concept& b)
{ return a.value() >= b.value(); }

// Non-member functions:
inline real_concept acos(real_concept a)
{ return std::acos(a.value()); }
inline real_concept cos(real_concept a)
{ return std::cos(a.value()); }
inline real_concept asin(real_concept a)
{ return std::asin(a.value()); }
inline real_concept atan(real_concept a)
{ return std::atan(a.value()); }
inline real_concept atan2(real_concept a, real_concept b)
{ return std::atan2(a.value(), b.value()); }
inline real_concept ceil(real_concept a)
{ return std::ceil(a.value()); }
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
// I've seen std::fmod(long double) crash on some platforms
// so use fmodl instead:
#ifdef _WIN32_WCE
//
// Ugly workaround for macro fmodl:
//
inline long double call_fmodl(long double a, long double b)
{  return fmodl(a, b); }
inline real_concept fmod(real_concept a, real_concept b)
{ return call_fmodl(a.value(), b.value()); }
#else
inline real_concept fmod(real_concept a, real_concept b)
{ return fmodl(a.value(), b.value()); }
#endif
#endif
inline real_concept cosh(real_concept a)
{ return std::cosh(a.value()); }
inline real_concept exp(real_concept a)
{ return std::exp(a.value()); }
inline real_concept fabs(real_concept a)
{ return std::fabs(a.value()); }
inline real_concept abs(real_concept a)
{ return std::abs(a.value()); }
inline real_concept floor(real_concept a)
{ return std::floor(a.value()); }
inline real_concept modf(real_concept a, real_concept* ipart)
{
#ifdef __MINGW32__
   real_concept_base_type ip;
   real_concept_base_type result = boost::math::modf(a.value(), &ip);
   *ipart = ip;
   return result;
#else
   real_concept_base_type ip;
   real_concept_base_type result = std::modf(a.value(), &ip);
   *ipart = ip;
   return result;
#endif
}
inline real_concept frexp(real_concept a, int* expon)
{ return std::frexp(a.value(), expon); }
inline real_concept ldexp(real_concept a, int expon)
{ return std::ldexp(a.value(), expon); }
inline real_concept log(real_concept a)
{ return std::log(a.value()); }
inline real_concept log10(real_concept a)
{ return std::log10(a.value()); }
inline real_concept tan(real_concept a)
{ return std::tan(a.value()); }
inline real_concept pow(real_concept a, real_concept b)
{ return std::pow(a.value(), b.value()); }
#if !defined(__SUNPRO_CC)
inline real_concept pow(real_concept a, int b)
{ return std::pow(a.value(), b); }
#else
inline real_concept pow(real_concept a, int b)
{ return std::pow(a.value(), static_cast<real_concept_base_type>(b)); }
#endif
inline real_concept sin(real_concept a)
{ return std::sin(a.value()); }
inline real_concept sinh(real_concept a)
{ return std::sinh(a.value()); }
inline real_concept sqrt(real_concept a)
{ return std::sqrt(a.value()); }
inline real_concept tanh(real_concept a)
{ return std::tanh(a.value()); }

//
// C++11 ism's
// Note that these must not actually call the std:: versions as that precludes using this
// header to test in C++03 mode, call the Boost versions instead:
//
inline boost::math::concepts::real_concept asinh(boost::math::concepts::real_concept a)
{
   return boost::math::asinh(a.value(), boost::math::policies::make_policy(boost::math::policies::overflow_error<boost::math::policies::ignore_error>()));
}
inline boost::math::concepts::real_concept acosh(boost::math::concepts::real_concept a)
{
   return boost::math::acosh(a.value(), boost::math::policies::make_policy(boost::math::policies::overflow_error<boost::math::policies::ignore_error>()));
}
inline boost::math::concepts::real_concept atanh(boost::math::concepts::real_concept a)
{
   return boost::math::atanh(a.value(), boost::math::policies::make_policy(boost::math::policies::overflow_error<boost::math::policies::ignore_error>()));
}

//
// Conversion and truncation routines:
//
template <class Policy>
inline int iround(const concepts::real_concept& v, const Policy& pol)
{ return boost::math::iround(v.value(), pol); }
inline int iround(const concepts::real_concept& v)
{ return boost::math::iround(v.value(), policies::policy<>()); }
template <class Policy>
inline long lround(const concepts::real_concept& v, const Policy& pol)
{ return boost::math::lround(v.value(), pol); }
inline long lround(const concepts::real_concept& v)
{ return boost::math::lround(v.value(), policies::policy<>()); }

#ifdef BOOST_HAS_LONG_LONG
template <class Policy>
inline boost::long_long_type llround(const concepts::real_concept& v, const Policy& pol)
{ return boost::math::llround(v.value(), pol); }
inline boost::long_long_type llround(const concepts::real_concept& v)
{ return boost::math::llround(v.value(), policies::policy<>()); }
#endif

template <class Policy>
inline int itrunc(const concepts::real_concept& v, const Policy& pol)
{ return boost::math::itrunc(v.value(), pol); }
inline int itrunc(const concepts::real_concept& v)
{ return boost::math::itrunc(v.value(), policies::policy<>()); }
template <class Policy>
inline long ltrunc(const concepts::real_concept& v, const Policy& pol)
{ return boost::math::ltrunc(v.value(), pol); }
inline long ltrunc(const concepts::real_concept& v)
{ return boost::math::ltrunc(v.value(), policies::policy<>()); }

#ifdef BOOST_HAS_LONG_LONG
template <class Policy>
inline boost::long_long_type lltrunc(const concepts::real_concept& v, const Policy& pol)
{ return boost::math::lltrunc(v.value(), pol); }
inline boost::long_long_type lltrunc(const concepts::real_concept& v)
{ return boost::math::lltrunc(v.value(), policies::policy<>()); }
#endif

// Streaming:
template <class charT, class traits>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& os, const real_concept& a)
{
   return os << a.value();
}
template <class charT, class traits>
inline std::basic_istream<charT, traits>& operator>>(std::basic_istream<charT, traits>& is, real_concept& a)
{
#if defined(BOOST_MSVC) && defined(__SGI_STL_PORT)
   //
   // STLPort 5.1.4 has a problem reading long doubles from strings,
   // see http://sourceforge.net/tracker/index.php?func=detail&aid=1811043&group_id=146814&atid=766244
   //
   double v;
   is >> v;
   a = v;
   return is;
#elif defined(__SGI_STL_PORT) || defined(_RWSTD_VER) || defined(__LIBCOMO__) || defined(_LIBCPP_VERSION)
   std::string s;
   real_concept_base_type d;
   is >> s;
   std::sscanf(s.c_str(), "%Lf", &d);
   a = d;
   return is;
#else
   real_concept_base_type v;
   is >> v;
   a = v;
   return is;
#endif
}

} // namespace concepts

namespace tools
{

template <>
inline concepts::real_concept make_big_value<concepts::real_concept>(boost::math::tools::largest_float val, const char* , boost::false_type const&, boost::false_type const&)
{
   return val;  // Can't use lexical_cast here, sometimes it fails....
}

template <>
inline concepts::real_concept max_value<concepts::real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::real_concept))
{
   return max_value<concepts::real_concept_base_type>();
}

template <>
inline concepts::real_concept min_value<concepts::real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::real_concept))
{
   return min_value<concepts::real_concept_base_type>();
}

template <>
inline concepts::real_concept log_max_value<concepts::real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::real_concept))
{
   return log_max_value<concepts::real_concept_base_type>();
}

template <>
inline concepts::real_concept log_min_value<concepts::real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::real_concept))
{
   return log_min_value<concepts::real_concept_base_type>();
}

template <>
inline concepts::real_concept epsilon<concepts::real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::real_concept))
{
#ifdef __SUNPRO_CC
   return std::numeric_limits<concepts::real_concept_base_type>::epsilon();
#else
   return tools::epsilon<concepts::real_concept_base_type>();
#endif
}

template <>
inline BOOST_MATH_CONSTEXPR int digits<concepts::real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::real_concept)) BOOST_NOEXCEPT
{
   // Assume number of significand bits is same as real_concept_base_type,
   // unless std::numeric_limits<T>::is_specialized to provide digits.
   return tools::digits<concepts::real_concept_base_type>();
   // Note that if numeric_limits real concept is NOT specialized to provide digits10
   // (or max_digits10) then the default precision of 6 decimal digits will be used
   // by Boost test (giving misleading error messages like
   // "difference between {9.79796} and {9.79796} exceeds 5.42101e-19%"
   // and by Boost lexical cast and serialization causing loss of accuracy.
}

} // namespace tools
/*
namespace policies {
   namespace detail {

      template <class T>
      inline concepts::real_concept raise_rounding_error(
         const char*,
         const char*,
         const T& val,
         const concepts::real_concept&,
         const  ::boost::math::policies::rounding_error< ::boost::math::policies::errno_on_error>&) BOOST_MATH_NOEXCEPT(T)
      {
         errno = ERANGE;
         // This may or may not do the right thing, but the user asked for the error
         // to be silent so here we go anyway:
         return  val > 0 ? boost::math::tools::max_value<concepts::real_concept>() : -boost::math::tools::max_value<concepts::real_concept>();
      }

   }
}*/

#if defined(__SGI_STL_PORT) || defined(BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS)
//
// We shouldn't really need these type casts any more, but there are some
// STLport iostream bugs we work around by using them....
//
namespace tools
{
// real_cast converts from T to integer and narrower floating-point types.

// Convert from T to integer types.

template <>
inline unsigned int real_cast<unsigned int, concepts::real_concept>(concepts::real_concept r)
{
   return static_cast<unsigned int>(r.value());
}

template <>
inline int real_cast<int, concepts::real_concept>(concepts::real_concept r)
{
   return static_cast<int>(r.value());
}

template <>
inline long real_cast<long, concepts::real_concept>(concepts::real_concept r)
{
   return static_cast<long>(r.value());
}

// Converts from T to narrower floating-point types, float, double & long double.

template <>
inline float real_cast<float, concepts::real_concept>(concepts::real_concept r)
{
   return static_cast<float>(r.value());
}
template <>
inline double real_cast<double, concepts::real_concept>(concepts::real_concept r)
{
   return static_cast<double>(r.value());
}
template <>
inline long double real_cast<long double, concepts::real_concept>(concepts::real_concept r)
{
   return r.value();
}

} // STLPort

#endif

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
//
// For some strange reason ADL sometimes fails to find the
// correct overloads, unless we bring these declarations into scope:
//
using concepts::itrunc;
using concepts::iround;

#endif

} // namespace math
} // namespace boost

#endif // BOOST_MATH_REAL_CONCEPT_HPP



/* real_concept.hpp
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
*/