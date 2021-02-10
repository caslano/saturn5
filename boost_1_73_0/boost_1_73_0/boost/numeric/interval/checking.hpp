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
UkmR1pw/7+m3fpFFoqpUQNsJi6lq70iWYpmKRXVD0pZ13MkEbrVMYblmSiffOsPL6Qh6OcZbURox+17OUu440E/Ueq5tmos8SchDFdYooPewKEpnuq3vqN0hUTdQDLZ7wm52tXojCAC0L40sXNZp73+AL5iROyDa66LdHbQenvhUFa/06n/a+dSso/3arEC9NazfA0oH1maRUBcCZgo1vLCT5NxAD40MzGRuolPqZwt/+u0Jm5wP6qPZKfQsanirCEMOWvh2o/SCKyYL6bzD7PNo8jEesXg06voLXgfxvP9+Ey53PU7W2fOyLnz3Kc5qj6zDxjERtJ+oQYYDQ6TBxW0V1GYkSvCiKjv1kREOmxLmJ7M5O5lO2Zf478mUfYyP6fiBrNuBt8LhMOn4TVS7PLmYs9lpPD0JAjaaDM/ZcTyP2XAyHp8M557oFSCk+OlyPIw2Nf9axcvxI9WQ3xBZTO5I6zKMF8MLm2Gz08yqo+APQiVhoWgcYWoN4laYNTZKeRAmzkrSDKTHOnzFkGF14UQsCuErBmcS9rHwWKXWiiZT/XnwtuJsWtAnd49KC4EybToS0304AAlH8Dsub95sshs6grzeFITgdr1TD74i6GCjATvX6hCRIETIx2c6ioBq2IfEf7V79DVoLKwN
*/