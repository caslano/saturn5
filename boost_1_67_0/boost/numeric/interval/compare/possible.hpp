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