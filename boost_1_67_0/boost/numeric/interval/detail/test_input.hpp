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
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
*/