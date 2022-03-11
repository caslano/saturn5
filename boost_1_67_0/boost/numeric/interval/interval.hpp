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