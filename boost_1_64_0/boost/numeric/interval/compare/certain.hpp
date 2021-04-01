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
btpCA+INrx9/oafXkrwNrCiBzHeJk7YMsXMjQVVBejKjOF98Bi833m5TAQtr8IsL4sVmrenOVDSSFizb80t4qmulSgD49OkNsMuBpPLXMctO9UtzZu5bhBVvcu/2zMIlMdYipIEgNycL9+FM4VWMgRI5w9fbNRYOCpwGDeL+Lt1PW8F6rul1x90+XHQoGiqyGf4a5VXpqb/UGg/rz+wDpZNrN3l1v7L9jnT/+rTBNcoprCi5UHOuXMUAT+JRu9lYsUvyb5giEXyPP0I+WjVNYLFo/dBr4786j6xew0X1WZ02awRyw2J3VV8EFlALKPYk5NpA93bMPyaz8+P6yzQj0+lBH02NARlU/+xtQ7MkNN7ef5ibj0bo+oaFcAWDaA+/Jxrxw0e9BOS2by3cONxxqpjbStvq1tRYABTIbiwYlAwQwtqCl+e2Vyy4faeB/impj9s0sBuvcO8BNYII7TAvuyahcN3tn0nbdEel4kDtz6GS4GqnPLZzdtWKnvMs2SMe+ZPTCWyn7DBOTkW2c6RHZwJCkjGV0d87uW54EKZw0FI+n3g3LeXQ/gUl4g==
*/