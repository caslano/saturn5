/* Boost interval/rounded_arith.hpp template implementation file
 *
 * Copyright 2002-2003 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_ROUNDED_ARITH_HPP
#define BOOST_NUMERIC_INTERVAL_ROUNDED_ARITH_HPP

#include <boost/numeric/interval/rounding.hpp>
#include <boost/numeric/interval/detail/bugs.hpp>
#include <boost/config/no_tr1/cmath.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * Three classes of rounding: exact, std, opp
 * See documentation for details.
 */

template<class T, class Rounding>
struct rounded_arith_exact: Rounding {
  void init() { }
  template<class U> T conv_down(U const &v) { return v; }
  template<class U> T conv_up  (U const &v) { return v; }
  T add_down (const T& x, const T& y) { return x + y; }
  T add_up   (const T& x, const T& y) { return x + y; }
  T sub_down (const T& x, const T& y) { return x - y; }
  T sub_up   (const T& x, const T& y) { return x - y; }
  T mul_down (const T& x, const T& y) { return x * y; }
  T mul_up   (const T& x, const T& y) { return x * y; }
  T div_down (const T& x, const T& y) { return x / y; }
  T div_up   (const T& x, const T& y) { return x / y; }
  T median   (const T& x, const T& y) { return (x + y) / 2; }
  T sqrt_down(const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); return sqrt(x); }
  T sqrt_up  (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); return sqrt(x); }
  T int_down (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(floor); return floor(x); }
  T int_up   (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(ceil); return ceil(x); }
};

template<class T, class Rounding>
struct rounded_arith_std: Rounding {
# define BOOST_DN(EXPR) this->downward();   return this->force_rounding(EXPR)
# define BOOST_NR(EXPR) this->to_nearest(); return this->force_rounding(EXPR)
# define BOOST_UP(EXPR) this->upward();     return this->force_rounding(EXPR)
  void init() { }
  template<class U> T conv_down(U const &v) { BOOST_DN(v); }
  template<class U> T conv_up  (U const &v) { BOOST_UP(v); }
  T add_down(const T& x, const T& y) { BOOST_DN(x + y); }
  T sub_down(const T& x, const T& y) { BOOST_DN(x - y); }
  T mul_down(const T& x, const T& y) { BOOST_DN(x * y); }
  T div_down(const T& x, const T& y) { BOOST_DN(x / y); }
  T add_up  (const T& x, const T& y) { BOOST_UP(x + y); }
  T sub_up  (const T& x, const T& y) { BOOST_UP(x - y); }
  T mul_up  (const T& x, const T& y) { BOOST_UP(x * y); }
  T div_up  (const T& x, const T& y) { BOOST_UP(x / y); }
  T median(const T& x, const T& y) { BOOST_NR((x + y) / 2); }
  T sqrt_down(const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_DN(sqrt(x)); }
  T sqrt_up  (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_UP(sqrt(x)); }
  T int_down(const T& x) { this->downward(); return this->to_int(x); }
  T int_up  (const T& x) { this->upward();   return this->to_int(x); }
# undef BOOST_DN
# undef BOOST_NR
# undef BOOST_UP
};
  
template<class T, class Rounding>
struct rounded_arith_opp: Rounding {
  void init() { this->upward(); }
# define BOOST_DN(EXPR) \
    this->downward(); \
    T r = this->force_rounding(EXPR); \
    this->upward(); \
    return r
# define BOOST_NR(EXPR) \
    this->to_nearest(); \
    T r = this->force_rounding(EXPR); \
    this->upward(); \
    return r
# define BOOST_UP(EXPR) return this->force_rounding(EXPR)
# define BOOST_UP_NEG(EXPR) return -this->force_rounding(EXPR)
  template<class U> T conv_down(U const &v) { BOOST_UP_NEG(-v); }
  template<class U> T conv_up  (U const &v) { BOOST_UP(v); }
  T add_down(const T& x, const T& y) { BOOST_UP_NEG((-x) - y); }
  T sub_down(const T& x, const T& y) { BOOST_UP_NEG(y - x); }
  T mul_down(const T& x, const T& y) { BOOST_UP_NEG(x * (-y)); }
  T div_down(const T& x, const T& y) { BOOST_UP_NEG(x / (-y)); }
  T add_up  (const T& x, const T& y) { BOOST_UP(x + y); }
  T sub_up  (const T& x, const T& y) { BOOST_UP(x - y); }
  T mul_up  (const T& x, const T& y) { BOOST_UP(x * y); }
  T div_up  (const T& x, const T& y) { BOOST_UP(x / y); }
  T median  (const T& x, const T& y) { BOOST_NR((x + y) / 2); }
  T sqrt_down(const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_DN(sqrt(x)); }
  T sqrt_up  (const T& x)
  { BOOST_NUMERIC_INTERVAL_using_math(sqrt); BOOST_UP(sqrt(x)); }
  T int_down(const T& x) { return -this->to_int(-x); }
  T int_up  (const T& x) { return  this->to_int(x); }
# undef BOOST_DN
# undef BOOST_NR
# undef BOOST_UP
# undef BOOST_UP_NEG
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_ROUNDED_ARITH_HPP

/* rounded_arith.hpp
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
*/