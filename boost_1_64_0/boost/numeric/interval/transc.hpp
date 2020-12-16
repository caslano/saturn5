/* Boost interval/transc.hpp template implementation file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_TRANSC_HPP
#define BOOST_NUMERIC_INTERVAL_TRANSC_HPP

#include <boost/config.hpp>
#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/bugs.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/numeric/interval/rounding.hpp>
#include <boost/numeric/interval/constants.hpp>
#include <boost/numeric/interval/arith.hpp>
#include <boost/numeric/interval/arith2.hpp>
#include <algorithm>

namespace boost {
namespace numeric {

template<class T, class Policies> inline
interval<T, Policies> exp(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.exp_down(x.lower()), rnd.exp_up(x.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> log(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x) ||
      !interval_lib::user::is_pos(x.upper()))
    return I::empty();
  typename Policies::rounding rnd;
  typedef typename Policies::checking checking;
  T l = !interval_lib::user::is_pos(x.lower())
             ? checking::neg_inf() : rnd.log_down(x.lower());
  return I(l, rnd.log_up(x.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> cos(const interval<T, Policies>& x)
{
  if (interval_lib::detail::test_input(x))
    return interval<T, Policies>::empty();
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  typedef typename interval_lib::unprotect<I>::type R;

  // get lower bound within [0, pi]
  const R pi2 = interval_lib::pi_twice<R>();
  R tmp = fmod((const R&)x, pi2);
  if (width(tmp) >= pi2.lower())
    return I(static_cast<T>(-1), static_cast<T>(1), true); // we are covering a full period
  if (tmp.lower() >= interval_lib::constants::pi_upper<T>())
    return -cos(tmp - interval_lib::pi<R>());
  T l = tmp.lower();
  T u = tmp.upper();

  BOOST_USING_STD_MIN();
  // separate into monotone subintervals
  if (u <= interval_lib::constants::pi_lower<T>())
    return I(rnd.cos_down(u), rnd.cos_up(l), true);
  else if (u <= pi2.lower())
    return I(static_cast<T>(-1), rnd.cos_up(min BOOST_PREVENT_MACRO_SUBSTITUTION(rnd.sub_down(pi2.lower(), u), l)), true);
  else
    return I(static_cast<T>(-1), static_cast<T>(1), true);
}

template<class T, class Policies> inline
interval<T, Policies> sin(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x))
    return I::empty();
  typename Policies::rounding rnd;
  typedef typename interval_lib::unprotect<I>::type R;
  I r = cos((const R&)x - interval_lib::pi_half<R>());
  (void)&rnd;
  return r;
}

template<class T, class Policies> inline
interval<T, Policies> tan(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x))
    return I::empty();
  typename Policies::rounding rnd;
  typedef typename interval_lib::unprotect<I>::type R;

  // get lower bound within [-pi/2, pi/2]
  const R pi = interval_lib::pi<R>();
  R tmp = fmod((const R&)x, pi);
  const T pi_half_d = interval_lib::constants::pi_half_lower<T>();
  if (tmp.lower() >= pi_half_d)
    tmp -= pi;
  if (tmp.lower() <= -pi_half_d || tmp.upper() >= pi_half_d)
    return I::whole();
  return I(rnd.tan_down(tmp.lower()), rnd.tan_up(tmp.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> asin(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x)
     || x.upper() < static_cast<T>(-1) || x.lower() > static_cast<T>(1))
    return I::empty();
  typename Policies::rounding rnd;
  T l = (x.lower() <= static_cast<T>(-1))
             ? -interval_lib::constants::pi_half_upper<T>()
             : rnd.asin_down(x.lower());
  T u = (x.upper() >= static_cast<T>(1) )
             ?  interval_lib::constants::pi_half_upper<T>()
             : rnd.asin_up  (x.upper());
  return I(l, u, true);
}

template<class T, class Policies> inline
interval<T, Policies> acos(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x)
     || x.upper() < static_cast<T>(-1) || x.lower() > static_cast<T>(1))
    return I::empty();
  typename Policies::rounding rnd;
  T l = (x.upper() >= static_cast<T>(1) )
          ? static_cast<T>(0)
          : rnd.acos_down(x.upper());
  T u = (x.lower() <= static_cast<T>(-1))
          ? interval_lib::constants::pi_upper<T>()
          : rnd.acos_up  (x.lower());
  return I(l, u, true);
}

template<class T, class Policies> inline
interval<T, Policies> atan(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.atan_down(x.lower()), rnd.atan_up(x.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> sinh(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.sinh_down(x.lower()), rnd.sinh_up(x.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> cosh(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x))
    return I::empty();
  typename Policies::rounding rnd;
  if (interval_lib::user::is_neg(x.upper()))
    return I(rnd.cosh_down(x.upper()), rnd.cosh_up(x.lower()), true);
  else if (!interval_lib::user::is_neg(x.lower()))
    return I(rnd.cosh_down(x.lower()), rnd.cosh_up(x.upper()), true);
  else
    return I(static_cast<T>(1), rnd.cosh_up(-x.lower() > x.upper() ? x.lower() : x.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> tanh(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.tanh_down(x.lower()), rnd.tanh_up(x.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> asinh(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x))
    return I::empty();
  typename Policies::rounding rnd;
  return I(rnd.asinh_down(x.lower()), rnd.asinh_up(x.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> acosh(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x) || x.upper() < static_cast<T>(1))
    return I::empty();
  typename Policies::rounding rnd;
  T l = x.lower() <= static_cast<T>(1) ? static_cast<T>(0) : rnd.acosh_down(x.lower());
  return I(l, rnd.acosh_up(x.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> atanh(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x)
      || x.upper() < static_cast<T>(-1) || x.lower() > static_cast<T>(1))
    return I::empty();
  typename Policies::rounding rnd;
  typedef typename Policies::checking checking;
  T l = (x.lower() <= static_cast<T>(-1))
             ? checking::neg_inf() : rnd.atanh_down(x.lower());
  T u = (x.upper() >= static_cast<T>(1) )
             ? checking::pos_inf() : rnd.atanh_up  (x.upper());
  return I(l, u, true);
}

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_TRANSC_HPP

/* transc.hpp
JsdnN27bW54nYHLOethFPeV5AiZz/ofbyRCeJ2AyDjejAtmXHTD/v7YXz87ba3Nt5sGshHU0z8zmvMBshbW4n9SI62+Mnk7EHwv+Y2+D4j+xXsMq//0msAfPXnb9NvJ+O4Zj+GMj7brPYPxgpYTFr1l4mOe6sXo6lYRZbUwsPO/CTISde1zsDM9uih1wut+KNRJmLGx3lRY9uN4V22BdZArHBzMXNis2fztzHmYqzKjiIhOeGWCWwiqsqurBGMHshZX4ODOT9ROmETbq+axJrAXK+6wTX7bh2Q1mK+xGlX94JtIbp/2bm8alcY3ZwoKE1Qs6w5zoAisqbOvP+P9wPmH6wtq5/GrOOgHTE/bjn2bOnGvFPH5fXcKcV/p5L2aPBe8rMENhd9/6ZzAOMBn3MqUL9nKPG1eYZ7vxHN753CXOtbB/f+xs7hfWCZ3xhetoF57dlkbXZf2EWQgzPLDPlXsOzFyY3bjiRZmf4jd34rnTsvFMjgHm99fS8HRyyu3E/RZW+q+l4vn0c8xkrltY3t+/0W7Hvx4yN+0O53oS5+WPxT/41Id5DTMU5tJkZAjnGmYg7IDjxCHsJ8xSmFvRaSn8ewdMI6zBjVqxzHmYhbA71S+lcv+DmQt7nmbD9XddaRdacQzz84XyvtSCu8s5LzAzYT7Oc1gjjSZr/2b+w7KDeD6DaWS7xq9YQwJgcj4rNrRjjKopv/mPhXE/1iyYnGvbh3e7cL+FWQr7pfHh+aw3zEpYyRmPyjB+sDJ/LRnP+7Hpi3k3nFyYL9vwDOvmMph1QrTb+u/7zr0J5R1hCu3Px804Vx9f7lVTCn9zC56Dhz4+xHOPaLcZz9mzqtlxjQnbhOeMZ5v3sS5NxX4rbGnXn+cYh6mF7TbiubpCwSjO2dTCvqzHM7bbEXPmp2i3Ds/zKYvfMM9Eu0Q89Y1Hcc/5MbUwB9fiaWGfsJv70TTEVlhG55K8d3jCNMI6TpwbxDMDzFFYzMwwxj1UsaA1/f0Zd5iTsKt25Q/wngqzEfbjQTvGKFGx1acCnXjOgtkK011zdDvvQMr43gxbcoxnBuU3x9VcYME5g9kLi/W6xDus43SsP2E+Znv4t0FfmJWw2VNDOL5aMNnPV+H9xjPuMDdh7XQW8944UrErdp1yuBfDvIWNWTXZmmdMpS9HrC9wHd2DyXlZVmflD569YTJ+S64ObMd8mYF7jjD7XnNCOHaYtTDfnrPG8BwJkzkY5lK/Cb9ZwWRfIvOvPOBeDJNztqvksDOsEzAZIx2X0OncG5X3+Y0p05HfP2HFhFWZ+r4N80X5zU7PJjF3X8FchXWtpTHgOXKmdk4cKCiSxnUEk3352PfcFK4jmKmwHQ0S/uGcweRc7z+8qAdrFsxSWK7OkWXcG9V22x4UYw2ByZyv2yGy8O9VMI2wrJLJq1l3Ye7CPhxKZe3JgTkJS3JN1HCvgjkIuznlFNe07Sztdjtr3GcOVoLJHLxjfcCR+QJL/PufwVqNf+014WU+4zCf+9Ef27b7KfviCNMI27d7GmPkC3MQZr51M88a9WHGwoJaTpjOvii/uTKgvyHPmDAjYb2nPWee9VN+c/vTB9+43mH6wrqYhHJ/j4PpCRt5NHUvzzZKX+JrO3hyH4OZCUt6teAO4w6zFhbaKZ55lgkzFTbbpP8Q7n8wE2GXx8Y+Z07ALGS7l2Mmcx0pv1lnfeP+rLvKGEyqBkWw9izQ7ueUS3vmcn+HybifvJNzlGcbmKOw3TlV1vNMCzMXdqz69fY808JkjPbX8QlnXYLJ8X2P3jGL8VN+M+abzQXucTCZE78No/0ZI5iVsGUd8vJZs2Ayfs8Ozo7l/qfMy0eLYDvWM5itnOs=
*/