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
L+/lnMHk+NYv8lvJvUNpt0nXypxrDCbnMzWxlSVrltJuTPletDkwJ5nXnSancY0pfcm/tySBdQkm5/P3tWlLuG8q72v4aeIznrPaaP+tIK5O/zCusTbK3ykbryv8713D7IQ16BmwkmsMZiJs59SCxjx7w2Q/l19O9mK9hnkI03xcVJznJaXdpNpveB68B5N5fTjVcivHroxBV881kvtfW+08q7q9bQbHDpN9ufh0LfsZCpPvCxzW+hnjDpPzGZG9+y7PBcr7Mobbfudagcm8XubtcpVjV9r11VnFMZyByZxo5nzNjjUEphHWtWZx5sQPZXzHtwwdx7G3U/43x9YtZk2uBZPt0h1P5XDsMFsZv/InWHfHwuT4xifbN+S+ApP58qyK7hzWVpibjMONMl35vQcm58UmLSiPOQHzErbYxv8x62d77T11WH7XyfymA/MUljd3DP8eHgyzEZYVd+sWawFMzotVmfgpXO8wOb7h4+/yfXNgcl7Ouft34XpX+pl38SnjcBQmxxewYstL7qlKP3uvDWTu6kRoz+fEcLtJjDvMRL5vVmcD3qtgXjJGd9ync+wwO2HHetUpwf1Baefq2ng+4w5zljE6YMr1ngnTF9bU+VY93jeV9135XtOZ372Vdv5FSnzivCjve9V97gXuDx30dMrIOAwc2YZxh8nfXDN42Td+e4JZ/LVTeI5oW4vnyI4wU2FH157nGusHMxLmOPzFL55DYDbC5j1d2YM1UvnNLam2zJdEmEZY3S8Ds3m3UNr902TACOaSYhuerFjAfUX5zfOl9zXjXIs5O4mnT6rfD66jSD2dRbowneDgE/jXs3yjLJhLUfzvhP6xiMCYvjxrwHz1/9fuOP7154Phh1kje3Cu/1hCkTtHuVZg5sKG1HroxFxS2rWr0Kcbx6e0a5zZaiLHB9MIszE43It/k4IZCUszN/rK2gpzFFau4/YNnJee2r+5Yul9XZ5DYLIvORuG8W5fTWm3tUhmBHMQZi1Mf+iLvdyLYWbCXrdcy2+Og2Cmwk7UcR7LmqX85r2DD94zDspvDjBswzEkKZZ+wCyN+xjMWFhmcgd3rmmYjFFiwjDeU3MUG9Q4KpR7nDJn9a9Wecw4KJa3IceMd65e2v2ccWEZ901XmJzr8nfrcM8JUGxeWTu2qwWT/Wztu+st78UwK2FJ6zut476p2IXJ52xYC2AyRkZDyy3jeQImx5ewpmUoY6RYgw+LUxgjmKWwesbXJnGtwAyFOYW//84YKX0Z7O6+inc8xUpb1YnjvVixgohlM3g+U8ZuElDVizU5WruffXvGVWWMYDIOo5dVSWaMYPJ9wzeHVGKMYCbCqsffPcV1BLMRNq7Bt/lcRzA5n8VahdTjOlL66fqfA/wmPgUmc8L+9INSjBFMzvV3w2VZrOWKrcu/HsH4wYyE9T6yeia/XShjLzrqjgnjp7QLM2kXwzqojMHqZnHGKA/m/9f+7eC7WQ2Hsp71LhzfsX/HPsY6hXGAOQjbeKzDE841zFJYwYUqUdw3YdbChul4MT9jYVbCpvZt3pPrAWYnbH50k7K8byr9HLN5kR7rkvK+3QczG3JeYLbCMjOmVOZ5QrFiN4+W4zmrj/b7RuhcH8B7B0y+z2F/3WmcM5j8zYa7Mlhf6sOchK1N7v+WNQQm56WUxyPaSJipsJRJcVs4ZzBnYet1F01nnim278WXirx3KGNo+/rTWe6bSrtNXmuHcV5icP4UVuTCG56vvWE2wr5+bh/EdQuTY/8dMtCJ+QKzknnWRJdxGASzFNZ12PqdXJswc2H9LE9xb1yk9KX2pdNfeNaA+ci+3AtYzL0KJuMXFz2G+18+zF7mRAMnf+5HfXE=
*/