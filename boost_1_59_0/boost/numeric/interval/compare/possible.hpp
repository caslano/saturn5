/* Boost interval/compare/possible.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_POSSIBLE_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_POSSIBLE_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace possible {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() < y.upper();
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
  return x.lower() <= y.upper();
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() > y.lower();
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() > y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() >= y.lower();
}

template<class T, class Policies> inline
bool operator>=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() >= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y.upper() && x.upper() >= y.lower();
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() <= y && x.upper() >= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y.upper() || x.upper() != y.lower();
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() != y || x.upper() != y;
}

} // namespace possible
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_COMPARE_POSSIBLE_HPP

/* possible.hpp
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
*/