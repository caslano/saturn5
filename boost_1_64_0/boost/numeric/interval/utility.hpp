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
+ZGhPGMq/ezww7oh163yvtF6k3/yjLlQu589P0ff4NkGZinM7f3EFax1MNnPNodWFX4DhJX+a6vwLPlWvypzXthKPKvWrprOscMC/tq/L6rZeNJI5hmszF9bhqf13hXNmS+LCtf7UjxfXl1jw7oL8xCWXrB0HM8vMGdh+Y73yzC2MHthH97t68s1BjMXllzeuQhrK8xJmEsnZ+5x12G2wn5XODqJ44NZCQue+MiDd7zF2AOEZTwtMZwxgrkIm/vsxEqeUWCmwrb2ybTnuQ4m33d3fvfnrHUwS2Ga0YOjePeFWQh7P+jbKc6Z8puPYmtwHa2CyTk7YPt4GL85wuS8vHkzNJBnYZiNsHpbQni/vaf85oPgFgc5nzCNsNE1fmWyLsGshdU11rC+2C7Rfp9/m76MXwBMxmFG/c/tmfMwOfapnTQ1uL/D5Psapq+sxflU2unMyJ/P+YTJuV64tlwXzidMxnbQkI8/OJ8wmbuv1t9I5jlSsSd5OcyzPJiDsDXx15cwB5dqtxvv+SmDOajYd/1DE3nfhJkJSyp7uCLnDCbf97O+H/OlB8xJ2PVZBuznFJiF1lw37s2zIsxRjiHA0JBrE+Yv7NqjBUmsn0pfRhSfyJqst0w77rufWX/heVCx+EoJ5bn+YHIMHTu8fMOcgLkLa7f2Ti5rJMxLmMmJvpzPJJic63JDgn5xrcB8hK2d4cA7ST7MWdjGefd9eM5arj32R72ef2LOwyxkvlTd8IS1FWYn+9lveuGZFuYrbMlcrxyeW2EuwuJiT5Ri7ip9afCzxUvmLkzO2ZbKyzlnr2C2wiYlPt7A+K3QXn+PzpeczdyFyXwx1ixpwdyF2Qhb8COUtaAlzEpYaPXjhbm7onBeFuMZGVIyg7GF+Qub8PjLHO5/sJA/FvzHShTdfI8xWomzhrDF5pumcQwrC2vBQjzHHXLzZPxglsLSTMY/ZfxgHf/+ZjyePutCuK/sgBkJO+Eanc1z5MrC763z8MwfMYx3p6Mwa2Htsube5jkSZiIsqcS9bqw9MEdhvqnlIlh7ViHnhek+6D2TY4fJvuS+HtaOaxOmL+x7ugdrpC9Mp8j/7h2z8a/7xhg+Ye6uLuzndDyHltPc55kBZixsdNz0gTwrwpCQf35zCp4l4xYfYs1aw1z6YzOW2zxmLYcFCFtnfH4Mz3wwB2Ft671yZs7DjIW9f5z9gWc+mKWwHPGfIdesxXwKy+8XUpLzApO/2apL4GDe42AmwqKNsgKYSzArYTVHfed8hsOMhNm8NFjMs4ZiTdoEL+W9CmYqLHPGirH8XqDY0yr3xrO+wMyEGZWYvppzDXMR5tlxbWPmtTKGp8OunWMcYBbCDlXtd565q7Tbmelal3GAGQrzXbZpNPM6UXvsNZbU3sIYwZyEHc8cwPcFwGRsJz87ZME4wOTY7dvmvmfNglkLO5MQfJd5rbQrWUaziXkNM/r77X4y/nXEDcsh3DfX8/8X/4/5NRz/nfmp2OO1sxy5Hym2IXU+z9AfYfrC0ue3rsqzm2LTvidUYZ3foG3BH+b7cj5hVsKKtHu2inUCZiqsqqXdAN5zYGbCLtjta8u5hlkIm3n24BXmPMxYmNVz+wbMeZhGWJ9cDc9ngxQ7vsbhOvcOmKWwlktur+F9E1bqr03CM6t+8lDumzD/vzYRz+kNG7bmfIp5mfBvX2Y+03DP2YixCxvX8aQ/5wxmIWz171UrWSdgtsIi5r1mLoXCzIVNjtr9mXUXZi3Mf+UK7h2xSrsODX66srbCLIVN29w7j+dBmIOw3Lo9+vI8qLSbs+RBU84ZzEaYa6UI3t9zlb4M/FW6MfMaJufzWsHvPczPTdrv29DInd88HBU=
*/