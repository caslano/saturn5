
//  Copyright (c) 2011 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_BIG_CONSTANT_HPP
#define BOOST_MATH_TOOLS_BIG_CONSTANT_HPP

#include <boost/math/tools/config.hpp>
#ifndef BOOST_MATH_NO_LEXICAL_CAST
#include <boost/lexical_cast.hpp>
#endif
#include <boost/type_traits/is_constructible.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_floating_point.hpp>

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
#else
typedef long double largest_float;
#define BOOST_MATH_LARGEST_FLOAT_C(x) x##L
#endif

template <class T>
inline BOOST_CONSTEXPR_OR_CONST T make_big_value(largest_float v, const char*, boost::true_type const&, boost::false_type const&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(v);
}
template <class T>
inline BOOST_CONSTEXPR_OR_CONST T make_big_value(largest_float v, const char*, boost::true_type const&, boost::true_type const&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(v);
}
#ifndef BOOST_MATH_NO_LEXICAL_CAST
template <class T>
inline T make_big_value(largest_float, const char* s, boost::false_type const&, boost::false_type const&)
{
   return boost::lexical_cast<T>(s);
}
#endif
template <class T>
inline BOOST_MATH_CONSTEXPR T make_big_value(largest_float, const char* s, boost::false_type const&, boost::true_type const&) BOOST_MATH_NOEXCEPT(T)
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
      boost::integral_constant<bool, (boost::is_convertible<boost::math::tools::largest_float, T>::value) && \
      ((D <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::digits) \
          || boost::is_floating_point<T>::value \
          || (boost::math::tools::numeric_traits<T>::is_specialized && \
          (boost::math::tools::numeric_traits<T>::digits10 <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::digits10))) >(), \
      boost::is_constructible<T, const char*>())
//
// For constants too huge for any conceivable long double (and which generate compiler errors if we try and declare them as such):
//
#define BOOST_MATH_HUGE_CONSTANT(T, D, x)\
   boost::math::tools::make_big_value<T>(0.0L, BOOST_STRINGIZE(x), \
   boost::integral_constant<bool, boost::is_floating_point<T>::value || (boost::math::tools::numeric_traits<T>::is_specialized && boost::math::tools::numeric_traits<T>::max_exponent <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::max_exponent && boost::math::tools::numeric_traits<T>::digits <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::digits)>(), \
   boost::is_constructible<T, const char*>())

}}} // namespaces

#endif


/* big_constant.hpp
c8we1jsKJR02GNCnn7P/jKW6l/UoXWD/Uc9CdaGP94Y6G93rKB3Qvj4YqBYID9wRsYFDO9Mvo+tuY/RlcPekzzrXR5E4yo+u6zfh+89tPhy9Ojl21h4b9zurwfvr/izxj2YNv3lVLI6uimUvuvWPpj/maQQp8qDS/4bMpr4PGR6/tF6Ww+au7Gzrvhat3V/N3wFQSwMECgAAAAgALWdKUuG7+YD7AAAAwwEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMDIyVVQFAAG2SCRgTZGxjsMgDIZ3nsJqdWPiXmeUJbd0baXbKTgNKsER0FZ5+yM012QJsf35t3+QiWLSKlIjpPUd5+NO04uDiY3Qj+Aqzb6zNyFxzUt8o2Iv9nCh8KRQRWtIyECjm2Zg+SlE6yz5tBC6BBmJpa8Rnn1O438I0qshb9PyMKpAMO8AVZVr0bKHl009bPZaS7kT360gNQ+D8qYRa1XiJylHzp570vdGfF3O7c/pjM5e55vA+fN9OB7r0UFd43aS4xvGZPhRAFiFN3J5yuKvOP+lYLsJjEoKVJcoQOoJ5hnQqwhXIg+72HPaCfksbJagEDhoNtnJIQtuQokfCNd3+wNQSwMECgAAAAgALWdKUhMxHDMAAQAAwQEA
*/