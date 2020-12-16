/* Boost interval/detail/x86_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_X86_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_X86_ROUNDING_CONTROL_HPP

#ifdef __GNUC__
#  include <boost/numeric/interval/detail/x86gcc_rounding_control.hpp>
#elif defined(__BORLANDC__)
#  include <boost/numeric/interval/detail/bcc_rounding_control.hpp>
#elif defined(_MSC_VER)
#  include <boost/numeric/interval/detail/msvc_rounding_control.hpp>
#elif defined(__MWERKS__) || defined(__ICC) || defined (__SUNPRO_CC)
#  define BOOST_NUMERIC_INTERVAL_USE_C99_SUBSYSTEM
#  include <boost/numeric/interval/detail/c99sub_rounding_control.hpp>
#else
#  error Unsupported C++ compiler.
#endif

namespace boost {
namespace numeric {
namespace interval_lib {

namespace detail {

#ifdef BOOST_NUMERIC_INTERVAL_USE_C99_SUBSYSTEM
typedef c99_rounding_control x86_rounding_control;
#undef BOOST_NUMERIC_INTERVAL_USE_C99_SUBSYSTEM
#else
struct fpu_rounding_modes
{
  unsigned short to_nearest;
  unsigned short downward;
  unsigned short upward;
  unsigned short toward_zero;
};

// exceptions masked, extended precision
// hardware default is 0x037f (0x1000 only has a meaning on 287)
static const fpu_rounding_modes rnd_mode = { 0x137f, 0x177f, 0x1b7f, 0x1f7f };

struct x86_rounding_control: x86_rounding
{
  static void to_nearest()  { set_rounding_mode(rnd_mode.to_nearest);  }
  static void downward()    { set_rounding_mode(rnd_mode.downward);    }
  static void upward()      { set_rounding_mode(rnd_mode.upward);      }
  static void toward_zero() { set_rounding_mode(rnd_mode.toward_zero); }
};
#endif // BOOST_NUMERIC_INTERVAL_USE_C99_SUBSYSTEM

} // namespace detail

template<>
struct rounding_control<float>: detail::x86_rounding_control
{
  static float force_rounding(const float& r) 
  { volatile float r_ = r; return r_; }
};

template<>
struct rounding_control<double>: detail::x86_rounding_control
{
  /*static double force_rounding(double r) 
  { asm volatile ("" : "+m"(r) : ); return r; }*/
  static double force_rounding(const double& r) 
  { volatile double r_ = r; return r_; }
};

namespace detail {

template<bool>
struct x86_rounding_control_long_double;

template<>
struct x86_rounding_control_long_double<false>: x86_rounding_control
{
  static long double force_rounding(long double const &r)
  { volatile long double r_ = r; return r_; }
};

template<>
struct x86_rounding_control_long_double<true>: x86_rounding_control
{
  static long double const &force_rounding(long double const &r)
  { return r; }
};

} // namespace detail

template<>
struct rounding_control<long double>:
  detail::x86_rounding_control_long_double< (sizeof(long double) >= 10) >
{};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_X86_ROUNDING_CONTROL_HPP */

/* x86_rounding_control.hpp
9Tk7/xOKuXNUM0RHODRD5PfTDOlAQXyN8Yl+TZCIM51epIs9hmRl7KWXCDCd3tlDVmNn9/IexkrNZ+yc50+h9DIkYWyaIPPueozFxVJncelgWlw4mnTDLr7UUouZBtrkKvrl7bouYbryDjiCcRswBOMKImd7mXTzGELhpilmZxt6GaYHFXo4QgmqKbLQfE0RheYHDIFw0AxRML9miIL5NUMWzK8psjh7TRHG2ed2xm+6POQstdhipmtUzZGMLy+9bHR5DNFAAUHijtDpJYNk5+1FilynlwwpL71kQHnpRcPJI4gUjmaIhp9HkA0+REd4jl6BR8WjIAhocUHXeYx8VdLZYJRdaam8pakwk912x6nAXSumcRYexZU3F3bD5Yyll/wnFGMnv0cZ0tdp4ynrUSS7yR4h70jrDsYSQsqIvE/wEjIccS868l505L2IukvGsIM9z0qhZCoXnSp+dYy18dNiNEUQm+unrzhVk8cV/JljbPbq9AKNGaQvDRccWTXMLXE//XDJNHhMpxdoKJ1e4PjWH+YK3HFFhcEjCPRbumL8XLWQA4+Hqc+xh2PuHgpJAvuly5EEaoUcwTN3xjgGj54NOUXXe5Psdnc5kt1rn5PeR5BLseK9BKHQAUN0ji7kGI+agODuWTZuY02RPLujy9g1K86kYHpio0vIG5+q8hmSZ4qEjBFTR6/PkOjbLsP4wFFAEDwxymeInnXieAF7jnlQoJ9eFhToc2RBgf7WffAhaeVsBTpCEt7pM0ThnZoisc58giAe1CeI4kG70Qdo6eFhwTNL/swrFirmleohiurWy3OMD1/8iSd4WMqfeIJ42ZAnjOsY3H1oKF/WH8a7nyFHonsHR/Ar0Ds6vX42i6m54jP2LJVNZZZPqOxmfFa0S5DVubJzYUiWA76WQVZpwaawJog2WLoMc/2vGZKNNZ9Q3N3UYAzSGxtkOr1k304TBGavTi+wRfz0u5aNl4E+AZ2WN15C+ZSdhhY3XZkGBEdW6fxerukOQ5cgG9xSGZMrmNpFOr3Eh6gJglVykL40IpwJg8MF4YTOGvsfdHrBUfLBYTxgfHEEFPsXpnbtX2jGE0OnDj7ShaJrrC984j8qpLCIBbwqWN2YP7UzoEjCVLsU80NoAUPyuNOQYjwYAkIOjxKVlsspGX9PQpcyaLzw6jKyjrF3FBTvJdlk8SmSLVKfIdki7TKMTVRNGBKPLTCEzQv3zODupn6TgAGCiKFnlbE+8RjieSgzfjQjt7vxw5M1QfL1CoND+JWsATVBtATUDMEKUKcXLJJ0etH6L1vZe8Tx3/XZp3//hWFI5w0E0wcP9RZgz6xxCOEYTRJNE7KMeyBglJ2d/UvB8XnPn4IvDNjD+BBdQBA8+r/LKJi6zn2CJAo1YAyXRkR5eG+Sw3RBNpAHgqHrUSSPcQkYg4WdzL++J+Bkh3cqmY8yUKp4FzwVa4xT3dtUwo1xKo5oUHocwRbQGGckv6eYM1Q2NYJCjkBChhzBWU+fI55nVfG0qYq+HUlT3GXFueBAqehoc5eEI4N7mCr4gCM4ZqgZ+L/xtwr4BHHtC4vn0q7pd0qEDOOFpmbAKsCXy8gE4JDgu9I0AQd0JC54zcktXhBWHgxh5T0TeMR8m67LEddFyySDR6H/lVOsVAdFUlaTSsZf39DlSB5FGapA1EjU2N6bYFETcgTxXSFHZDd5HOE5O58ke1JBwNm9OmT6lJqQ4VRFKj2bFnwtk8+QPB8qYEBujAhHmsfJm/q1NEUUk+szREuvgIKADuPvIupS8CAu4zCQgFMcNH+ylk+RSloQoAKGRGaWDsqVjrDc7sI8RKfsAg4kurguMEsEjZyveK/0nmXjgJU=
*/