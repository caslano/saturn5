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