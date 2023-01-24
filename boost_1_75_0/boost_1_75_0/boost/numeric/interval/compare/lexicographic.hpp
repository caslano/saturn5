/* Boost interval/compare/lexicographic.hpp template implementation file
 *
 * Copyright 2002-2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_LEXICOGRAPHIC_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_LEXICOGRAPHIC_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace lexicographic {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl < yl || (xl == yl && x.upper() < y.upper());
}

template<class T, class Policies> inline
bool operator<(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() < y;
}

template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl < yl || (xl == yl && x.upper() <= y.upper());
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  return xl < y || (xl == y && x.upper() <= y);
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl > yl || (xl == yl && x.upper() > y.upper());
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  return xl > y || (xl == y && x.upper() > y);
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  const T& xl = x.lower();
  const T& yl = y.lower();
  return xl > yl || (xl == yl && x.upper() >= y.upper());
}

template<class T, class Policies> inline
bool operator>=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() >= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() == y.lower() && x.upper() == y.upper();
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() == y && x.upper() == y;
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y.lower() || x.upper() != y.upper();
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y || x.upper() != y;
}

} // namespace lexicographic
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_COMPARE_LEXICOGRAPHIC_HPP

/* lexicographic.hpp
TaXwpTd0Sgv8DRqeeyd2uOA2ACl1FBvUHCmnWLfIuZu6mhJKIjZgWrBkFsAow7JBx7u/QrPnglwjsYWOGz01oOO/Jgoe4vu4W2bEatcxOuiAB0EH5SkA38yEpctX8Yt0SaLoqUwjj2pUhy6WQ/kmowRi4BFZ6TE2g+KNFpv56v07zZH9hZtEXMrSx8SDvxA8d2YVYpIOcdY1jEfQMHRrKQcXax7hj7XiRx4mWzT8EBebEkzkT9AaIj50ugUk3GDGL0WhJBcddhUlIqBdnoun0ybswxeaMeiWZ+sg9yX3NhZPqRL5XJBpJd1mxCQWe0NT95pEhiE/noDaTPmKvMrY/d7w2Ab4uxf+1qLtX41rMJ9y53t4uCeBhqFbXtYoUKvtFK6/L8BzruhzwPLP3Wkj4CG6hwGVhaSVhy1Ycc2XVYwTPuwHPtG3Vunx3zx6cE0aWKl3dRdiGV0lLOnaybqPpDgNo/WEun0ItAZUC+VwUSrcyfCF/Xlg7mKeV3UWKHEOCu1p5lbp37zIMygJrGYvWkweiiRlijVyKzxcHPswjz9M/tDqAmkzGB5Pi318nv7txF4RZEb+2IcnS8g1UDYbOlUmpnlZ7yzbJ91CTV1tpWOSRGYOmS4sttKheNHWy1Z6LYFIgKMWsC6ZB+7i7dAJq630g0S8SLOVqgl4AV/gq4tPIIC2soOU8p+ntzW0JRBA5uAx9DGgujUVZiZw
*/