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

#include <boost/math/policies/policy.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <limits>
#include <ostream>
#include <istream>
#include <cmath>

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
#endif
   std_real_concept(unsigned long long c) : m_value(static_cast<std_real_concept_base_type>(c)){}
   std_real_concept(long long c) : m_value(static_cast<std_real_concept_base_type>(c)){}
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
#endif
   std_real_concept& operator=(long long c) { m_value = static_cast<std_real_concept_base_type>(c); return *this; }
   std_real_concept& operator=(unsigned long long c) { m_value = static_cast<std_real_concept_base_type>(c); return *this; }

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

template <class Policy>
inline long long llround(const concepts::std_real_concept& v, const Policy& pol)
{
   return boost::math::llround(v.value(), pol);
}
inline long long llround(const concepts::std_real_concept& v)
{
   return boost::math::llround(v.value(), policies::policy<>());
}

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

template <class Policy>
inline long long lltrunc(const concepts::std_real_concept& v, const Policy& pol)
{
   return boost::math::lltrunc(v.value(), pol);
}
inline long long lltrunc(const concepts::std_real_concept& v)
{
   return boost::math::lltrunc(v.value(), policies::policy<>());
}

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
inline concepts::std_real_concept make_big_value<concepts::std_real_concept>(boost::math::tools::largest_float val, const char*, std::false_type const&, std::false_type const&)
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
inline constexpr int digits<concepts::std_real_concept>(BOOST_MATH_EXPLICIT_TEMPLATE_TYPE_SPEC(concepts::std_real_concept)) noexcept
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

#if defined(_MSC_VER) && (_MSC_VER <= 1310)
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