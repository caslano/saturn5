/* Boost interval/detail/division.hpp file
 *
 * Copyright 2003 Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_DIVISION_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_DIVISION_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/bugs.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/numeric/interval/rounded_arith.hpp>
#include <algorithm>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

template<class T, class Policies> inline
interval<T, Policies> div_non_zero(const interval<T, Policies>& x,
                                   const interval<T, Policies>& y)
{
  // assert(!in_zero(y));
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  const T& xl = x.lower();
  const T& xu = x.upper();
  const T& yl = y.lower();
  const T& yu = y.upper();
  if (::boost::numeric::interval_lib::user::is_neg(xu))
    if (::boost::numeric::interval_lib::user::is_neg(yu))
      return I(rnd.div_down(xu, yl), rnd.div_up(xl, yu), true);
    else
      return I(rnd.div_down(xl, yl), rnd.div_up(xu, yu), true);
  else if (::boost::numeric::interval_lib::user::is_neg(xl))
    if (::boost::numeric::interval_lib::user::is_neg(yu))
      return I(rnd.div_down(xu, yu), rnd.div_up(xl, yu), true);
    else
      return I(rnd.div_down(xl, yl), rnd.div_up(xu, yl), true);
  else
    if (::boost::numeric::interval_lib::user::is_neg(yu))
      return I(rnd.div_down(xu, yu), rnd.div_up(xl, yl), true);
    else
      return I(rnd.div_down(xl, yu), rnd.div_up(xu, yl), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_non_zero(const T& x, const interval<T, Policies>& y)
{
  // assert(!in_zero(y));
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  const T& yl = y.lower();
  const T& yu = y.upper();
  if (::boost::numeric::interval_lib::user::is_neg(x))
    return I(rnd.div_down(x, yl), rnd.div_up(x, yu), true);
  else
    return I(rnd.div_down(x, yu), rnd.div_up(x, yl), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_positive(const interval<T, Policies>& x, const T& yu)
{
  // assert(::boost::numeric::interval_lib::user::is_pos(yu));
  if (::boost::numeric::interval_lib::user::is_zero(x.lower()) &&
      ::boost::numeric::interval_lib::user::is_zero(x.upper()))
    return x;
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  const T& xl = x.lower();
  const T& xu = x.upper();
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(xu))
    return I(checking::neg_inf(), rnd.div_up(xu, yu), true);
  else if (::boost::numeric::interval_lib::user::is_neg(xl))
    return I(checking::neg_inf(), checking::pos_inf(), true);
  else
    return I(rnd.div_down(xl, yu), checking::pos_inf(), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_positive(const T& x, const T& yu)
{
  // assert(::boost::numeric::interval_lib::user::is_pos(yu));
  typedef interval<T, Policies> I;
  if (::boost::numeric::interval_lib::user::is_zero(x))
    return I(static_cast<T>(0), static_cast<T>(0), true);
  typename Policies::rounding rnd;
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(x))
    return I(checking::neg_inf(), rnd.div_up(x, yu), true);
  else
    return I(rnd.div_down(x, yu), checking::pos_inf(), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_negative(const interval<T, Policies>& x, const T& yl)
{
  // assert(::boost::numeric::interval_lib::user::is_neg(yl));
  if (::boost::numeric::interval_lib::user::is_zero(x.lower()) &&
      ::boost::numeric::interval_lib::user::is_zero(x.upper()))
    return x;
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  const T& xl = x.lower();
  const T& xu = x.upper();
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(xu))
    return I(rnd.div_down(xu, yl), checking::pos_inf(), true);
  else if (::boost::numeric::interval_lib::user::is_neg(xl))
    return I(checking::neg_inf(), checking::pos_inf(), true);
  else
    return I(checking::neg_inf(), rnd.div_up(xl, yl), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_negative(const T& x, const T& yl)
{
  // assert(::boost::numeric::interval_lib::user::is_neg(yl));
  typedef interval<T, Policies> I;
  if (::boost::numeric::interval_lib::user::is_zero(x))
    return I(static_cast<T>(0), static_cast<T>(0), true);
  typename Policies::rounding rnd;
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(x))
    return I(rnd.div_down(x, yl), checking::pos_inf(), true);
  else
    return I(checking::neg_inf(), rnd.div_up(x, yl), true);
}

template<class T, class Policies> inline
interval<T, Policies> div_zero(const interval<T, Policies>& x)
{
  if (::boost::numeric::interval_lib::user::is_zero(x.lower()) &&
      ::boost::numeric::interval_lib::user::is_zero(x.upper()))
    return x;
  else return interval<T, Policies>::whole();
}

template<class T, class Policies> inline
interval<T, Policies> div_zero(const T& x)
{
  if (::boost::numeric::interval_lib::user::is_zero(x))
    return interval<T, Policies>(static_cast<T>(0), static_cast<T>(0), true);
  else return interval<T, Policies>::whole();
}

template<class T, class Policies> inline
interval<T, Policies> div_zero_part1(const interval<T, Policies>& x,
                                     const interval<T, Policies>& y, bool& b)
{
  // assert(::boost::numeric::interval_lib::user::is_neg(y.lower()) && ::boost::numeric::interval_lib::user::is_pos(y.upper()));
  if (::boost::numeric::interval_lib::user::is_zero(x.lower()) && ::boost::numeric::interval_lib::user::is_zero(x.upper()))
    { b = false; return x; }
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  const T& xl = x.lower();
  const T& xu = x.upper();
  const T& yl = y.lower();
  const T& yu = y.upper();
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(xu))
    { b = true;  return I(checking::neg_inf(), rnd.div_up(xu, yu), true); }
  else if (::boost::numeric::interval_lib::user::is_neg(xl))
    { b = false; return I(checking::neg_inf(), checking::pos_inf(), true); }
  else
    { b = true;  return I(checking::neg_inf(), rnd.div_up(xl, yl), true); }
}

template<class T, class Policies> inline
interval<T, Policies> div_zero_part2(const interval<T, Policies>& x,
                                     const interval<T, Policies>& y)
{
  // assert(::boost::numeric::interval_lib::user::is_neg(y.lower()) && ::boost::numeric::interval_lib::user::is_pos(y.upper()) && (div_zero_part1(x, y, b), b));
  typename Policies::rounding rnd;
  typedef interval<T, Policies> I;
  typedef typename Policies::checking checking;
  if (::boost::numeric::interval_lib::user::is_neg(x.upper()))
    return I(rnd.div_down(x.upper(), y.lower()), checking::pos_inf(), true);
  else
    return I(rnd.div_down(x.lower(), y.upper()), checking::pos_inf(), true);
}

} // namespace detail
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_DIVISION_HPP

/* division.hpp
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
*/