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
j/dFkimYOWl0N0MNIbNitsE8APVlHRkfe+y689+x/4n36b1tifNglnhfjfcO2G9zyHjc05+O6YbaI95X84F6IXLpPH1LYOa9+3gdrE0yWz5n2avzcLcg43F36B2Msfchs2AWYZyNvJ5AxvuS4L/bG/sKGZ+z5leemqCekTkyC/x0De1ukvHcfbHfHnOdT8bnc8TW/YHYH8T7to6fjP3BMJvu4XwM3zo44D5NxvMlxdPsGNYYGY/DSkOnkcgX8czf7v0fYV8Rz9wSOjQDZz4yPoYm1TavxjrKFuvIMfAr1hEZj0P53Ut22DfJTHm+5He0x/n6gmpsjY6uRD9thJ1ept4XtYeM51Kqzp3DyBcyBbMfXXq1wRojM+BzpghPxJxdEGNI2YF9LI5Mj9nA3HjsOYvJ+Ph+Hdb/jH2TzIiZ140HSfjOLsZQaNv2OdYfGY9t1F+TFMgzYV93LjqOWk7mwmxfw2dqWGMXVWvklCExtXF2I9OstECyr6GF2phPYbM9E1/iTkKmxSxgwYhl+OZBpsss6cDrIKxbYa8aLs9DHMQzz2T4DMf+QGbIbMu+BfURIzJ9ZvFH295AjMi8me3rO+UI5lq8L6zngWE4o5D5VFozMrvElaE4e19SPrMpWWjTgi64a19StmtC5m742wd1iUzB7P68rjOwNsl6VlhQhcX9yGiF2kqmztod0Ombjb2KTJPZlZU2g5ATZLqV1pjM8+J77I26lyknmDmtPYocdCPzZTa5yfc9iJ+wiFP7RuFsc1k59kZkkc9mPsF8snYBZKfemaRgPq8orQFZ3vUIDcwnM3+yzocen8d8kv3/7yzXJxsy7EQ6zmCsnR9Zabc1MVh/rF090e4Qs7rC0tkz65DNqKl2GXWetast2pUw8xVWekWZEz5kVRzuzsf+cJXqBLM7Pj2QLy5kvN2C2BLMmR+ZETPjZXcQv2AyG/7MmwtDcD4js2MW/EkT9SyOzJqZ/Zy2b3EGI7Nnpr/GaQ7OraIvwX8GmSAnhOl9q3Ma92nRl1oOtRKQ16IvKeMSsW5trtG5jlnGOH1X5BIZf+br9JXNkNdkfF5eXbCfgVwi43Ew+d26O+oLmTGzZ+1be2JeyPj4umuqx+OsIWy1TcRczJl4n2U/p8k4h5CZMvtd4qb8dwTJFMzKQtKUdycxPs8LWdgDLK7TvsIsoG5cKvZbMgtmJxJ7TsMeQKbg8avq/xTzScbnZd7RLNzHRpEZMgvt7nEMZ1rRTrEh7T3mmozP2aAU15+Ya9EuIjMHfUkR70tYO7YJ5pqMz/Ukv9hZmGvxPitvz0LsxWTazLYVrLDHnYtMl+fZ5z6NUAtEPw8++1WCOnhDtZ/bze/GIEZkWsy872piL3Yg02FWf0MycsJN2J7C4WNwxiQz4O0MuiF3m5DxMUw8dScGcSfjYx/d4xzyrJMYw/ja21qhvgjzn3u0J/Z3Ya7507Gm48j4nF2p2l3570eK8eVGTr2GO5AYn6f9/uY474p2k5c3ao39QYx9dFD2AOSLaBfR5uAXnCdEu+y5+kuQS8KyJuwchFonzEfDyhu5JGyTj28n5JKwM7FmjyuNXkjnVmYxdzr4Yl8RFrtj73DUTzIdPmcnNAKx55Dx9x2587AQuUSmz2zN7L/f4O5LZsBje1ljA3JJWGwzRRDO7OKZrxZtDMb3FzIzZrbZL3VQQ8hMmf28WQdxiCfjuXtN7Y8T8oXMhOeuY6I/agiZO6+DwXM/I35kNswaLStDjErFM4cv37kWcbhF3yqZJZfrbcEdj4yPPans0TjMCxnvi+PBV7dwjiTTYLb0ydCVqJ9kPO4e1+cXYezifevaJ+N+tJXMkJnbiDdtcV4is+Q=
*/