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
8CvYdHsidt0qC2dW4dnTtrY2pP0yzoXluLtiWdjkSiIfXnY9rmu8KkuVlyOw37uKVwvy52VX9TPuxav7mfWya4tMfPHKvE9k1sQ4JgEZ0/HlwIU+kdQUTyrmaHn9Ll6N5+/Lrsdy/cUrBln9suv6eQDj1fkeT07lv1+c905Zo4hLm0En3XoNL5b9aqhhQix74ZHDn9kPa+HhL0x1Fu3cPA0Wi65xp5mVJVJR6vNRXZ2UjQ8CmRazDQJ9PM3ZgXjSXs4ISslMw3rWfI4nUNjZFMxLQTRehjuYIhq7n0LEuWlHExtSnupPnzqbdp08qz8LsxPSMC2hn/AQiOkL+0CUBrkvX/EUl0EZ2j5R+EWbLSgvFcUiPyPPkNgKEjTylmNt0P1iGSOsOXEM0G6szVxKbMs1POML9XddQ05MhMyKFSzPS7e/8pSFYBJzy9cCNTXvWL5IUQJGapNDMKCra+aYV6nUfnr96f8O7w7ZZ/1OdMU6EVgCm8opT+8xU+th4CCZBQ4wxRRpBdQi8R7LrDrBdB9sVR3AVtygqLnAE94w6yNLnygBETkfUTBK8lMfBXoxRD8nxsxWQKOQd3P+2/nFh3Oex/RZzX0WCN0K2jw6WnHiqASmkXgvIjk1XZ5TEzH5k40bTaaJL8x/GeGO
*/