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

#include <boost/math/special_functions/round.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/special_functions/modf.hpp>
#include <boost/math/tools/big_constant.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/special_functions/asinh.hpp>
#include <boost/math/special_functions/atanh.hpp>
#if defined(__SGI_STL_PORT)
#  include <boost/math/tools/real_cast.hpp>
#endif
#include <ostream>
#include <istream>
#include <limits>
#include <cmath>
#include <cstdint>

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
   real_concept(wchar_t c) : m_value(c){}
   real_concept(unsigned char c) : m_value(c){}
   real_concept(signed char c) : m_value(c){}
   real_concept(unsigned short c) : m_value(c){}
   real_concept(short c) : m_value(c){}
   real_concept(unsigned int c) : m_value(c){}
   real_concept(int c) : m_value(c){}
   real_concept(unsigned long c) : m_value(c){}
   real_concept(long c) : m_value(c){}
   real_concept(unsigned long long c) : m_value(static_cast<real_concept_base_type>(c)){}
   real_concept(long long c) : m_value(static_cast<real_concept_base_type>(c)){}
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
   real_concept& operator=(wchar_t c) { m_value = c; return *this; }
   real_concept& operator=(short c) { m_value = c; return *this; }
   real_concept& operator=(unsigned short c) { m_value = c; return *this; }
   real_concept& operator=(int c) { m_value = c; return *this; }
   real_concept& operator=(unsigned int c) { m_value = c; return *this; }
   real_concept& operator=(long c) { m_value = c; return *this; }
   real_concept& operator=(unsigned long c) { m_value = c; return *this; }
   real_concept& operator=(long long c) { m_value = static_cast<real_concept_base_type>(c); return *this; }
   real_concept& operator=(unsigned long long c) { m_value = static_cast<real_concept_base_type>(c); return *this; }
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

template <class Policy>
inline long long llround(const concepts::real_concept& v, const Policy& pol)
{ return boost::math::llround(v.value(), pol); }
inline long long llround(const concepts::real_concept& v)
{ return boost::math::llround(v.value(), policies::policy<>()); }

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

template <class Policy>
inline long long lltrunc(const concepts::real_concept& v, const Policy& pol)
{ return boost::math::lltrunc(v.value(), pol); }
inline long long lltrunc(const concepts::real_concept& v)
{ return boost::math::lltrunc(v.value(), policies::policy<>()); }

// Streaming:
template <class charT, class traits>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& os, const real_concept& a)
{
   return os << a.value();
}
template <class charT, class traits>
inline std::basic_istream<charT, traits>& operator>>(std::basic_istream<charT, traits>& is, real_concept& a)
{
   real_concept_base_type v;
   is >> v;
   a = v;
   return is;
}

} // namespace concepts

namespace tools
{

template <>
inline concepts::real_concept make_big_value<concepts::real_concept>(boost::math::tools::largest_float val, const char* , std::false_type const&, std::false_type const&)
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
inline constexpr int digits<concepts::real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::real_concept)) noexcept
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
} // namespace math
} // namespace boost

#endif // BOOST_MATH_REAL_CONCEPT_HPP



/* real_concept.hpp
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
*/