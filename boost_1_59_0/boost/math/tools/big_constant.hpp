
//  Copyright (c) 2011 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_BIG_CONSTANT_HPP
#define BOOST_MATH_TOOLS_BIG_CONSTANT_HPP

#include <boost/math/tools/config.hpp>
#ifndef BOOST_MATH_STANDALONE
#include <boost/lexical_cast.hpp>
#endif

#include <cstdlib>
#include <type_traits>
#include <limits>

namespace boost{ namespace math{ 

namespace tools{

template <class T>
struct numeric_traits : public std::numeric_limits< T > {};

#ifdef BOOST_MATH_USE_FLOAT128
typedef __float128 largest_float;
#define BOOST_MATH_LARGEST_FLOAT_C(x) x##Q
template <>
struct numeric_traits<__float128>
{
   static const int digits = 113;
   static const int digits10 = 33;
   static const int max_exponent = 16384;
   static const bool is_specialized = true;
};
#elif LDBL_DIG > DBL_DIG
typedef long double largest_float;
#define BOOST_MATH_LARGEST_FLOAT_C(x) x##L
#else
typedef double largest_float;
#define BOOST_MATH_LARGEST_FLOAT_C(x) x
#endif

template <class T>
inline constexpr T make_big_value(largest_float v, const char*, std::true_type const&, std::false_type const&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(v);
}
template <class T>
inline constexpr T make_big_value(largest_float v, const char*, std::true_type const&, std::true_type const&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(v);
}
#ifndef BOOST_MATH_NO_LEXICAL_CAST
template <class T>
inline T make_big_value(largest_float, const char* s, std::false_type const&, std::false_type const&)
{
   return boost::lexical_cast<T>(s);
}
#else
template <typename T>
inline T make_big_value(largest_float, const char* s, std::false_type const&, std::false_type const&)
{
   static_assert(sizeof(T) == 0, "Type is unsupported in standalone mode. Please disable and try again.");
}
#endif
template <class T>
inline constexpr T make_big_value(largest_float, const char* s, std::false_type const&, std::true_type const&) BOOST_MATH_NOEXCEPT(T)
{
   return T(s);
}

//
// For constants which might fit in a long double (if it's big enough):
//
#define BOOST_MATH_BIG_CONSTANT(T, D, x)\
   boost::math::tools::make_big_value<T>(\
      BOOST_MATH_LARGEST_FLOAT_C(x), \
      BOOST_STRINGIZE(x), \
      std::integral_constant<bool, (std::is_convertible<boost::math::tools::largest_float, T>::value) && \
      ((D <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::digits) \
          || std::is_floating_point<T>::value \
          || (boost::math::tools::numeric_traits<T>::is_specialized && \
          (boost::math::tools::numeric_traits<T>::digits10 <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::digits10))) >(), \
      std::is_constructible<T, const char*>())
//
// For constants too huge for any conceivable long double (and which generate compiler errors if we try and declare them as such):
//
#define BOOST_MATH_HUGE_CONSTANT(T, D, x)\
   boost::math::tools::make_big_value<T>(0.0L, BOOST_STRINGIZE(x), \
   std::integral_constant<bool, std::is_floating_point<T>::value || (boost::math::tools::numeric_traits<T>::is_specialized && boost::math::tools::numeric_traits<T>::max_exponent <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::max_exponent && boost::math::tools::numeric_traits<T>::digits <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::digits)>(), \
   std::is_constructible<T, const char*>())

}}} // namespaces

#endif


/* big_constant.hpp
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
*/