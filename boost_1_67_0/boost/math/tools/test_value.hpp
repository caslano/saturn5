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
#include <boost/lexical_cast.hpp>
#include <boost/type_traits/is_constructible.hpp>
#include <boost/type_traits/is_convertible.hpp>

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
inline T create_test_value(largest_float val, const char*, const boost::true_type&, const T2&)
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
inline T create_test_value(largest_float, const char* str, const boost::false_type&, const boost::true_type&)
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
inline T create_test_value(largest_float, const char* str, const boost::false_type&, const boost::false_type&)
{ // Create test value using from lexical cast of decimal digit string const char* str.
  // For example, extended precision or other User-Defined types which are NOT constructible from a string
  // (NOR constructible from a long double).
    // (This is case T1 = false_type and T2 == false_type).
  #ifdef BOOST_MATH_INSTRUMENT_CREATE_TEST_VALUE
  create_type = 3;
  #endif
  return boost::lexical_cast<T>(str);
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
  boost::integral_constant<bool, \
    std::numeric_limits<T>::is_specialized &&\
      (std::numeric_limits<T>::radix == 2)\
        && (std::numeric_limits<T>::digits <= BOOST_MATH_TEST_LARGEST_FLOAT_DIGITS)\
        && boost::is_convertible<largest_float, T>::value>(),\
  boost::integral_constant<bool, \
    boost::is_constructible<T, const char*>::value>()\
)
#endif // TEST_VALUE_HPP

/* test_value.hpp
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
*/