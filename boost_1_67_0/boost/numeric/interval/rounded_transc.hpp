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