/* Boost interval/compare/certain.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_CERTAIN_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_CERTAIN_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace certain {

template<class T, class Policies1, class Policies2> inline
bool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y.lower();
}

template<class T, class Policies> inline
bool operator<(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y;
}

template<class T, class Policies1, class Policies2> inline
bool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() <= y.lower();
}

template<class T, class Policies> inline
bool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() <= y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() > y.upper();
}

template<class T, class Policies> inline
bool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() > y;
}

template<class T, class Policies1, class Policies2> inline
bool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.lower() >= y.upper();
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
  return x.upper() == y.lower() && x.lower() == y.upper();
}

template<class T, class Policies> inline
bool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() == y && x.lower() == y;
}

template<class T, class Policies1, class Policies2> inline
bool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y.lower() || x.lower() > y.upper();
}

template<class T, class Policies> inline
bool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  return x.upper() < y || x.lower() > y;
}

} // namespace certain
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_COMPARE_CERTAIN_HPP

/* certain.hpp
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
*/