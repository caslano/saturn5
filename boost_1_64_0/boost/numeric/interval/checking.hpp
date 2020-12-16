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
UZXv+/jvz23nH2GuTdCuwgbsPOmPuSarUtFOEfRB7X//YewmyJcKC/mZ3gxxIPNm1ic3bCXWNJl+pb37N+96e9fEeYmsWqW9/neur341wHpXKMfwbyHr2CjwNWqrAuuhwmoGb/bAnkqmwezmt42I30UyXWa+d+bpo59kWsy+dSt8hvUg2lmpWyIHX5NZV9pL+nltyf545Jkp7dPM3Ho2uo/6SWbGbNmNAReQg2TGzCJXam3E7xFMlfPygn42y7sVhrOpKfK6wrr4ZZ/H3dBMQ02HWdHsLptwZifTZ7Z9aTU/rGkyXW6jv2ViDGSOzK622VWAOxCzQvo5+VL7M8gzMgdmUfQXM3HPEdaj1QqMb7945tb2444ifsLOpFbH3bdU2MbLCyJQW81VrXenky9xjhTmZvIX7jKDhf29yekn9hxhDb4XFKLuCvv1KuYw6oSwmQXVbHC2Efbcqf1W7EcWquYR8kT5bysLy875G7Wnv7C/I+xn4lsemSmzyAaO5djDyeyYDWowEZZOZsDMfbEecvAiWTVmR/50v4TxkdWstH+TaEz9/qE491hqqAVV5vwd+mn4a8wn3JktkfNk1O9+L8dgv2V2m37GLJlYDWuazLByf79JP0+fq7oB5x5L5ZnoOv3MKI1piH6SaTLr9Z9lN5BnZBrMvl6b0gfnOjJ1Zh5XR47F2rRSnuuu0c+1ax7Ox/2PzLSyn5f/rSlDpicjP8kqv3VVWJXz21uhXpP5VNpF+mnQIwR7/1YyrUr7t+h0LXDA+FLIbJkNt0pBvlwl02ZWPXZzO6w/MitmlgeTXHBfIdNh9nvdtxOYMzJLZmH17iJGFtZUe5gVdG5jiNpDZsasub7+EdRPMj1mvRqHDEJdIuNj+FJ2FXnWnsyG2dxNozVRs8j4GDxsE07iDkRmysx976eaWEdkhszm55nGYx8j43Ptf+EtcvAQmREzi8BWyr/zQ+bIrFmbPQnYj8j0mU0zT6mB3CVzZtbUctZs1EEbWrfMZqZk3UEOkrkwq22QgPeFkfH39TVzzUd9IavK39fQUgc1UrzP0Cl8LeoLGe/nIO37uJNkkvH4uYW3sUN9Ee/rnxZ4BDlIxuP3J11RhBwU7Sy/7O6APLNVfd+w7trJqEtkmswMul/Yhjkj4+87caRzd5zBRLt7p9ObIndFu60jSgKw3sl4Lvm5+T7EvYNMl9kxs3lYY33EGIa3jjbBPibauQzTR05EiXabDwU74vxJpses8zSnGch58Uy73H8m4vsSGc+X0R9roNYlirEvKf7UBzWLzIDHVm/feqwV0a7+2u44f54Qfanapugu8kWM72Ldwl3Yi8X4OvUpvYW9Q7yvrb8jcqlQvG+/8+IFyEHRzl/xvQpyULzvjOY63A017VTbTWlgh2+OhmR8XrYn7UNsHUS7Xc1CE3EfI+O55Ojboi3yk8ySmb529kXkmXhfl61B1bHeRTv1aqOVf/dYvO+NVSpq8mLR7tvh4prYw8n4fA5smzoGcRftfsf3Lkb8yPh8mnfJGIn4ib4M6B9TgL1ftNudOOcjYiTG7j69ZWOcoe1V8zrjvXZf7GNkVsxOJx7B3bc2GX/mxzkFmljvol1L37h5WNOi3YybNpOx9ws7FJjSC3EQdmLMrR2IA5ktM+3QF+NwLhDtbjeu+QhrTLQrL70Tj7kmc2L2asYT20qjBFUd38UeyvOuAxlvt+PDA/QliMyO2bwtS2ojB8l4HNyWTp+CeSHjcW8wVy0L3yrJ0lMrzpgV1qflzLWIe5Fqu4B8hwLE/b2Gmgmz0OKrhRgDmTGz4IlXn2F/EO0+nlq2BOMjM+K1YOCkr1h/ot0UrStqqOWiXbdON/bhnEw=
*/