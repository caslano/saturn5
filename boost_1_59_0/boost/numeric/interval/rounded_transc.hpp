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
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
*/