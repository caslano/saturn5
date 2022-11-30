/* Boost interval/interval.hpp header file
 *
 * Copyright 2002-2003 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_INTERVAL_HPP
#define BOOST_NUMERIC_INTERVAL_INTERVAL_HPP

#include <stdexcept>
#include <string>
#include <boost/numeric/interval/detail/interval_prototype.hpp>

namespace boost {
namespace numeric {

namespace interval_lib {
    
class comparison_error
  : public std::runtime_error 
{
public:
  comparison_error()
    : std::runtime_error("boost::interval: uncertain comparison")
  { }
};

} // namespace interval_lib

/*
 * interval class
 */

template<class T, class Policies>
class interval
{
private:
  struct interval_holder;
  struct number_holder;
public:
  typedef T base_type;
  typedef Policies traits_type;

  T const &lower() const;
  T const &upper() const;

  interval();
  interval(T const &v);
  template<class T1> interval(T1 const &v);
  interval(T const &l, T const &u);
  template<class T1, class T2> interval(T1 const &l, T2 const &u);
  interval(interval<T, Policies> const &r);
  template<class Policies1> interval(interval<T, Policies1> const &r);
  template<class T1, class Policies1> interval(interval<T1, Policies1> const &r);

  interval &operator=(T const &v);
  template<class T1> interval &operator=(T1 const &v);
  interval &operator=(interval<T, Policies> const &r);
  template<class Policies1> interval &operator=(interval<T, Policies1> const &r);
  template<class T1, class Policies1> interval &operator=(interval<T1, Policies1> const &r);
 
  void assign(const T& l, const T& u);

  static interval empty();
  static interval whole();
  static interval hull(const T& x, const T& y);

  interval& operator+= (const T& r);
  interval& operator+= (const interval& r);
  interval& operator-= (const T& r);
  interval& operator-= (const interval& r);
  interval& operator*= (const T& r);
  interval& operator*= (const interval& r);
  interval& operator/= (const T& r);
  interval& operator/= (const interval& r);

  bool operator< (const interval_holder& r) const;
  bool operator> (const interval_holder& r) const;
  bool operator<= (const interval_holder& r) const;
  bool operator>= (const interval_holder& r) const;
  bool operator== (const interval_holder& r) const;
  bool operator!= (const interval_holder& r) const;

  bool operator< (const number_holder& r) const;
  bool operator> (const number_holder& r) const;
  bool operator<= (const number_holder& r) const;
  bool operator>= (const number_holder& r) const;
  bool operator== (const number_holder& r) const;
  bool operator!= (const number_holder& r) const;

  // the following is for internal use only, it is not a published interface
  // nevertheless, it's public because friends don't always work correctly.
  interval(const T& l, const T& u, bool): low(l), up(u) {}
  void set_empty();
  void set_whole();
  void set(const T& l, const T& u);

private:
  struct interval_holder {
    template<class Policies2>
    interval_holder(const interval<T, Policies2>& r)
      : low(r.lower()), up(r.upper())
    {
      typedef typename Policies2::checking checking2;
      if (checking2::is_empty(low, up))
        throw interval_lib::comparison_error();
    }

    const T& low;
    const T& up;
  };

  struct number_holder {
    number_holder(const T& r) : val(r)
    {
      typedef typename Policies::checking checking;
      if (checking::is_nan(r))
        throw interval_lib::comparison_error();
    }
    
    const T& val;
  };

  typedef typename Policies::checking checking;
  typedef typename Policies::rounding rounding;

  T low;
  T up;
};

template<class T, class Policies> inline
interval<T, Policies>::interval():
  low(static_cast<T>(0)), up(static_cast<T>(0))
{}

template<class T, class Policies> inline
interval<T, Policies>::interval(T const &v): low(v), up(v)
{
  if (checking::is_nan(v)) set_empty();
}

template<class T, class Policies> template<class T1> inline
interval<T, Policies>::interval(T1 const &v)
{
  if (checking::is_nan(v)) set_empty();
  else {
    rounding rnd;
    low = rnd.conv_down(v);
    up  = rnd.conv_up  (v);
  }
}

template<class T, class Policies> template<class T1, class T2> inline
interval<T, Policies>::interval(T1 const &l, T2 const &u)
{
  if (checking::is_nan(l) || checking::is_nan(u) || !(l <= u)) set_empty();
  else {
    rounding rnd;
    low = rnd.conv_down(l);
    up  = rnd.conv_up  (u);
  }
}

template<class T, class Policies> inline
interval<T, Policies>::interval(T const &l, T const &u): low(l), up(u)
{
  if (checking::is_nan(l) || checking::is_nan(u) || !(l <= u))
    set_empty();
}


template<class T, class Policies> inline
interval<T, Policies>::interval(interval<T, Policies> const &r): low(r.lower()), up(r.upper())
{}

template<class T, class Policies> template<class Policies1> inline
interval<T, Policies>::interval(interval<T, Policies1> const &r): low(r.lower()), up(r.upper())
{
  typedef typename Policies1::checking checking1;
  if (checking1::is_empty(r.lower(), r.upper())) set_empty();
}

template<class T, class Policies> template<class T1, class Policies1> inline
interval<T, Policies>::interval(interval<T1, Policies1> const &r)
{
  typedef typename Policies1::checking checking1;
  if (checking1::is_empty(r.lower(), r.upper())) set_empty();
  else {
    rounding rnd;
    low = rnd.conv_down(r.lower());
    up  = rnd.conv_up  (r.upper());
  }
}

template<class T, class Policies> inline
interval<T, Policies> &interval<T, Policies>::operator=(T const &v)
{
  if (checking::is_nan(v)) set_empty();
  else low = up = v;
  return *this;
}

template<class T, class Policies> template<class T1> inline
interval<T, Policies> &interval<T, Policies>::operator=(T1 const &v)
{
  if (checking::is_nan(v)) set_empty();
  else {
    rounding rnd;
    low = rnd.conv_down(v);
    up  = rnd.conv_up  (v);
  }
  return *this;
}

template<class T, class Policies> inline
interval<T, Policies> &interval<T, Policies>::operator=(interval<T, Policies> const &r)
{
  low = r.lower();
  up  = r.upper();
  return *this;
}

template<class T, class Policies> template<class Policies1> inline
interval<T, Policies> &interval<T, Policies>::operator=(interval<T, Policies1> const &r)
{
  typedef typename Policies1::checking checking1;
  if (checking1::is_empty(r.lower(), r.upper())) set_empty();
  else {
    low = r.lower();
    up  = r.upper();
  }
  return *this;
}

template<class T, class Policies> template<class T1, class Policies1> inline
interval<T, Policies> &interval<T, Policies>::operator=(interval<T1, Policies1> const &r)
{
  typedef typename Policies1::checking checking1;
  if (checking1::is_empty(r.lower(), r.upper())) set_empty();
  else {
    rounding rnd;
    low = rnd.conv_down(r.lower());
    up  = rnd.conv_up  (r.upper());
  }
  return *this;
}

template<class T, class Policies> inline
void interval<T, Policies>::assign(const T& l, const T& u)
{
  if (checking::is_nan(l) || checking::is_nan(u) || !(l <= u))
    set_empty();
  else set(l, u);
}

template<class T, class Policies> inline
void interval<T, Policies>::set(const T& l, const T& u)
{
  low = l;
  up  = u;
}

template<class T, class Policies> inline
void interval<T, Policies>::set_empty()
{
  low = checking::empty_lower();
  up  = checking::empty_upper();
}

template<class T, class Policies> inline
void interval<T, Policies>::set_whole()
{
  low = checking::neg_inf();
  up  = checking::pos_inf();
}

template<class T, class Policies> inline
interval<T, Policies> interval<T, Policies>::hull(const T& x, const T& y)
{
  bool bad_x = checking::is_nan(x);
  bool bad_y = checking::is_nan(y);
  if (bad_x)
    if (bad_y) return interval::empty();
    else       return interval(y, y, true);
  else
    if (bad_y) return interval(x, x, true);
  if (x <= y) return interval(x, y, true);
  else        return interval(y, x, true);
}

template<class T, class Policies> inline
interval<T, Policies> interval<T, Policies>::empty()
{
  return interval<T, Policies>(checking::empty_lower(),
                               checking::empty_upper(), true);
}

template<class T, class Policies> inline
interval<T, Policies> interval<T, Policies>::whole()
{
  return interval<T, Policies>(checking::neg_inf(), checking::pos_inf(), true);
}

template<class T, class Policies> inline
const T& interval<T, Policies>::lower() const
{
  return low;
}

template<class T, class Policies> inline
const T& interval<T, Policies>::upper() const
{
  return up;
}

/*
 * interval/interval comparisons
 */

template<class T, class Policies> inline
bool interval<T, Policies>::operator< (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up < r.low) return true;
    else if (low >= r.up) return false;
  }
  throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator> (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (low > r.up) return true;
    else if (up <= r.low) return false;
  }
  throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator<= (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up <= r.low) return true;
    else if (low > r.up) return false;
  }
  throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator>= (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (low >= r.up) return true;
    else if (up < r.low) return false;
  }
  throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator== (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up == r.low && low == r.up) return true;
    else if (up < r.low || low > r.up) return false;
  }
  throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator!= (const interval_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up < r.low || low > r.up) return true;
    else if (up == r.low && low == r.up) return false;
  }
  throw interval_lib::comparison_error();
}

/*
 * interval/number comparisons
 */

template<class T, class Policies> inline
bool interval<T, Policies>::operator< (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up < r.val) return true;
    else if (low >= r.val) return false;
  }
  throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator> (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (low > r.val) return true;
    else if (up <= r.val) return false;
  }
  throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator<= (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up <= r.val) return true;
    else if (low > r.val) return false;
  }
  throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator>= (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (low >= r.val) return true;
    else if (up < r.val) return false;
  }
  throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator== (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up == r.val && low == r.val) return true;
    else if (up < r.val || low > r.val) return false;
  }
  throw interval_lib::comparison_error();
}

template<class T, class Policies> inline
bool interval<T, Policies>::operator!= (const number_holder& r) const
{
  if (!checking::is_empty(low, up)) {
    if (up < r.val || low > r.val) return true;
    else if (up == r.val && low == r.val) return false;
  }
  throw interval_lib::comparison_error();
}

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_INTERVAL_HPP

/* interval.hpp
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
*/