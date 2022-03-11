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