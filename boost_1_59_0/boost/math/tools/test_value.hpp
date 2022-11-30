// Copyright Paul A. Bristow 2017.
// Copyright John Maddock 2017.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// test_value.hpp

#ifndef TEST_VALUE_HPP
#define TEST_VALUE_HPP

// BOOST_MATH_TEST_VALUE is used to create a test value of suitable type from a decimal digit string.
// Two parameters, both a floating-point literal double like 1.23 (not long double so no suffix L)
// and a decimal digit string const char* like "1.23" must be provided.
// The decimal value represented must be the same of course, with at least enough precision for long double.
//   Note there are two gotchas to this approach:
// * You need all values to be real floating-point values
// * and *MUST* include a decimal point (to avoid confusion with an integer literal).
// * It's slow to compile compared to a simple literal.

// Speed is not an issue for a few test values,
// but it's not generally usable in large tables
// where you really need everything to be statically initialized.

// Macro BOOST_MATH_INSTRUMENT_CREATE_TEST_VALUE provides a global diagnostic value for create_type.

#include <boost/cstdfloat.hpp> // For float_64_t, float128_t. Must be first include!
#ifndef BOOST_MATH_STANDALONE
#include <boost/lexical_cast.hpp>
#endif
#include <limits>
#include <type_traits>

#ifdef BOOST_MATH_INSTRUMENT_CREATE_TEST_VALUE
// global int create_type(0); must be defined before including this file.
#endif

#ifdef BOOST_HAS_FLOAT128
typedef __float128 largest_float;
#define BOOST_MATH_TEST_LARGEST_FLOAT_SUFFIX(x) x##Q
#define BOOST_MATH_TEST_LARGEST_FLOAT_DIGITS 113
#else
typedef long double largest_float;
#define BOOST_MATH_TEST_LARGEST_FLOAT_SUFFIX(x) x##L
#define BOOST_MATH_TEST_LARGEST_FLOAT_DIGITS std::numeric_limits<long double>::digits
#endif

template <class T, class T2>
inline T create_test_value(largest_float val, const char*, const std::true_type&, const T2&)
{ // Construct from long double or quad parameter val (ignoring string/const char* str).
  // (This is case for MPL parameters = true_ and T2 == false_,
  // and  MPL parameters = true_ and T2 == true_  cpp_bin_float)
  // All built-in/fundamental floating-point types,
  // and other User-Defined Types that can be constructed without loss of precision
  // from long double suffix L (or quad suffix Q),
  //
  // Choose this method, even if can be constructed from a string,
  // because it will be faster, and more likely to be the closest representation.
  // (This is case for MPL parameters = true_type and T2 == true_type).
  #ifdef BOOST_MATH_INSTRUMENT_CREATE_TEST_VALUE
  create_type = 1;
  #endif
  return static_cast<T>(val);
}

template <class T>
inline T create_test_value(largest_float, const char* str, const std::false_type&, const std::true_type&)
{ // Construct from decimal digit string const char* @c str (ignoring long double parameter).
  // For example, extended precision or other User-Defined types which ARE constructible from a string
  // (but not from double, or long double without loss of precision).
  // (This is case for MPL parameters = false_type and T2 == true_type).
  #ifdef BOOST_MATH_INSTRUMENT_CREATE_TEST_VALUE
  create_type = 2;
  #endif
  return T(str);
}

template <class T>
inline T create_test_value(largest_float, const char* str, const std::false_type&, const std::false_type&)
{ // Create test value using from lexical cast of decimal digit string const char* str.
  // For example, extended precision or other User-Defined types which are NOT constructible from a string
  // (NOR constructible from a long double).
  // (This is case T1 = false_type and T2 == false_type).
#ifdef BOOST_MATH_INSTRUMENT_CREATE_TEST_VALUE
  create_type = 3;
#endif
#if defined(BOOST_MATH_STANDALONE)
  static_assert(sizeof(T) == 0, "Can not create a test value using lexical cast of string in standalone mode");
  return T();
#else
  return boost::lexical_cast<T>(str);
#endif
}

// T real type, x a decimal digits representation of a floating-point, for example: 12.34.
// It must include a decimal point (or it would be interpreted as an integer).

//  x is converted to a long double by appending the letter L (to suit long double fundamental type), 12.34L.
//  x is also passed as a const char* or string representation "12.34"
//  (to suit most other types that cannot be constructed from long double without possible loss).

// BOOST_MATH_TEST_LARGEST_FLOAT_SUFFIX(x) makes a long double or quad version, with
// suffix a letter L (or Q) to suit long double (or quad) fundamental type, 12.34L or 12.34Q.
// #x makes a decimal digit string version to suit multiprecision and fixed_point constructors, "12.34".
// (Constructing from double or long double (or quad) could lose precision for multiprecision or fixed-point).

// The matching create_test_value function above is chosen depending on the T1 and T2 mpl bool truths.
// The string version from #x is used if the precision of T is greater than long double.

// Example: long double test_value = BOOST_MATH_TEST_VALUE(double, 1.23456789);

#define BOOST_MATH_TEST_VALUE(T, x) create_test_value<T>(\
  BOOST_MATH_TEST_LARGEST_FLOAT_SUFFIX(x),\
  #x,\
  std::integral_constant<bool, \
    std::numeric_limits<T>::is_specialized &&\
      (std::numeric_limits<T>::radix == 2)\
        && (std::numeric_limits<T>::digits <= BOOST_MATH_TEST_LARGEST_FLOAT_DIGITS)\
        && std::is_convertible<largest_float, T>::value>(),\
  std::integral_constant<bool, \
    std::is_constructible<T, const char*>::value>()\
)

#if LDBL_MAX_10_EXP > DBL_MAX_10_EXP
#define BOOST_MATH_TEST_HUGE_FLOAT_SUFFIX(x) BOOST_MATH_TEST_LARGEST_FLOAT_SUFFIX(x)
#else
#define BOOST_MATH_TEST_HUGE_FLOAT_SUFFIX(x) 0.0
#endif

#define BOOST_MATH_HUGE_TEST_VALUE(T, x) create_test_value<T>(\
  BOOST_MATH_TEST_HUGE_FLOAT_SUFFIX(x),\
  #x,\
  std::integral_constant<bool, \
    std::numeric_limits<T>::is_specialized &&\
      (std::numeric_limits<T>::radix == 2)\
        && (std::numeric_limits<T>::digits <= BOOST_MATH_TEST_LARGEST_FLOAT_DIGITS)\
        && std::is_convertible<largest_float, T>::value>(),\
  std::integral_constant<bool, \
    std::is_constructible<T, const char*>::value>()\
)
#endif // TEST_VALUE_HPP

/* test_value.hpp
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
*/