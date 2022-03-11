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