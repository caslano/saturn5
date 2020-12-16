/* Boost interval/hw_rounding.hpp template implementation file
 *
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 * Copyright 2005 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_HW_ROUNDING_HPP
#define BOOST_NUMERIC_INTERVAL_HW_ROUNDING_HPP

#include <boost/numeric/interval/rounding.hpp>
#include <boost/numeric/interval/rounded_arith.hpp>

#define BOOST_NUMERIC_INTERVAL_NO_HARDWARE

// define appropriate specialization of rounding_control for built-in types
#if defined(__x86_64__) && (defined(__USE_ISOC99) || defined(__APPLE__))
#  include <boost/numeric/interval/detail/c99_rounding_control.hpp>
#elif defined(__i386__) || defined(_M_IX86) || defined(__BORLANDC__) || defined(_M_X64)
#  include <boost/numeric/interval/detail/x86_rounding_control.hpp>
#elif defined(__i386) && defined(__SUNPRO_CC)
#  include <boost/numeric/interval/detail/x86_rounding_control.hpp>
#elif defined(powerpc) || defined(__powerpc__) || defined(__ppc__)
#  include <boost/numeric/interval/detail/ppc_rounding_control.hpp>
#elif defined(sparc) || defined(__sparc__)
#  include <boost/numeric/interval/detail/sparc_rounding_control.hpp>
#elif defined(alpha) || defined(__alpha__)
#  include <boost/numeric/interval/detail/alpha_rounding_control.hpp>
#elif defined(ia64) || defined(__ia64) || defined(__ia64__)
#  include <boost/numeric/interval/detail/ia64_rounding_control.hpp>
#endif

#if defined(BOOST_NUMERIC_INTERVAL_NO_HARDWARE) && (defined(__USE_ISOC99) || defined(__MSL__))
#  include <boost/numeric/interval/detail/c99_rounding_control.hpp>
#endif

#if defined(BOOST_NUMERIC_INTERVAL_NO_HARDWARE)
#  undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE
#  error Boost.Numeric.Interval: Please specify rounding control mechanism.
#endif

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * Three specializations of rounded_math<T>
 */

template<>
struct rounded_math<float>
  : save_state<rounded_arith_opp<float> >
{};

template<>
struct rounded_math<double>
  : save_state<rounded_arith_opp<double> >
{};

template<>
struct rounded_math<long double>
  : save_state<rounded_arith_opp<long double> >
{};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_HW_ROUNDING_HPP

/* hw_rounding.hpp
U1vVTAttUXtcyPjYz/6oaoX9iIz3pe66NSdx3iWzYXZ0RZLy9+jCTtTr9hi5RGbFLL/O3uPYV4QtvX9jLPZpMj72hX+iI7BPi34OU+y6hlwi43GITZ9QgnnRUW03Km1AHHKJjL+vxx8zxN2PzIRZ1bju5thXyPgYbDu/y8LeIZ7ZfNNl1JdpZLyfkZEuN3COFKbbOP8w5kyModtpw2lYf2Q8ts22JZhh/Yl2hw067seZXbQLe/LwEuZMVzW2gw8vTkEukfHxZfoXdUAuCUse4tUAuUTG81N/y14L5BKZgtmtQbexB8SR8Xn565X9LHwzFu3Saps9QJ0n4+PLznBDXzJFP/uv6qKGPBPttr8txPiKRV9SF8xejznTU53ruMWJj5BnZCr3lUfBBahZZLwvAy50b488I7Pkcb+ZEII8E+2qrFrjjzwjs2amyMxUxzlEWNRKtVjcDcUzm9p6BuDeIcawz6joNc4aYuwecwr8cO8Q7W5EeK3AmU9f9ay4d3nGMex/ZA7MnrpEWCOXRLuy4731sMeRKZiFj8tDXs8m47Gd1LGZN+5qZMbM7ngtwt6fQmbDa8+IrjfxvZyMjy+p3/FmODOIZ4Zo1L2D9SesRXRz2E8yfWam5sujsDcaqPblZGQmctCNTAGj/xJue2BtkvGxp80NeYb5JDPl7xs/bgbyjIzH9mKObwzyjMyK566L4VTkmWj3bs+rebirkZkwW6oT4YgzmOjL1XynjlibZDzu25ctaYw8E/OiOe5IT5xbDVXHrtEkZRzyjIz3c9fMA8jdYDJ7ZtOy9hpjXsiMmMVldMb+PoGMxyF+6ZmW2BvJHJmt0yqPQ56JvjT8bGyGeSHjc3bwyaTrmBcyC2ZhxpaIXzEZn8/XT7y+oWYZqeagRY8RxZgzMt6X0W5vZmPOyHjc3Xv+6IeaRcbnunDuYKzN/uKZk970w5zFina/T1e1xd5IxsdnnKa+C3VeWOjDH/mo82J8x711QnHOEn2p4bu8F85Zoi8tHp1vXWn0ctV2U4fty8V5XtiBl0lNUefJrJldWVgwH78rF+3Oje+djzwj43nd471WEPZGMt7PYy0vDMb6I+Nx37vs5x/kGZkds1UZA+aizpPxOTvsa30N9YyM5+Ch/VYYQzGZJbPbIY9KUOdNVNdDzvktyCUXMj1m//QP2Yg8E3agd8hL1DMy/r50l1jkdRiZNrPcuG7fcdYXNq7qUk3MtehnjYSTTshPYRsmjHbBPYDMgZnt8ISlqHXCRmd2XIDzGRmPUYOAIsToNZkts/DgUGvsAQrVMdSuvwRzrSCrxmyjX7wufkdEZsTn+mSPnshBaYMbeWPOhB3/3SEZZzdpNVzuYn8Q5vrFpRHmTFrNDqjzicLeaq+ej9yV9rRU+W91Cvvcalk08lpa4nMt5LWwkSHP32GflrZ82Sbs02Q8P93UBvVDjExVba3zqwOorcJGH9+MfHER9mRr9UFYD2TGzHrHO3RBbIVF9+2qjK0ws1pPZiG2wgJeLp+P2JLpMMueveYC9jjRzr7HXdTW2WQGzO7n/gf1c5V45s6WiS0Qd/FM70+X4hF3MidmE5KX5qGWk5kzS9TIC8c6IuPxu/FnYyHODGRmfP3tzFyLdWSm+k0u7dKGW4gRmYKZdYvwTNwbyWx4jZwzrxPOWWS8n6c7uuCbcaR4n2tQ/n9Qe8j4fCYc7nQC5wnxvl0uX47i3ija+VZTb4azvmg38p+rbzGfol15/nPEKF+0axe0fDLWg2iXeMZzEfYAc9V2V+I0XPG9nIznxLfFjZV/Z0tY+KZ3o7AHCGthN/wVvpEJK9Jj/z60sLUPFyQgRsIaXu6J+0q4sE+lLbD++gs=
*/