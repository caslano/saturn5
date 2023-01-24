/* Boost interval/detail/test_input.hpp file
 *
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_TEST_INPUT_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_TEST_INPUT_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {
namespace user {

template<class T> inline
bool is_zero(T const &v) { return v == static_cast<T>(0); }

template<class T> inline
bool is_neg (T const &v) { return v <  static_cast<T>(0); }

template<class T> inline
bool is_pos (T const &v) { return v >  static_cast<T>(0); }

} // namespace user

namespace detail {

template<class T, class Policies> inline
bool test_input(const interval<T, Policies>& x) {
  typedef typename Policies::checking checking;
  return checking::is_empty(x.lower(), x.upper());
}

template<class T, class Policies1, class Policies2> inline
bool test_input(const interval<T, Policies1>& x, const interval<T, Policies2>& y) {
  typedef typename Policies1::checking checking1;
  typedef typename Policies2::checking checking2;
  return checking1::is_empty(x.lower(), x.upper()) ||
         checking2::is_empty(y.lower(), y.upper());
}

template<class T, class Policies> inline
bool test_input(const T& x, const interval<T, Policies>& y) {
  typedef typename Policies::checking checking;
  return checking::is_nan(x) || checking::is_empty(y.lower(), y.upper());
}

template<class T, class Policies> inline
bool test_input(const interval<T, Policies>& x, const T& y) {
  typedef typename Policies::checking checking;
  return checking::is_empty(x.lower(), x.upper()) || checking::is_nan(y);
}

template<class T, class Policies> inline
bool test_input(const T& x) {
  typedef typename Policies::checking checking;
  return checking::is_nan(x);
}

template<class T, class Policies> inline
bool test_input(const T& x, const T& y) {
  typedef typename Policies::checking checking;
  return checking::is_nan(x) || checking::is_nan(y);
}

} // namespace detail
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_TEST_INPUT_HPP

/* test_input.hpp
83dBcOcWxhDcFdAmgVvN4aLAutO37zxt+5r9lFcMyPujYwZk+7uig09jOojzC1ChTN6bYx+o6/nnze7rY3OsXpbyLa+8S3zBG8r61qRVOS+e+X1MljY2nxvbUrTuUue+mwz2q58doKpvX4LZFETDsgwFKDOjA9xZPQfDiOAyiGznRpZSMTKcUkPXIVCMJa2CWdzOipkHIuMcWlljYISjEXQKRH84JrBJuDGccj1dhzDnpV6W6kDkQh+bZWW/aDWAzs/x6PxsYhZn68xvI3RmZqRVCidmoWJWHHb4wo9a6ehxpx6WjJgacXo567YSzIc3NDQvwzS7S7WUZY44QvN6mwJX0B6P+mkXKitE42ZhE3qTBpGNdRWrC7JMMYUqJ+k5dIDX/XZtTO0QQRHApZMm9YsWs+Ych/syqY7VngKziQ5JNz0rDA+ZqoJS3bsCnsgukEz32QlvuC+YWgMazSLtOJop5QgCAb2KjpTOfVhWxpOfKxfX4TqMNSprCdwB6grcNePOj2Lv2hMtIni5iEphY2ejClAFQfaf0b7+ZkzB6xlruKudlL3QlmJiEoD751eDfkEC4W9XkcJRdbXIKT1eVw5gZpLGXBKt2eOlco9uvuMaTYmIsGwcIRC3Cj+PJqSkVpghvKrwl5tD6ctDl+kzEq2EUloRuNydf+2sLP1ONu5hXnsjwNbTG07cYVSv1LpEtuIYUL83jiD1jz9y
*/