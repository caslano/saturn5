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
u+mfZpyMLhKnWPw1ZNCc98jm8OVX1A20VH8mYQTF+XOAEc/IgR3tyHe/cghlfQB66w7bI+s0WCXS9+3PjejzomFEongwFiyZ64Lv5tBjDpTLT1tnyBJjukydmhT9Oi+nmzXu19D9E+RL0pSc5JRfLayXPVlxFzpKVl9XFScNBe5qjeTfNxzY0VG6qwhHU+JQN5ahfFoNuPNr70g2jhC+PnBUu+YF4yklDq0+BljoI/I2Qoq6MHCLrV6JM//o2lFqpx4FJS8nDiW0mYdDdBInb9GedmW7WeWqisUICKbu3MJHKJ5D0ObEtITZNjBXyZe4WEgY+vWQbMPSE9L+2yQcIfSz5oKthHam9ikXSaidpz7PI6WdNfdk/HYG3MesbidDx25wNdThC1WQImRwFHWEAu3/PxIVeQjb/ZRmT4PQnKp1A9cI0R7lJEzuW/5Ij8TwxQT2gG33AtaapYSIODGa7EyAs65XOL+HulRb1bbq7rMEVzBTuTYGDkW1asUoUH75lp87Cv5wiKHkE0m5lywDfTLhyop7VXc6N5TIFFK2zHCHTrgNCNcvxtSR5A==
*/