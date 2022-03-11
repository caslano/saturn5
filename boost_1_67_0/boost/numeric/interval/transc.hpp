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