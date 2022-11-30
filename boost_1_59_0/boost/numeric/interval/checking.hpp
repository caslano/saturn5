/* Boost interval/checking.hpp template implementation file
 *
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_CHECKING_HPP
#define BOOST_NUMERIC_INTERVAL_CHECKING_HPP

#include <stdexcept>
#include <string>
#include <cassert>
#include <boost/limits.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

struct exception_create_empty
{
  void operator()()
  {
    throw std::runtime_error("boost::interval: empty interval created");
  }
};

struct exception_invalid_number
{
  void operator()()
  {
    throw std::invalid_argument("boost::interval: invalid number");
  }
};

template<class T>
struct checking_base
{
  static T pos_inf()
  {
    assert(std::numeric_limits<T>::has_infinity);
    return std::numeric_limits<T>::infinity();
  }
  static T neg_inf()
  {
    assert(std::numeric_limits<T>::has_infinity);
    return -std::numeric_limits<T>::infinity();
  }
  static T nan()
  {
    assert(std::numeric_limits<T>::has_quiet_NaN);
    return std::numeric_limits<T>::quiet_NaN();
  }
  static bool is_nan(const T& x)
  {
    return std::numeric_limits<T>::has_quiet_NaN && (x != x);
  }
  static T empty_lower()
  {
    return (std::numeric_limits<T>::has_quiet_NaN ?
            std::numeric_limits<T>::quiet_NaN() : static_cast<T>(1));
  }
  static T empty_upper()
  {
    return (std::numeric_limits<T>::has_quiet_NaN ?
            std::numeric_limits<T>::quiet_NaN() : static_cast<T>(0));
  }
  static bool is_empty(const T& l, const T& u)
  {
    return !(l <= u); // safety for partial orders
  }
};

template<class T, class Checking = checking_base<T>,
         class Exception = exception_create_empty>
struct checking_no_empty: Checking
{
  static T nan()
  {
    assert(false);
    return Checking::nan();
  }
  static T empty_lower()
  {
    Exception()();
    return Checking::empty_lower();
  }
  static T empty_upper()
  {
    Exception()();
    return Checking::empty_upper();
  }
  static bool is_empty(const T&, const T&)
  {
    return false;
  }
};

template<class T, class Checking = checking_base<T> >
struct checking_no_nan: Checking
{
  static bool is_nan(const T&)
  {
    return false;
  }
};

template<class T, class Checking = checking_base<T>,
         class Exception = exception_invalid_number>
struct checking_catch_nan: Checking
{
  static bool is_nan(const T& x)
  {
    if (Checking::is_nan(x)) Exception()();
    return false;
  }
};

template<class T>
struct checking_strict:
  checking_no_nan<T, checking_no_empty<T> >
{};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_CHECKING_HPP

/* checking.hpp
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
*/