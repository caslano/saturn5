//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// std_real_concept is an archetype for built-in Real types.

// The main purpose in providing this type is to verify
// that std lib functions are found via a using declaration
// bringing those functions into the current scope, and not
// just because they happen to be in global scope.
//
// If ::pow is found rather than std::pow say, then the code
// will silently compile, but truncation of long doubles to
// double will cause a significant loss of precision.
// A template instantiated with std_real_concept will *only*
// compile if it std::whatever is in scope.

#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/special_functions/math_fwd.hpp>

#include <ostream>
#include <istream>
#include <boost/config/no_tr1/cmath.hpp>
#include <math.h> // fmodl

#ifndef BOOST_MATH_STD_REAL_CONCEPT_HPP
#define BOOST_MATH_STD_REAL_CONCEPT_HPP

namespace boost{ namespace math{

namespace concepts
{

#ifdef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
   typedef double std_real_concept_base_type;
#else
   typedef long double std_real_concept_base_type;
#endif

class std_real_concept
{
public:
   // Constructors:
   std_real_concept() : m_value(0){}
   std_real_concept(char c) : m_value(c){}
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
   std_real_concept(wchar_t c) : m_value(c){}
#endif
   std_real_concept(unsigned char c) : m_value(c){}
   std_real_concept(signed char c) : m_value(c){}
   std_real_concept(unsigned short c) : m_value(c){}
   std_real_concept(short c) : m_value(c){}
   std_real_concept(unsigned int c) : m_value(c){}
   std_real_concept(int c) : m_value(c){}
   std_real_concept(unsigned long c) : m_value(c){}
   std_real_concept(long c) : m_value(c){}
#if defined(__DECCXX) || defined(__SUNPRO_CC)
   std_real_concept(unsigned long long c) : m_value(static_cast<std_real_concept_base_type>(c)){}
   std_real_concept(long long c) : m_value(static_cast<std_real_concept_base_type>(c)){}
#elif defined(BOOST_HAS_LONG_LONG)
   std_real_concept(boost::ulong_long_type c) : m_value(static_cast<std_real_concept_base_type>(c)){}
   std_real_concept(boost::long_long_type c) : m_value(static_cast<std_real_concept_base_type>(c)){}
#endif
   std_real_concept(float c) : m_value(c){}
   std_real_concept(double c) : m_value(c){}
   std_real_concept(long double c) : m_value(c){}
#ifdef BOOST_MATH_USE_FLOAT128
   std_real_concept(BOOST_MATH_FLOAT128_TYPE c) : m_value(c){}
#endif

   // Assignment:
   std_real_concept& operator=(char c) { m_value = c; return *this; }
   std_real_concept& operator=(unsigned char c) { m_value = c; return *this; }
   std_real_concept& operator=(signed char c) { m_value = c; return *this; }
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
   std_real_concept& operator=(wchar_t c) { m_value = c; return *this; }
#endif
   std_real_concept& operator=(short c) { m_value = c; return *this; }
   std_real_concept& operator=(unsigned short c) { m_value = c; return *this; }
   std_real_concept& operator=(int c) { m_value = c; return *this; }
   std_real_concept& operator=(unsigned int c) { m_value = c; return *this; }
   std_real_concept& operator=(long c) { m_value = c; return *this; }
   std_real_concept& operator=(unsigned long c) { m_value = c; return *this; }
#if defined(__DECCXX) || defined(__SUNPRO_CC)
   std_real_concept& operator=(unsigned long long c) { m_value = static_cast<std_real_concept_base_type>(c); return *this; }
   std_real_concept& operator=(long long c) { m_value = static_cast<std_real_concept_base_type>(c); return *this; }
#elif defined(BOOST_HAS_LONG_LONG)
   std_real_concept& operator=(boost::long_long_type c) { m_value = static_cast<std_real_concept_base_type>(c); return *this; }
   std_real_concept& operator=(boost::ulong_long_type c) { m_value = static_cast<std_real_concept_base_type>(c); return *this; }
#endif
   std_real_concept& operator=(float c) { m_value = c; return *this; }
   std_real_concept& operator=(double c) { m_value = c; return *this; }
   std_real_concept& operator=(long double c) { m_value = c; return *this; }

   // Access:
   std_real_concept_base_type value()const{ return m_value; }

   // Member arithmetic:
   std_real_concept& operator+=(const std_real_concept& other)
   { m_value += other.value(); return *this; }
   std_real_concept& operator-=(const std_real_concept& other)
   { m_value -= other.value(); return *this; }
   std_real_concept& operator*=(const std_real_concept& other)
   { m_value *= other.value(); return *this; }
   std_real_concept& operator/=(const std_real_concept& other)
   { m_value /= other.value(); return *this; }
   std_real_concept operator-()const
   { return -m_value; }
   std_real_concept const& operator+()const
   { return *this; }

private:
   std_real_concept_base_type m_value;
};

// Non-member arithmetic:
inline std_real_concept operator+(const std_real_concept& a, const std_real_concept& b)
{
   std_real_concept result(a);
   result += b;
   return result;
}
inline std_real_concept operator-(const std_real_concept& a, const std_real_concept& b)
{
   std_real_concept result(a);
   result -= b;
   return result;
}
inline std_real_concept operator*(const std_real_concept& a, const std_real_concept& b)
{
   std_real_concept result(a);
   result *= b;
   return result;
}
inline std_real_concept operator/(const std_real_concept& a, const std_real_concept& b)
{
   std_real_concept result(a);
   result /= b;
   return result;
}

// Comparison:
inline bool operator == (const std_real_concept& a, const std_real_concept& b)
{ return a.value() == b.value(); }
inline bool operator != (const std_real_concept& a, const std_real_concept& b)
{ return a.value() != b.value();}
inline bool operator < (const std_real_concept& a, const std_real_concept& b)
{ return a.value() < b.value(); }
inline bool operator <= (const std_real_concept& a, const std_real_concept& b)
{ return a.value() <= b.value(); }
inline bool operator > (const std_real_concept& a, const std_real_concept& b)
{ return a.value() > b.value(); }
inline bool operator >= (const std_real_concept& a, const std_real_concept& b)
{ return a.value() >= b.value(); }

} // namespace concepts
} // namespace math
} // namespace boost

namespace std{

// Non-member functions:
inline boost::math::concepts::std_real_concept acos(boost::math::concepts::std_real_concept a)
{ return std::acos(a.value()); }
inline boost::math::concepts::std_real_concept cos(boost::math::concepts::std_real_concept a)
{ return std::cos(a.value()); }
inline boost::math::concepts::std_real_concept asin(boost::math::concepts::std_real_concept a)
{ return std::asin(a.value()); }
inline boost::math::concepts::std_real_concept atan(boost::math::concepts::std_real_concept a)
{ return std::atan(a.value()); }
inline boost::math::concepts::std_real_concept atan2(boost::math::concepts::std_real_concept a, boost::math::concepts::std_real_concept b)
{ return std::atan2(a.value(), b.value()); }
inline boost::math::concepts::std_real_concept ceil(boost::math::concepts::std_real_concept a)
{ return std::ceil(a.value()); }
#ifndef BOOST_MATH_NO_LONG_DOUBLE_MATH_FUNCTIONS
inline boost::math::concepts::std_real_concept fmod(boost::math::concepts::std_real_concept a, boost::math::concepts::std_real_concept b)
{ return fmodl(a.value(), b.value()); }
#else
inline boost::math::concepts::std_real_concept fmod(boost::math::concepts::std_real_concept a, boost::math::concepts::std_real_concept b)
{ return std::fmod(a.value(), b.value()); }
#endif
inline boost::math::concepts::std_real_concept cosh(boost::math::concepts::std_real_concept a)
{ return std::cosh(a.value()); }
inline boost::math::concepts::std_real_concept exp(boost::math::concepts::std_real_concept a)
{ return std::exp(a.value()); }
inline boost::math::concepts::std_real_concept fabs(boost::math::concepts::std_real_concept a)
{ return std::fabs(a.value()); }
inline boost::math::concepts::std_real_concept abs(boost::math::concepts::std_real_concept a)
{ return std::abs(a.value()); }
inline boost::math::concepts::std_real_concept floor(boost::math::concepts::std_real_concept a)
{ return std::floor(a.value()); }
inline boost::math::concepts::std_real_concept modf(boost::math::concepts::std_real_concept a, boost::math::concepts::std_real_concept* ipart)
{
   boost::math::concepts::std_real_concept_base_type ip;
   boost::math::concepts::std_real_concept_base_type result = std::modf(a.value(), &ip);
   *ipart = ip;
   return result;
}
inline boost::math::concepts::std_real_concept frexp(boost::math::concepts::std_real_concept a, int* expon)
{ return std::frexp(a.value(), expon); }
inline boost::math::concepts::std_real_concept ldexp(boost::math::concepts::std_real_concept a, int expon)
{ return std::ldexp(a.value(), expon); }
inline boost::math::concepts::std_real_concept log(boost::math::concepts::std_real_concept a)
{ return std::log(a.value()); }
inline boost::math::concepts::std_real_concept log10(boost::math::concepts::std_real_concept a)
{ return std::log10(a.value()); }
inline boost::math::concepts::std_real_concept tan(boost::math::concepts::std_real_concept a)
{ return std::tan(a.value()); }
inline boost::math::concepts::std_real_concept pow(boost::math::concepts::std_real_concept a, boost::math::concepts::std_real_concept b)
{ return std::pow(a.value(), b.value()); }
#if !defined(__SUNPRO_CC)
inline boost::math::concepts::std_real_concept pow(boost::math::concepts::std_real_concept a, int b)
{ return std::pow(a.value(), b); }
#else
inline boost::math::concepts::std_real_concept pow(boost::math::concepts::std_real_concept a, int b)
{ return std::pow(a.value(), static_cast<long double>(b)); }
#endif
inline boost::math::concepts::std_real_concept sin(boost::math::concepts::std_real_concept a)
{ return std::sin(a.value()); }
inline boost::math::concepts::std_real_concept sinh(boost::math::concepts::std_real_concept a)
{ return std::sinh(a.value()); }
inline boost::math::concepts::std_real_concept sqrt(boost::math::concepts::std_real_concept a)
{ return std::sqrt(a.value()); }
inline boost::math::concepts::std_real_concept tanh(boost::math::concepts::std_real_concept a)
{ return std::tanh(a.value()); }
inline boost::math::concepts::std_real_concept (nextafter)(boost::math::concepts::std_real_concept a, boost::math::concepts::std_real_concept b)
{ return (boost::math::nextafter)(a, b); }
//
// C++11 ism's
// Note that these must not actually call the std:: versions as that precludes using this
// header to test in C++03 mode, call the Boost versions instead:
//
inline boost::math::concepts::std_real_concept asinh(boost::math::concepts::std_real_concept a)
{ return boost::math::asinh(a.value(), boost::math::policies::make_policy(boost::math::policies::overflow_error<boost::math::policies::ignore_error>())); }
inline boost::math::concepts::std_real_concept acosh(boost::math::concepts::std_real_concept a)
{ return boost::math::acosh(a.value(), boost::math::policies::make_policy(boost::math::policies::overflow_error<boost::math::policies::ignore_error>())); }
inline boost::math::concepts::std_real_concept atanh(boost::math::concepts::std_real_concept a)
{ return boost::math::atanh(a.value(), boost::math::policies::make_policy(boost::math::policies::overflow_error<boost::math::policies::ignore_error>())); }
inline bool (isfinite)(boost::math::concepts::std_real_concept a)
{
   return (boost::math::isfinite)(a.value());
}


} // namespace std

#include <boost/math/special_functions/round.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/special_functions/modf.hpp>
#include <boost/math/tools/precision.hpp>

namespace boost{ namespace math{ namespace concepts{

//
// Conversion and truncation routines:
//
template <class Policy>
inline int iround(const concepts::std_real_concept& v, const Policy& pol)
{
   return boost::math::iround(v.value(), pol);
}
inline int iround(const concepts::std_real_concept& v)
{
   return boost::math::iround(v.value(), policies::policy<>());
}

template <class Policy>
inline long lround(const concepts::std_real_concept& v, const Policy& pol)
{
   return boost::math::lround(v.value(), pol);
}
inline long lround(const concepts::std_real_concept& v)
{
   return boost::math::lround(v.value(), policies::policy<>());
}

#ifdef BOOST_HAS_LONG_LONG

template <class Policy>
inline boost::long_long_type llround(const concepts::std_real_concept& v, const Policy& pol)
{
   return boost::math::llround(v.value(), pol);
}
inline boost::long_long_type llround(const concepts::std_real_concept& v)
{
   return boost::math::llround(v.value(), policies::policy<>());
}

#endif

template <class Policy>
inline int itrunc(const concepts::std_real_concept& v, const Policy& pol)
{
   return boost::math::itrunc(v.value(), pol);
}
inline int itrunc(const concepts::std_real_concept& v)
{
   return boost::math::itrunc(v.value(), policies::policy<>());
}

template <class Policy>
inline long ltrunc(const concepts::std_real_concept& v, const Policy& pol)
{
   return boost::math::ltrunc(v.value(), pol);
}
inline long ltrunc(const concepts::std_real_concept& v)
{
   return boost::math::ltrunc(v.value(), policies::policy<>());
}

#ifdef BOOST_HAS_LONG_LONG

template <class Policy>
inline boost::long_long_type lltrunc(const concepts::std_real_concept& v, const Policy& pol)
{
   return boost::math::lltrunc(v.value(), pol);
}
inline boost::long_long_type lltrunc(const concepts::std_real_concept& v)
{
   return boost::math::lltrunc(v.value(), policies::policy<>());
}

#endif

// Streaming:
template <class charT, class traits>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& os, const std_real_concept& a)
{
   return os << a.value();
}
template <class charT, class traits>
inline std::basic_istream<charT, traits>& operator>>(std::basic_istream<charT, traits>& is, std_real_concept& a)
{
#if defined(__SGI_STL_PORT) || defined(_RWSTD_VER) || defined(__LIBCOMO__) || defined(_LIBCPP_VERSION)
   std::string s;
   std_real_concept_base_type d;
   is >> s;
   std::sscanf(s.c_str(), "%Lf", &d);
   a = d;
   return is;
#else
   std_real_concept_base_type v;
   is >> v;
   a = v;
   return is;
#endif
}

} // namespace concepts
}}

#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/big_constant.hpp>

namespace boost{ namespace math{
namespace tools
{

template <>
inline concepts::std_real_concept make_big_value<concepts::std_real_concept>(boost::math::tools::largest_float val, const char*, boost::false_type const&, boost::false_type const&)
{
   return val;  // Can't use lexical_cast here, sometimes it fails....
}

template <>
inline concepts::std_real_concept max_value<concepts::std_real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::std_real_concept))
{
   return max_value<concepts::std_real_concept_base_type>();
}

template <>
inline concepts::std_real_concept min_value<concepts::std_real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::std_real_concept))
{
   return min_value<concepts::std_real_concept_base_type>();
}

template <>
inline concepts::std_real_concept log_max_value<concepts::std_real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::std_real_concept))
{
   return log_max_value<concepts::std_real_concept_base_type>();
}

template <>
inline concepts::std_real_concept log_min_value<concepts::std_real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::std_real_concept))
{
   return log_min_value<concepts::std_real_concept_base_type>();
}

template <>
inline concepts::std_real_concept epsilon(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::std_real_concept))
{
   return tools::epsilon<concepts::std_real_concept_base_type>();
}

template <>
inline BOOST_MATH_CONSTEXPR int digits<concepts::std_real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::std_real_concept)) BOOST_NOEXCEPT
{ // Assume number of significand bits is same as std_real_concept_base_type,
  // unless std::numeric_limits<T>::is_specialized to provide digits.
   return digits<concepts::std_real_concept_base_type>();
}

template <>
inline double real_cast<double, concepts::std_real_concept>(concepts::std_real_concept r)
{
   return static_cast<double>(r.value());
}


} // namespace tools

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
using concepts::itrunc;
using concepts::ltrunc;
using concepts::lltrunc;
using concepts::iround;
using concepts::lround;
using concepts::llround;
#endif

} // namespace math
} // namespace boost

//
// These must go at the end, as they include stuff that won't compile until
// after std_real_concept has been defined:
//
#include <boost/math/special_functions/acosh.hpp>
#include <boost/math/special_functions/asinh.hpp>
#include <boost/math/special_functions/atanh.hpp>

#endif // BOOST_MATH_STD_REAL_CONCEPT_HPP

/* std_real_concept.hpp
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
*/