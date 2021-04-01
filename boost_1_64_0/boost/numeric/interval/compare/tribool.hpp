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
XwYczsIvMTQY7+YdXkuP8uissno+U2GB9sPmCWqx74rR+jzj5MYHlDv96AKn4XXC6A3hHN6yU13gxArHK8NfEVyauyLzKSx/eO8oNdR9n4pFz2vP0hQBrL2ze8MXProg0jtwXZPTh/X8D0XlwYwurrywa8YlJYOi4VqFEeh7pgiPDcZopTvOK+ZTYfnqfAEYgJeJpdwW7o8RbGJSIl5jC/fJPINHP87qvWe58dPaFuU7rrpxM2dsqReCIYl19YFV6O5U1NQwXdXWT2FzrLVuIPHrM2clMnuTt7VrLfJKiU6A2cVBGdkdaSl56B/hEgvPlWI7EsxEQyliFLDwAtDsgcGU5fAZv/SyTQEhXpIQnJZb2P4tMyJt+OurnHm+F7CGiLg+DL3TRTAwWdTqaJcb//iKIzuhSKMXQYCBKyaq17AQJSTIf7G7OPmNPu2VCNA5Gl1gwfjV98gL8F68wyX7vRL8YJ+D0XwUgtXuUdrabGnJVIP/ucALAEuDE10Kn4RmXzIKCedv6NhjkB6pndQLyzMB5lSOjOkI3Xbj9aNGtYUQSMwhwQKRacm3gA==
*/