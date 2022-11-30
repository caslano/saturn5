/* Boost interval/utility.hpp template implementation file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002-2003 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_UTILITY_HPP
#define BOOST_NUMERIC_INTERVAL_UTILITY_HPP

#include <boost/numeric/interval/utility_fwd.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/numeric/interval/detail/bugs.hpp>
#include <algorithm>
#include <utility>

/*
 * Implementation of simple functions
 */

namespace boost {
namespace numeric {

/*
 * Utility Functions
 */

template<class T, class Policies> inline
const T& lower(const interval<T, Policies>& x)
{
  return x.lower();
}

template<class T, class Policies> inline
const T& upper(const interval<T, Policies>& x)
{
  return x.upper();
}

template<class T, class Policies> inline
T checked_lower(const interval<T, Policies>& x)
{
  if (empty(x)) {
    typedef typename Policies::checking checking;
    return checking::nan();
  }
  return x.lower();
}

template<class T, class Policies> inline
T checked_upper(const interval<T, Policies>& x)
{
  if (empty(x)) {
    typedef typename Policies::checking checking;
    return checking::nan();
  }
  return x.upper();
}

template<class T, class Policies> inline
T width(const interval<T, Policies>& x)
{
  if (interval_lib::detail::test_input(x)) return static_cast<T>(0);
  typename Policies::rounding rnd;
  return rnd.sub_up(x.upper(), x.lower());
}

template<class T, class Policies> inline
T median(const interval<T, Policies>& x)
{
  if (interval_lib::detail::test_input(x)) {
    typedef typename Policies::checking checking;
    return checking::nan();
  }
  typename Policies::rounding rnd;
  return rnd.median(x.lower(), x.upper());
}

template<class T, class Policies> inline
interval<T, Policies> widen(const interval<T, Policies>& x, const T& v)
{
  if (interval_lib::detail::test_input(x))
    return interval<T, Policies>::empty();
  typename Policies::rounding rnd;
  return interval<T, Policies>(rnd.sub_down(x.lower(), v),
                               rnd.add_up  (x.upper(), v), true);
}

/*
 * Set-like operations
 */

template<class T, class Policies> inline
bool empty(const interval<T, Policies>& x)
{
  return interval_lib::detail::test_input(x);
}

template<class T, class Policies> inline
bool zero_in(const interval<T, Policies>& x)
{
  if (interval_lib::detail::test_input(x)) return false;
  return (!interval_lib::user::is_pos(x.lower())) &&
         (!interval_lib::user::is_neg(x.upper()));
}

template<class T, class Policies> inline
bool in_zero(const interval<T, Policies>& x) // DEPRECATED
{
  return zero_in<T, Policies>(x);
}

template<class T, class Policies> inline
bool in(const T& x, const interval<T, Policies>& y)
{
  if (interval_lib::detail::test_input(x, y)) return false;
  return y.lower() <= x && x <= y.upper();
}

template<class T, class Policies> inline
bool subset(const interval<T, Policies>& x,
            const interval<T, Policies>& y)
{
  if (empty(x)) return true;
  return !empty(y) && y.lower() <= x.lower() && x.upper() <= y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool proper_subset(const interval<T, Policies1>& x,
                   const interval<T, Policies2>& y)
{
  if (empty(y)) return false;
  if (empty(x)) return true;
  return y.lower() <= x.lower() && x.upper() <= y.upper() &&
         (y.lower() != x.lower() || x.upper() != y.upper());
}

template<class T, class Policies1, class Policies2> inline
bool overlap(const interval<T, Policies1>& x,
             const interval<T, Policies2>& y)
{
  if (interval_lib::detail::test_input(x, y)) return false;
  return (x.lower() <= y.lower() && y.lower() <= x.upper()) ||
         (y.lower() <= x.lower() && x.lower() <= y.upper());
}

template<class T, class Policies> inline
bool singleton(const interval<T, Policies>& x)
{
 return !empty(x) && x.lower() == x.upper();
}

template<class T, class Policies1, class Policies2> inline
bool equal(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (empty(x)) return empty(y);
  return !empty(y) && x.lower() == y.lower() && x.upper() == y.upper();
}

template<class T, class Policies> inline
interval<T, Policies> intersect(const interval<T, Policies>& x,
                                const interval<T, Policies>& y)
{
  BOOST_USING_STD_MIN();
  BOOST_USING_STD_MAX();
  if (interval_lib::detail::test_input(x, y))
    return interval<T, Policies>::empty();
  const T& l = max BOOST_PREVENT_MACRO_SUBSTITUTION(x.lower(), y.lower());
  const T& u = min BOOST_PREVENT_MACRO_SUBSTITUTION(x.upper(), y.upper());
  if (l <= u) return interval<T, Policies>(l, u, true);
  else        return interval<T, Policies>::empty();
}

template<class T, class Policies> inline
interval<T, Policies> hull(const interval<T, Policies>& x,
                           const interval<T, Policies>& y)
{
  BOOST_USING_STD_MIN();
  BOOST_USING_STD_MAX();
  bool bad_x = interval_lib::detail::test_input(x);
  bool bad_y = interval_lib::detail::test_input(y);
  if (bad_x)
    if (bad_y) return interval<T, Policies>::empty();
    else       return y;
  else
    if (bad_y) return x;
  return interval<T, Policies>(min BOOST_PREVENT_MACRO_SUBSTITUTION(x.lower(), y.lower()),
                               max BOOST_PREVENT_MACRO_SUBSTITUTION(x.upper(), y.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> hull(const interval<T, Policies>& x, const T& y)
{
  BOOST_USING_STD_MIN();
  BOOST_USING_STD_MAX();
  bool bad_x = interval_lib::detail::test_input(x);
  bool bad_y = interval_lib::detail::test_input<T, Policies>(y);
  if (bad_y)
    if (bad_x) return interval<T, Policies>::empty();
    else       return x;
  else
    if (bad_x) return interval<T, Policies>(y, y, true);
  return interval<T, Policies>(min BOOST_PREVENT_MACRO_SUBSTITUTION(x.lower(), y),
                               max BOOST_PREVENT_MACRO_SUBSTITUTION(x.upper(), y), true);
}

template<class T, class Policies> inline
interval<T, Policies> hull(const T& x, const interval<T, Policies>& y)
{
  BOOST_USING_STD_MIN();
  BOOST_USING_STD_MAX();
  bool bad_x = interval_lib::detail::test_input<T, Policies>(x);
  bool bad_y = interval_lib::detail::test_input(y);
  if (bad_x)
    if (bad_y) return interval<T, Policies>::empty();
    else       return y;
  else
    if (bad_y) return interval<T, Policies>(x, x, true);
  return interval<T, Policies>(min BOOST_PREVENT_MACRO_SUBSTITUTION(x, y.lower()),
                               max BOOST_PREVENT_MACRO_SUBSTITUTION(x, y.upper()), true);
}

template<class T> inline
interval<T> hull(const T& x, const T& y)
{
  return interval<T>::hull(x, y);
}

template<class T, class Policies> inline
std::pair<interval<T, Policies>, interval<T, Policies> >
bisect(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x))
    return std::pair<I,I>(I::empty(), I::empty());
  const T m = median(x);
  return std::pair<I,I>(I(x.lower(), m, true), I(m, x.upper(), true));
}

/*
 * Elementary functions
 */

template<class T, class Policies> inline
T norm(const interval<T, Policies>& x)
{
  if (interval_lib::detail::test_input(x)) {
    typedef typename Policies::checking checking;
    return checking::nan();
  }
  BOOST_USING_STD_MAX();
  return max BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<T>(-x.lower()), x.upper());
}

template<class T, class Policies> inline
interval<T, Policies> abs(const interval<T, Policies>& x)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x))
    return I::empty();
  if (!interval_lib::user::is_neg(x.lower())) return x;
  if (!interval_lib::user::is_pos(x.upper())) return -x;
  BOOST_USING_STD_MAX();
  return I(static_cast<T>(0), max BOOST_PREVENT_MACRO_SUBSTITUTION(static_cast<T>(-x.lower()), x.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> max BOOST_PREVENT_MACRO_SUBSTITUTION (const interval<T, Policies>& x,
                                                            const interval<T, Policies>& y)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x, y))
    return I::empty();
  BOOST_USING_STD_MAX();
  return I(max BOOST_PREVENT_MACRO_SUBSTITUTION(x.lower(), y.lower()), max BOOST_PREVENT_MACRO_SUBSTITUTION(x.upper(), y.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> max BOOST_PREVENT_MACRO_SUBSTITUTION (const interval<T, Policies>& x, const T& y)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x, y))
    return I::empty();
  BOOST_USING_STD_MAX();
  return I(max BOOST_PREVENT_MACRO_SUBSTITUTION(x.lower(), y), max BOOST_PREVENT_MACRO_SUBSTITUTION(x.upper(), y), true);
}

template<class T, class Policies> inline
interval<T, Policies> max BOOST_PREVENT_MACRO_SUBSTITUTION (const T& x, const interval<T, Policies>& y)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x, y))
    return I::empty();
  BOOST_USING_STD_MAX();
  return I(max BOOST_PREVENT_MACRO_SUBSTITUTION(x, y.lower()), max BOOST_PREVENT_MACRO_SUBSTITUTION(x, y.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> min BOOST_PREVENT_MACRO_SUBSTITUTION (const interval<T, Policies>& x,
                                                            const interval<T, Policies>& y)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x, y))
    return I::empty();
  BOOST_USING_STD_MIN();
  return I(min BOOST_PREVENT_MACRO_SUBSTITUTION(x.lower(), y.lower()), min BOOST_PREVENT_MACRO_SUBSTITUTION(x.upper(), y.upper()), true);
}

template<class T, class Policies> inline
interval<T, Policies> min BOOST_PREVENT_MACRO_SUBSTITUTION (const interval<T, Policies>& x, const T& y)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x, y))
    return I::empty();
  BOOST_USING_STD_MIN();
  return I(min BOOST_PREVENT_MACRO_SUBSTITUTION(x.lower(), y), min BOOST_PREVENT_MACRO_SUBSTITUTION(x.upper(), y), true);
}

template<class T, class Policies> inline
interval<T, Policies> min BOOST_PREVENT_MACRO_SUBSTITUTION (const T& x, const interval<T, Policies>& y)
{
  typedef interval<T, Policies> I;
  if (interval_lib::detail::test_input(x, y))
    return I::empty();
  BOOST_USING_STD_MIN();
  return I(min BOOST_PREVENT_MACRO_SUBSTITUTION(x, y.lower()), min BOOST_PREVENT_MACRO_SUBSTITUTION(x, y.upper()), true);
}

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_UTILITY_HPP

/* utility.hpp
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
*/