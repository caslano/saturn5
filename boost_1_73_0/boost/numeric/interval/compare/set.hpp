/* Boost interval/compare/set.hpp template implementation file
 *
 * Copyright 2002-2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/numeric/interval/utility.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace set {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return proper_subset(x, y);
}

template<class T, class Policies> inline
bool operator<(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return subset(x, y);
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return proper_subset(y, x);
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return subset(y, x);
}

template<class T, class Policies> inline
bool operator>=(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return equal(y, x);
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return !equal(y, x);
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& , const T& )
{
  throw comparison_error();
}

} // namespace set
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_COMPARE_SET_HPP

/* set.hpp
9ysp618x3ifpledTR9u8dKnMr1pF/LzDi5eb+J3ufT6+cJWJY4d+en3w/CJl/XyjibdA9PtNJs5j9rHwA1n/ED6era9vNjHd8L6fPX6r2L/MfhB+FLsfX/gO5P0ZpdtM3Mrur/iaicft89kjq9j/8bvFvrf7T50z/ynvP7lH8mcCc3zl8u26SFn/f9vERnY+9QGz//0pwTJ/5UTl/t8HTUy2uFbmoxaWefq7Jh4i+9Pxh8Q+
*/