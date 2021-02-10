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
VPfo6BCj9hcTy/KPqKqom6nkawGJccWDbeVs2eQIMul9lsbZ5GmoyB/hFNy9uX53cXV6/XHV9nA9YzZbtlXildZGmtzIbH2X9y+DR4TxWSf5SSn4XY8/OiWe8w0eWYSiOm59pj+v+EF6TvGthfkYOuI5RUbvvwJGBR5WhED+CUPsOvoTfDieJQ3oX3bf9H7pQUfqvbl4/75LdjCUj27S+s8Suolnrci3cEtIGZyJfe3urK1f7Honn/WTv+/2PvT2z6bbZ//76vrynVuHtVITUwiYnmbA+ubZtljZqCfNIwWrWnsomMmNfxOeKwT+I8oeKIOVysR//DCk650HdNT06dwoHXaNxNHULNWBWR9zR8S3ejGRg+Y9w6ffLAJLpwlxLbaYsmYjfzfYoXNmDMDQ8K3BLx0OC770ekbokYick34mqXThsyGhAVxugNgG/moK+foUpS9D5bST0LgzG9nureChZGN0yBxGcjN3J2tvOF0aerqIFHzsXSmD+cRSuN9Wbisq7kUUyD70opa3/5L89GpVgdldUi2w9e/UDg8l7SsFsivlNBk7+fR4WgWyIA47rO11a3u/1PbeKHtgbU+r7Q1re/oKeuFtDuvo9+pYFsf6Op9D2Fc/L0Npg4AtXFyqw1R5LCuL5VyIv6pZ
*/