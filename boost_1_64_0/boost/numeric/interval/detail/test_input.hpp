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
9B5S2Ymx2AZIc5AWI70h6JAv73v0xCyvH0/M3T/2JHyPAQm8BN2ROAetwL0V5xa/6yT2B/i7YpG7TDMX+cvkRnu0Bu2ti7L4nyGVn5w734GdH8XO72LnX7PzNU7Jns8Wv4QFmUg+wmQyucp+5in+snOMh08JhvOtIU7NqV44+nrz+2b58DwV+Y+fmu9juC787E9cPwTnW59G9ORvbaeRH5LPAQd6Cz8U2FfgnueQfkYav3igf8cXB/Pvs0D31GLyc06Pv3Py/724MPmd+YbH0+Y39fTCeLac7sz3sgL5br1RY3tHKp1p7+5MpLKnmdb153S3tCbXn1Q/qX7i3PV7MpMnTtqA8hZOn7Z+Zl68M5VcP5ma091s57e2zEl09nZ0te+8dbK+M5WJinUyNTeWdGItmTZmb21sSSdau5Mp/HalOtPx1ux1sKqfF0ts1NjR2d7cGW+rndvSmsrUjgf02o0LWtLJ9gWZ2vktXZnGSRNtFjitn1g/qWHKhlPqJzZ2t1n3pbuCspk6cZpgk+jsakx09XakwmCU6Uq2tIfBKNHemcJv04LQOQqGTYn29NyWZvD1KkLJjS43ZuJzU5mueGJ+UIFY2WUmdyU6WjoK5JR1U4tbSwc80lShVGenKUnrvHhmXlCp832lsyXdHAYnu2jbUm2Jjt6mTBg82+Ktre2JMDiRKxemsFLgLWmUXbtx6c0JXpnyBZgTz6S6Msn6eVpBMNna2hZvSdcnzKQV1IEF5oXQ1dIWSoCjwiyEYb4l4Rbx1pbmdFBueWomwDMMRgvCYkQGQ8QN7nt5caM304ggHLjhy8Vg0CZSmUzXvM5UPJmJd7T4eXNbprG7o7UlPb8+USg27rOqUL1h/Y1n0pNMaRZOnbhhU8/cXlO6bl97OCGZ0nTMT2Q28CNKpZsR8DKNqaaOeBJxGQWgS5BAuTYhVppR1BtGKkvznin1hrqjTvg22dkYKAEae6ZoqKKSNHV3tdYbKmQ5WpepbE1drZm59abSZRamU13mVPNTvcZEHd2dHeZEnb4N10CatnhHxpxqfrc5DZwoAFKiJR6ESJNGHfQId2pqSZt7VDqQehheGdO0pM2dsCU9t92cKD7VmKY5lTZ3wtTCrgAOlUp3txkTJTpbk2ZEHYneQA6R6GhvNXcIeJF5YJqDNtzcJ+YE8th4psXQgBZRq7l4ccRN86ofDxJt48mkYVtlOUVXZyplTpVuTwagaosbNgcgMg8uFlEy3mVodVChK5KYZ6JW48Im68cESZKYUXSmDjEj6Oieo+9BA1qPVE+HYazIdnpbE61GNP+xd5VRClRR+M1gJ3Yrdit269qt2C2wA6vosoyAXRjHDuxW7FbsVuxW7Fbs1rWP7TdvhllU5t539Z/HPQvM7ve+eX3vfffdN6RHskVhc0PG5iWSGRSnzFpjfyZkq9UyP+b+asGVnIorq312WFYwvMFxKGswvFXcXU3tiJBTrohMRP0m7ky8Of8gn/QeLqsw/zakc9kRdvH394yGTKdQD2cJMaW6l7wNqmWJzvM5/6StpZJHcxbfS8wpDe4i5gxLjC2fkv8HTS1bAfqcXF5i/gScxcUUpyjRpz4nWxU1QVWsrqrSQVOViujBvdPwAYmEDSi5gmk/7rlzedgtlYa339NN53Yytkl7aYMmXpOAt7uxKbp7Ab9wLxSG/6lHrNezp12EhkLRz9nHTPtKcwTmm5feyHf0V9ULAZrODRrWxE/sf5iWrFrBb3qPfLkwBCOxyoq3vxWwYlo4nVG54urMjNVPSPPGhvFybYxVKexkalSFJPhpzJfwASu/2z8pYH63f5CX+bDT6U2GXW96yQrXJ3guGVOC7yFP78lv4QQ=
*/