/* Boost interval/arith.hpp template implementation file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002-2003 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_ARITH_HPP
#define BOOST_NUMERIC_INTERVAL_ARITH_HPP

#include <boost/config.hpp>
#include <boost/numeric/interval/interval.hpp>
#include <boost/numeric/interval/detail/bugs.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/numeric/interval/detail/division.hpp>
#include <algorithm>

namespace boost {
namespace numeric {

/*
 * Basic arithmetic operators
 */

template<class T, class Policies> inline
const interval<T, Policies>& operator+(const interval<T, Policies>& x)
{
  return x;
}

template<class T, class Policies> inline
interval<T, Policies> operator-(const interval<T, Policies>& x)
{
  if (interval_lib::detail::test_input(x))
    return interval<T, Policies>::empty();
  return interval<T, Policies>(-x.upper(), -x.lower(), true);
}

template<class T, class Policies> inline
interval<T, Policies>& interval<T, Policies>::operator+=(const interval<T, Policies>& r)
{
  if (interval_lib::detail::test_input(*this, r))
    set_empty();
  else {
    typename Policies::rounding rnd;
    set(rnd.add_down(low, r.low), rnd.add_up(up, r.up));
  }
  return *this;
}

template<class T, class Policies> inline
interval<T, Policies>& interval<T, Policies>::operator+=(const T& r)
{
  if (interval_lib::detail::test_input(*this, r))
    set_empty();
  else {
    typename Policies::rounding rnd;
    set(rnd.add_down(low, r), rnd.add_up(up, r));
  }
  return *this;
}

template<class T, class Policies> inline
interval<T, Policies>& interval<T, Policies>::operator-=(const interval<T, Policies>& r)
{
  if (interval_lib::detail::test_input(*this, r))
    set_empty();
  else {
    typename Policies::rounding rnd;
    set(rnd.sub_down(low, r.up), rnd.sub_up(up, r.low));
  }
  return *this;
}

template<class T, class Policies> inline
interval<T, Policies>& interval<T, Policies>::operator-=(const T& r)
{
  if (interval_lib::detail::test_input(*this, r))
    set_empty();
  else {
    typename Policies::rounding rnd;
    set(rnd.sub_down(low, r), rnd.sub_up(up, r));
  }
  return *this;
}

template<class T, class Policies> inline
interval<T, Policies>& interval<T, Policies>::operator*=(const interval<T, Policies>& r)
{
  return *this = *this * r;
}

template<class T, class Policies> inline
interval<T, Policies>& interval<T, Policies>::operator*=(const T& r)
{
  return *this = r * *this;
}

template<class T, class Policies> inline
interval<T, Policies>& interval<T, Policies>::operator/=(const interval<T, Policies>& r)
{
  return *this = *this / r;
}

template<class T, class Policies> inline
interval<T, Policies>& interval<T, Policies>::operator/=(const T& r)
{
  return *this = *this / r;
}

template<class T, class Policies> inline
interval<T, Policies> operator+(const interval<T, Policies>& x,
                                const interval<T, Policies>& y)
{
  if (interval_lib::detail::test_input(x, y))
    return interval<T, Policies>::empty();
  typename Policies::rounding rnd;
  return interval<T,Policies>(rnd.add_down(x.lower(), y.lower()),
                              rnd.add_up  (x.upper(), y.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> operator+(const T& x, const interval<T, Policies>& y)
{
  if (interval_lib::detail::test_input(x, y))
    return interval<T, Policies>::empty();
  typename Policies::rounding rnd;
  return interval<T,Policies>(rnd.add_down(x, y.lower()),
                              rnd.add_up  (x, y.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> operator+(const interval<T, Policies>& x, const T& y)
{ return y + x; }

template<class T, class Policies> inline
interval<T, Policies> operator-(const interval<T, Policies>& x,
                                const interval<T, Policies>& y)
{
  if (interval_lib::detail::test_input(x, y))
    return interval<T, Policies>::empty();
  typename Policies::rounding rnd;
  return interval<T,Policies>(rnd.sub_down(x.lower(), y.upper()),
                              rnd.sub_up  (x.upper(), y.lower()), true);
}

template<class T, class Policies> inline
interval<T, Policies> operator-(const T& x, const interval<T, Policies>& y)
{
  if (interval_lib::detail::test_input(x, y))
    return interval<T, Policies>::empty();
  typename Policies::rounding rnd;
  return interval<T,Policies>(rnd.sub_down(x, y.upper()),
                              rnd.sub_up  (x, y.lower()), true);
}

template<class T, class Policies> inline
interval<T, Policies> operator-(const interval<T, Policies>& x, const T& y)
{
  if (interval_lib::detail::test_input(x, y))
    return interval<T, Policies>::empty();
  typename Policies::rounding rnd;
  return interval<T,Policies>(rnd.sub_down(x.lower(), y),
                              rnd.sub_up  (x.upper(), y), true);
}

template<class T, class Policies> inline
interval<T, Policies> operator*(const interval<T, Policies>& x,
                                const interval<T, Policies>& y)
{
  BOOST_USING_STD_MIN();
  BOOST_USING_STD_MAX();
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x, y))
    return I::empty();
  typename Policies::rounding rnd;
  const T& xl = x.lower();
  const T& xu = x.upper();
  const T& yl = y.lower();
  const T& yu = y.upper();

  if (interval_lib::user::is_neg(xl))
    if (interval_lib::user::is_pos(xu))
      if (interval_lib::user::is_neg(yl))
        if (interval_lib::user::is_pos(yu)) // M * M
          return I(min BOOST_PREVENT_MACRO_SUBSTITUTION(rnd.mul_down(xl, yu), rnd.mul_down(xu, yl)),
                   max BOOST_PREVENT_MACRO_SUBSTITUTION(rnd.mul_up  (xl, yl), rnd.mul_up  (xu, yu)), true);
        else                    // M * N
          return I(rnd.mul_down(xu, yl), rnd.mul_up(xl, yl), true);
      else
        if (interval_lib::user::is_pos(yu)) // M * P
          return I(rnd.mul_down(xl, yu), rnd.mul_up(xu, yu), true);
        else                    // M * Z
          return I(static_cast<T>(0), static_cast<T>(0), true);
    else
      if (interval_lib::user::is_neg(yl))
        if (interval_lib::user::is_pos(yu)) // N * M
          return I(rnd.mul_down(xl, yu), rnd.mul_up(xl, yl), true);
        else                    // N * N
          return I(rnd.mul_down(xu, yu), rnd.mul_up(xl, yl), true);
      else
        if (interval_lib::user::is_pos(yu)) // N * P
          return I(rnd.mul_down(xl, yu), rnd.mul_up(xu, yl), true);
        else                    // N * Z
          return I(static_cast<T>(0), static_cast<T>(0), true);
  else
    if (interval_lib::user::is_pos(xu))
      if (interval_lib::user::is_neg(yl))
        if (interval_lib::user::is_pos(yu)) // P * M
          return I(rnd.mul_down(xu, yl), rnd.mul_up(xu, yu), true);
        else                    // P * N
          return I(rnd.mul_down(xu, yl), rnd.mul_up(xl, yu), true);
      else
        if (interval_lib::user::is_pos(yu)) // P * P
          return I(rnd.mul_down(xl, yl), rnd.mul_up(xu, yu), true);
        else                    // P * Z
          return I(static_cast<T>(0), static_cast<T>(0), true);
    else                        // Z * ?
      return I(static_cast<T>(0), static_cast<T>(0), true);
}

template<class T, class Policies> inline
interval<T, Policies> operator*(const T& x, const interval<T, Policies>& y)
{ 
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x, y))
    return I::empty();
  typename Policies::rounding rnd;
  const T& yl = y.lower();
  const T& yu = y.upper();
  // x is supposed not to be infinite
  if (interval_lib::user::is_neg(x))
    return I(rnd.mul_down(x, yu), rnd.mul_up(x, yl), true);
  else if (interval_lib::user::is_zero(x))
    return I(static_cast<T>(0), static_cast<T>(0), true);
  else
    return I(rnd.mul_down(x, yl), rnd.mul_up(x, yu), true);
}

template<class T, class Policies> inline
interval<T, Policies> operator*(const interval<T, Policies>& x, const T& y)
{ return y * x; }

template<class T, class Policies> inline
interval<T, Policies> operator/(const interval<T, Policies>& x,
                                const interval<T, Policies>& y)
{
  if (interval_lib::detail::test_input(x, y))
    return interval<T, Policies>::empty();
  if (zero_in(y))
    if (!interval_lib::user::is_zero(y.lower()))
      if (!interval_lib::user::is_zero(y.upper()))
        return interval_lib::detail::div_zero(x);
      else
        return interval_lib::detail::div_negative(x, y.lower());
    else
      if (!interval_lib::user::is_zero(y.upper()))
        return interval_lib::detail::div_positive(x, y.upper());
      else
        return interval<T, Policies>::empty();
  else
    return interval_lib::detail::div_non_zero(x, y);
}

template<class T, class Policies> inline
interval<T, Policies> operator/(const T& x, const interval<T, Policies>& y)
{
  if (interval_lib::detail::test_input(x, y))
    return interval<T, Policies>::empty();
  if (zero_in(y))
    if (!interval_lib::user::is_zero(y.lower()))
      if (!interval_lib::user::is_zero(y.upper()))
        return interval_lib::detail::div_zero<T, Policies>(x);
      else
        return interval_lib::detail::div_negative<T, Policies>(x, y.lower());
    else
      if (!interval_lib::user::is_zero(y.upper()))
        return interval_lib::detail::div_positive<T, Policies>(x, y.upper());
      else
        return interval<T, Policies>::empty();
  else
    return interval_lib::detail::div_non_zero(x, y);
}

template<class T, class Policies> inline
interval<T, Policies> operator/(const interval<T, Policies>& x, const T& y)
{
  if (interval_lib::detail::test_input(x, y) || interval_lib::user::is_zero(y))
    return interval<T, Policies>::empty();
  typename Policies::rounding rnd;
  const T& xl = x.lower();
  const T& xu = x.upper();
  if (interval_lib::user::is_neg(y))
    return interval<T, Policies>(rnd.div_down(xu, y), rnd.div_up(xl, y), true);
  else
    return interval<T, Policies>(rnd.div_down(xl, y), rnd.div_up(xu, y), true);
}

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_ARITH_HPP

/* arith.hpp
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
*/