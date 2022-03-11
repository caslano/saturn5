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