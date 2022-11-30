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
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
*/