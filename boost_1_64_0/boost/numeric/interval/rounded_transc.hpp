/* Boost interval/rounded_transc.hpp template implementation file
 *
 * Copyright 2002-2003 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_ROUNDED_TRANSC_HPP
#define BOOST_NUMERIC_INTERVAL_ROUNDED_TRANSC_HPP

#include <boost/numeric/interval/rounding.hpp>
#include <boost/numeric/interval/detail/bugs.hpp>
#include <boost/config/no_tr1/cmath.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

template<class T, class Rounding>
struct rounded_transc_exact: Rounding
{
# define BOOST_NUMERIC_INTERVAL_new_func(f) \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_math(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
  BOOST_NUMERIC_INTERVAL_new_func(tanh)
# undef BOOST_NUMERIC_INTERVAL_new_func
# define BOOST_NUMERIC_INTERVAL_new_func(f) \
    T f##_down(const T& x) { BOOST_NUMERIC_INTERVAL_using_ahyp(f); return f(x); } \
    T f##_up  (const T& x) { BOOST_NUMERIC_INTERVAL_using_ahyp(f); return f(x); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
  BOOST_NUMERIC_INTERVAL_new_func(atanh)
# undef BOOST_NUMERIC_INTERVAL_new_func
};
  
template<class T, class Rounding>
struct rounded_transc_std: Rounding
{
# define BOOST_NUMERIC_INTERVAL_new_func(f) \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
  BOOST_NUMERIC_INTERVAL_new_func(tanh)
# undef BOOST_NUMERIC_INTERVAL_new_func
# define BOOST_NUMERIC_INTERVAL_new_func(f) \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->downward(); return this->force_rounding(f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->upward(); return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
  BOOST_NUMERIC_INTERVAL_new_func(atanh)
# undef BOOST_NUMERIC_INTERVAL_new_func
};

template<class T, class Rounding>
struct rounded_transc_opp: Rounding
{
# define BOOST_NUMERIC_INTERVAL_new_func(f) \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      this->downward(); T y = this->force_rounding(f(x)); \
      this->upward(); return y; } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(exp)
  BOOST_NUMERIC_INTERVAL_new_func(log)
  BOOST_NUMERIC_INTERVAL_new_func(cos)
  BOOST_NUMERIC_INTERVAL_new_func(acos)
  BOOST_NUMERIC_INTERVAL_new_func(cosh)
# undef BOOST_NUMERIC_INTERVAL_new_func
# define BOOST_NUMERIC_INTERVAL_new_func(f) \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return -this->force_rounding(-f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_math(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(sin)
  BOOST_NUMERIC_INTERVAL_new_func(tan)
  BOOST_NUMERIC_INTERVAL_new_func(asin)
  BOOST_NUMERIC_INTERVAL_new_func(atan)
  BOOST_NUMERIC_INTERVAL_new_func(sinh)
  BOOST_NUMERIC_INTERVAL_new_func(tanh)
# undef BOOST_NUMERIC_INTERVAL_new_func
# define BOOST_NUMERIC_INTERVAL_new_func(f) \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      this->downward(); T y = this->force_rounding(f(x)); \
      this->upward(); return y; } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(asinh)
  BOOST_NUMERIC_INTERVAL_new_func(atanh)
# undef BOOST_NUMERIC_INTERVAL_new_func
# define BOOST_NUMERIC_INTERVAL_new_func(f) \
    T f##_down(const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      return -this->force_rounding(-f(x)); } \
    T f##_up  (const T& x) \
    { BOOST_NUMERIC_INTERVAL_using_ahyp(f); \
      return this->force_rounding(f(x)); }
  BOOST_NUMERIC_INTERVAL_new_func(acosh)
# undef BOOST_NUMERIC_INTERVAL_new_func
};
  
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_ROUNDED_TRANSC_HPP

/* rounded_transc.hpp
QrayUZdnL2ltXXMd6TxY0f6QUmM7yhWmPZLiEp37eYLIGXeEL3TCI2pxPl3Sth4VxoBB2aJGzMDaTMh/RqkW9O4+2jj+SfX0lv/n4z3s2hIOu5gOiKHI+azUqYm9N9GYhypAY5E1bgExZa5WqZQVcHp8Cc5Fv5jghv0BZxspuFXCzMar1PxiI6w6SzNq2ln9S0m2AxZG4E680wnqpSnUgnevfOzKhm/qe3JdL53F//in0IqnoMU4VQCZKFKGGv0iJunfkrgFsr2qVC389iJc2uhz6kgTtQ/4O2JiH/PuPy0gKlZufP23IYGhYsq3eugO1ZXgNWYqFCDAIr0evTbRUHNN5taHTmSSUv1gvW9t4/FAdnhvkswbnA6JfoWqPpsikIzsSYL9qidElwIme1ELhIMXivqm91E0vkZQYChwKmNhVpolE2JDGPUDD0ujlt00EORojOBduy/408wGwtl6tek68XJDS3UvEaJv0cHnsZYOrCkSfLcIjAttTU6Jip+xaPqmvA5KKjkDAXAAnlSdvYyid1YcJwW9eX6Fd3mHotjhX/s6+M86P/VNng==
*/