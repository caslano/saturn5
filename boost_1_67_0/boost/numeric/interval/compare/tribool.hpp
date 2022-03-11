/* Boost interval/compare/tribool.hpp template implementation file
 *
 * Copyright 2002-2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_TRIBOOL_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_TRIBOOL_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>
#include <boost/logic/tribool.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace compare {
namespace tribool {

template<class T, class Policies1, class Policies2> inline
logic::tribool operator<(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y.lower()) return true;
  if (x.lower() >= y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator<(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y) return true;
  if (x.lower() >= y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator<=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() <= y.lower()) return true;
  if (x.lower() > y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator<=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() <= y) return true;
  if (x.lower() > y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator>(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() > y.upper()) return true;
  if (x.upper() <= y.lower()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator>(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() > y) return true;
  if (x.upper() <= y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator>=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() >= y.upper()) return true;
  if (x.upper() < y.lower()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator>=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.lower() >= y) return true;
  if (x.upper() < y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator==(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() == y.lower() && x.lower() == y.upper()) return true;
  if (x.upper() < y.lower() || x.lower() > y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator==(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() == y && x.lower() == y) return true;
  if (x.upper() < y || x.lower() > y) return false;
  return logic::indeterminate;
}

template<class T, class Policies1, class Policies2> inline
logic::tribool operator!=(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y.lower() || x.lower() > y.upper()) return true;
  if (x.upper() == y.lower() && x.lower() == y.upper()) return false;
  return logic::indeterminate;
}

template<class T, class Policies> inline
logic::tribool operator!=(const interval<T, Policies>& x, const T& y)
{
  if (detail::test_input(x, y)) throw comparison_error();
  if (x.upper() < y || x.lower() > y) return true;
  if (x.upper() == y && x.lower() == y) return false;
  return logic::indeterminate;
}

} // namespace tribool
} // namespace compare
} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_COMPARE_TRIBOOL_HPP

/* tribool.hpp
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
*/