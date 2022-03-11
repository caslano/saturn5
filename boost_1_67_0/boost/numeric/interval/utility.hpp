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