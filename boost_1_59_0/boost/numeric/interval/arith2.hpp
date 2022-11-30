/* Boost interval/arith2.hpp template implementation file
 *
 * This header provides some auxiliary arithmetic
 * functions: fmod, sqrt, square, pov, inverse and
 * a multi-interval division.
 *
 * Copyright 2002-2003 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_ARITH2_HPP
#define BOOST_NUMERIC_INTERVAL_ARITH2_HPP

#include <boost/config.hpp>
#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/numeric/interval/detail/bugs.hpp>
#include <boost/numeric/interval/detail/division.hpp>
#include <boost/numeric/interval/arith.hpp>
#include <boost/numeric/interval/policies.hpp>
#include <algorithm>
#include <cassert>
#include <boost/config/no_tr1/cmath.hpp>

namespace boost {
namespace numeric {

template<class T, class Policies> inline
interval<T, Policies> fmod(const interval<T, Policies>& x,
                           const interval<T, Policies>& y)
{
  if (interval_lib::detail::test_input(x, y))
    return interval<T, Policies>::empty();
  typename Policies::rounding rnd;
  typedef typename interval_lib::unprotect<interval<T, Policies> >::type I;
  T const &yb = interval_lib::user::is_neg(x.lower()) ? y.lower() : y.upper();
  T n = rnd.int_down(rnd.div_down(x.lower(), yb));
  return (const I&)x - n * (const I&)y;
}

template<class T, class Policies> inline
interval<T, Policies> fmod(const interval<T, Policies>& x, const T& y)
{
  if (interval_lib::detail::test_input(x, y))
    return interval<T, Policies>::empty();
  typename Policies::rounding rnd;
  typedef typename interval_lib::unprotect<interval<T, Policies> >::type I;
  T n = rnd.int_down(rnd.div_down(x.lower(), y));
  return (const I&)x - n * I(y);
}

template<class T, class Policies> inline
interval<T, Policies> fmod(const T& x, const interval<T, Policies>& y)
{
  if (interval_lib::detail::test_input(x, y))
    return interval<T, Policies>::empty();
  typename Policies::rounding rnd;
  typedef typename interval_lib::unprotect<interval<T, Policies> >::type I;
  T const &yb = interval_lib::user::is_neg(x) ? y.lower() : y.upper();
  T n = rnd.int_down(rnd.div_down(x, yb));
  return x - n * (const I&)y;
}

namespace interval_lib {

template<class T, class Policies> inline
interval<T, Policies> division_part1(const interval<T, Policies>& x,
                                     const interval<T, Policies>& y, bool& b)
{
  typedef interval<T, Policies> I;
  b = false;
  if (detail::test_input(x, y))
    return I::empty();
  if (zero_in(y))
    if (!user::is_zero(y.lower()))
      if (!user::is_zero(y.upper()))
        return detail::div_zero_part1(x, y, b);
      else
        return detail::div_negative(x, y.lower());
    else
      if (!user::is_zero(y.upper()))
        return detail::div_positive(x, y.upper());
      else
        return I::empty();
  else
    return detail::div_non_zero(x, y);
}

template<class T, class Policies> inline
interval<T, Policies> division_part2(const interval<T, Policies>& x,
                                     const interval<T, Policies>& y, bool b = true)
{
  if (!b) return interval<T, Policies>::empty();
  return detail::div_zero_part2(x, y);
}

template<class T, class Policies> inline
interval<T, Policies> multiplicative_inverse(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (detail::test_input(x))
    return I::empty();
  T one = static_cast<T>(1);
  typename Policies::rounding rnd;
  if (zero_in(x)) {
    typedef typename Policies::checking checking;
    if (!user::is_zero(x.lower()))
      if (!user::is_zero(x.upper()))
        return I::whole();
      else
        return I(checking::neg_inf(), rnd.div_up(one, x.lower()), true);
    else
      if (!user::is_zero(x.upper()))
        return I(rnd.div_down(one, x.upper()), checking::pos_inf(), true);
      else
        return I::empty();
  } else 
    return I(rnd.div_down(one, x.upper()), rnd.div_up(one, x.lower()), true);
}

namespace detail {

template<class T, class Rounding> inline
T pow_dn(const T& x_, int pwr, Rounding& rnd) // x and pwr are positive
{
  T x = x_;
  T y = (pwr & 1) ? x_ : static_cast<T>(1);
  pwr >>= 1;
  while (pwr > 0) {
    x = rnd.mul_down(x, x);
    if (pwr & 1) y = rnd.mul_down(x, y);
    pwr >>= 1;
  }
  return y;
}

template<class T, class Rounding> inline
T pow_up(const T& x_, int pwr, Rounding& rnd) // x and pwr are positive
{
  T x = x_;
  T y = (pwr & 1) ? x_ : static_cast<T>(1);
  pwr >>= 1;
  while (pwr > 0) {
    x = rnd.mul_up(x, x);
    if (pwr & 1) y = rnd.mul_up(x, y);
    pwr >>= 1;
  }
  return y;
}

} // namespace detail
} // namespace interval_lib

template<class T, class Policies> inline
interval<T, Policies> pow(const interval<T, Policies>& x, int pwr)
{
  BOOST_USING_STD_MAX();
  using interval_lib::detail::pow_dn;
  using interval_lib::detail::pow_up;
  typedef interval<T, Policies> I;

  if (interval_lib::detail::test_input(x))
    return I::empty();

  if (pwr == 0)
    if (interval_lib::user::is_zero(x.lower())
        && interval_lib::user::is_zero(x.upper()))
      return I::empty();
    else
      return I(static_cast<T>(1));
  else if (pwr < 0)
    return interval_lib::multiplicative_inverse(pow(x, -pwr));

  typename Policies::rounding rnd;
  
  if (interval_lib::user::is_neg(x.upper())) {        // [-2,-1]
    T yl = pow_dn(static_cast<T>(-x.upper()), pwr, rnd);
    T yu = pow_up(static_cast<T>(-x.lower()), pwr, rnd);
    if (pwr & 1)     // [-2,-1]^1
      return I(-yu, -yl, true);
    else             // [-2,-1]^2
      return I(yl, yu, true);
  } else if (interval_lib::user::is_neg(x.lower())) { // [-1,1]
    if (pwr & 1) {   // [-1,1]^1
      return I(-pow_up(static_cast<T>(-x.lower()), pwr, rnd), pow_up(x.upper(), pwr, rnd), true);
    } else {         // [-1,1]^2
      return I(static_cast<T>(0), pow_up(max BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<T>(-x.lower()), x.upper()), pwr, rnd), true);
    }
  } else {                                // [1,2]
    return I(pow_dn(x.lower(), pwr, rnd), pow_up(x.upper(), pwr, rnd), true);
  }
}

template<class T, class Policies> inline
interval<T, Policies> sqrt(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x) || interval_lib::user::is_neg(x.upper()))
    return I::empty();
  typename Policies::rounding rnd;
  T l = !interval_lib::user::is_pos(x.lower()) ? static_cast<T>(0) : rnd.sqrt_down(x.lower());
  return I(l, rnd.sqrt_up(x.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> square(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x))
    return I::empty();
  typename Policies::rounding rnd;
  const T& xl = x.lower();
  const T& xu = x.upper();
  if (interval_lib::user::is_neg(xu))
    return I(rnd.mul_down(xu, xu), rnd.mul_up(xl, xl), true);
  else if (interval_lib::user::is_pos(x.lower()))
    return I(rnd.mul_down(xl, xl), rnd.mul_up(xu, xu), true);
  else
    return I(static_cast<T>(0), (-xl > xu ? rnd.mul_up(xl, xl) : rnd.mul_up(xu, xu)), true);
}

namespace interval_lib {
namespace detail {

template< class I > inline
I root_aux(typename I::base_type const &x, int k) // x and k are bigger than one
{
  typedef typename I::base_type T;
  T tk(k);
  I y(static_cast<T>(1), x, true);
  for(;;) {
    T y0 = median(y);
    I yy = intersect(y, y0 - (pow(I(y0, y0, true), k) - x) / (tk * pow(y, k - 1)));
    if (equal(y, yy)) return y;
    y = yy;
  }
}

template< class I > inline // x is positive and k bigger than one
typename I::base_type root_aux_dn(typename I::base_type const &x, int k)
{
  typedef typename I::base_type T;
  typedef typename I::traits_type Policies;
  typename Policies::rounding rnd;
  T one(1);
  if (x > one) return root_aux<I>(x, k).lower();
  if (x == one) return one;
  return rnd.div_down(one, root_aux<I>(rnd.div_up(one, x), k).upper());
}

template< class I > inline // x is positive and k bigger than one
typename I::base_type root_aux_up(typename I::base_type const &x, int k)
{
  typedef typename I::base_type T;
  typedef typename I::traits_type Policies;
  typename Policies::rounding rnd;
  T one(1);
  if (x > one) return root_aux<I>(x, k).upper();
  if (x == one) return one;
  return rnd.div_up(one, root_aux<I>(rnd.div_down(one, x), k).lower());
}

} // namespace detail
} // namespace interval_lib

template< class T, class Policies > inline
interval<T, Policies> nth_root(interval<T, Policies> const &x, int k)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x)) return I::empty();
  assert(k > 0);
  if (k == 1) return x;
  typename Policies::rounding rnd;
  typedef typename interval_lib::unprotect<I>::type R;
  if (!interval_lib::user::is_pos(x.upper())) {
    if (interval_lib::user::is_zero(x.upper())) {
      T zero(0);
      if (!(k & 1) || interval_lib::user::is_zero(x.lower())) // [-1,0]^/2 or [0,0]
        return I(zero, zero, true);
      else               // [-1,0]^/3
        return I(-interval_lib::detail::root_aux_up<R>(-x.lower(), k), zero, true);
    } else if (!(k & 1)) // [-2,-1]^/2
      return I::empty();
    else {               // [-2,-1]^/3
      return I(-interval_lib::detail::root_aux_up<R>(-x.lower(), k),
               -interval_lib::detail::root_aux_dn<R>(-x.upper(), k), true);
    }
  }
  T u = interval_lib::detail::root_aux_up<R>(x.upper(), k);
  if (!interval_lib::user::is_pos(x.lower()))
    if (!(k & 1) || interval_lib::user::is_zero(x.lower())) // [-1,1]^/2 or [0,1]
      return I(static_cast<T>(0), u, true);
    else                 // [-1,1]^/3
      return I(-interval_lib::detail::root_aux_up<R>(-x.lower(), k), u, true);
  else                   // [1,2]
    return I(interval_lib::detail::root_aux_dn<R>(x.lower(), k), u, true);
}

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_ARITH2_HPP

/* arith2.hpp
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
*/