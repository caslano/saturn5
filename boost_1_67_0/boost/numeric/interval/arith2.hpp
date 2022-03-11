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