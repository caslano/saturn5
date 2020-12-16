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
UlkLYDIO++ze8qxfX2k3MtKea7o9zEzWl7q3OPbeMBmHqGUtWSPjYKbC3NKPcE0nKO3MrmYVZxyUfpZvu64z9yqln0OmpZdk3VXamW1pYsC6q7Q72b6gEmsBTMYve2f1GvzO0Ei7nY/VtSTWApiBsMYDfxbhNwil3YJLK5lLlWAy7pE3LNpyPSjtmm/LHcv7LUzG4X3EtG88YyrtCmKTBnKtwGS+5L6efJ0xgsk4nF4cOIpnb5idsDkJYcdYX5R2ix6m7WdNhpkLC71pY8j6ovQle28ffgt6AXMTttqz3S9+PwvRjtHzMZ3iGAeYfF+nxibtWXtgMgcrzqp4hHdRmEbYxX7jPXkXVdpN9e5agusBZiPs7Z5pD3meh9kKG715IOd6BkzGz2jPpjmca5iFsO2V97HWpSjtqoW1qcb1AJMxav+tfS6/rcFKCvs20aQh97jG2u/r0f52MmsITL4vwuD5Ke5xMPm+WzZHF3HOYPJ9XxYWZ10aqfzmmpChazgvSl9SOzeaxHMrzF5YouEW3o/2wcxljHIvFn77hRkLS3r6sC/rNcxbWJ1yg47zG24TrT0OsfbguvVuopwLdo99xzUNMxSWETDfn2sa5i3bjb9nxvoJsxaWsDThA9cmzEFYdy9b9mUVTF/Y3TVuP/n3KpifsIeWI+2YEzCNHN/gd/u5/mAVhfWcMY5117epdq1rbhHTifsKTL7vcINzL/m3cqVdyJfC+1g/mHxfg0tOTZnzMFuZE6EaU95JYHIMVkVHGTC2MDdh1685ZbLOwzyFmda/xNrqGao9n58/1ZvOscPcZD/LB8fw3gEzEWa+byLrZ3uYfF+M1bhJjC3MVFjjojEZ3BuV90VERVqw7sLk2EMnT/7EeYFZCPOfddCPcYeZyfhVsX/IuMOs5fgmt1zH9dBM++9qi64b/ubeCPMRdr70iqbMCaXdC6cf77lWlHbbRvru5j4Gk+MbFJOUxNoKk/1MG/GK7WbALIVd+hCrz7UCcxB2OnHDFdYQmKGw+pYLWbOOKv0s8dikCr+RwWyEvXx4vYDz0lz7PyN/tkr0II4dZiDsWKJNCusErIKwgtRW/Vk/lXZlLTYfZi7BZD+djjUL4DqCybzeGTbJg7kEk/V6aAu7uzwvwWR+fjwWtp3nVuV9dxZ0MeQ6aqF848za35HrCCbft8O1Wj7XitLukuGNaswJmJOwxIwDQzh2pd3JcL/qzAmlne7HAcd4xoTJuLeJ+ci70w6YmzA7k+0ZrC8wM61vOgsTOGcwF2HFvi0fy5xoqZ3XD4otP8m7E8xLWNijnknMCaXdRsukd6w9MD1Zs2485hprCZP9vLquzAfOJ0xf1p6q6+9zP1LeF18uMp45CJNz/endte6Mg/I+/SsrdFjPYJbCRm2ed5R7ldLOY8/8G8xPmKOwwaYulXnWh1kJ296y/SXGAWYh7D/p/vbcA5R2phNn/+AZs5V2nRhzwuMf5i5Mtut8XG86Y9RK+Zvi4ng7xghmKyy5Z7Qe90alXcb8QNaeWJiHsKDQo29Yz5R22X1+RnG9K+1O11jRm7kLk3Foan/SnHuA0u5I60kVeN9srd2u4hv9kTwTwWS7Rt45GRy70u5EpV3RzEGYnBddu9YLmGdKu0fWIyrybg+zEzY/dC3fl6S0Gzu7Z2mek2Eyl6a572ZtzVHazb775grrvNLPJlV/sE7ohWnvR/p+of14hobJdiaLp3KfrqS0MypduybnDCb7aXcmvBPXJsxY2D7L/guYLzBXmbspngd4t1DalV5azoHrD+YmLDhO14RnaJjMs+5OuZ05ZzAXYR7dXkRwjcE0wpxse97mvSNc+29uQ2/PYxx8YbKfO+w=
*/