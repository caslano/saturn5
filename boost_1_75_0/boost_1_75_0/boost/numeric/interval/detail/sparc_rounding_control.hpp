/* Boost interval/detail/sparc_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 * The basic code in this file was kindly provided by Jeremy Siek.
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_SPARC_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_SPARC_ROUNDING_CONTROL_HPP

#if !defined(sparc) && !defined(__sparc__)
#  error This header is only intended for SPARC CPUs.
#endif

#ifdef __SUNPRO_CC
#  include <ieeefp.h>
#endif


namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

struct sparc_rounding_control
{
  typedef unsigned int rounding_mode;

  static void set_rounding_mode(const rounding_mode& mode)
  {
#   if defined(__GNUC__)
    __asm__ __volatile__("ld %0, %%fsr" : : "m"(mode));
#   elif defined (__SUNPRO_CC)
    fpsetround(fp_rnd(mode));
#   elif defined(__KCC)
    asm("sethi %hi(mode), %o1");
    asm("ld [%o1+%lo(mode)], %fsr");
#   else
#     error Unsupported compiler for Sparc rounding control.
#   endif
  }

  static void get_rounding_mode(rounding_mode& mode)
  {
#   if defined(__GNUC__)
    __asm__ __volatile__("st %%fsr, %0" : "=m"(mode));
#   elif defined (__SUNPRO_CC)
    mode = fpgetround();
#   elif defined(__KCC)
#     error KCC on Sun SPARC get_round_mode: please fix me
    asm("st %fsr, [mode]");
#   else
#     error Unsupported compiler for Sparc rounding control.
#   endif
  }

#if defined(__SUNPRO_CC)
  static void downward()    { set_rounding_mode(FP_RM); }
  static void upward()      { set_rounding_mode(FP_RP); }
  static void to_nearest()  { set_rounding_mode(FP_RN); }
  static void toward_zero() { set_rounding_mode(FP_RZ); }
#else
  static void downward()    { set_rounding_mode(0xc0000000); }
  static void upward()      { set_rounding_mode(0x80000000); }
  static void to_nearest()  { set_rounding_mode(0x00000000); }
  static void toward_zero() { set_rounding_mode(0x40000000); }
#endif
};

} // namespace detail

extern "C" {
  float rintf(float);
  double rint(double);
}

template<>
struct rounding_control<float>:
  detail::sparc_rounding_control
{
  static const float& force_rounding(const float& x) { return x; }
  static float to_int(const float& x) { return rintf(x); }
};

template<>
struct rounding_control<double>:
  detail::sparc_rounding_control
{
  static const double& force_rounding(const double& x) { return x; }
  static double to_int(const double& x) { return rint(x); }
};

template<>
struct rounding_control<long double>:
  detail::sparc_rounding_control
{
  static const long double& force_rounding(const long double& x) { return x; }
  static long double to_int(const long double& x) { return rint(x); }
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_SPARC_ROUNDING_CONTROL_HPP */

/* sparc_rounding_control.hpp
N/e8APDQ4VawG50TU4M9cKaYy0oPfoIfTXPIRQI34d6882xld+uZvkDu19JrR5rG4pYLuy2dw5zOY/aoMx3IDPW10VEgiw0gXRzIDAHkL34OZAYCuY3oYWQ2dTUuqxhT7AOZUBpSTIBZr8EY0Ebnv8Ta4LiKjnnu97PCsaAdjtd1giMG3UQSKWdWjREJvegfSHuYNYzK9s3KFWQ3pYrXGvk7tASk93keEs8OdXseJ6It4u9HeTH6jsgDhzqy8GseAXboYw9bpZKF55mCN/jxGD0q2PVqAZUCOOVn1wLjylafPobSZ3SG+gTIISOvxosfgD6JnwY+lVlPcXtSR59lUxBejM+diAAU+tCuAxgul5nHSu5+sjNAl48MExWb5Aw/zGhOnW1dGvD43l2lnEbk8ZXA4xuDh8oa53XnKYmYKzXSE/h8HufzYOGYSuYCYOsl/BPs54eWvKyLL6dW8HtrPL+fN99InGiR80dYeZFontGNthy4DtiwFlFspThKOUNdOZqGJVuwNdDupFTN/txI1COvlMMPAVIPpU4L3Z1uQuaeS8w9A80nfiqhXn36fWTuFV7Fla1Xr8n2svty9eKM6t2ftGlnO39DY+bvR1Ps/Gl2G8KEE1gNS3mjS0zgN+/pE7gFJ9B12gl8D17kefC8PEcqTbb6At3G/Hdxz2ioFuvPePweQUyTQTXR0aAPXu8DgL3cottNK+KULAgu
*/