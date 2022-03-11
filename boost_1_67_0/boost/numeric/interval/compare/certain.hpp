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