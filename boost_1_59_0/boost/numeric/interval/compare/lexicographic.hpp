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
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
*/