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
3Zzru642z/3dd3sgj8eY1ebptVFuMeV40Kt9KPDEfeJ7triX93tpP6Py3kaOr5ZRuPLeOUDecPl/GjH/US3R8t9e5U9rmTb/wtcze4GhfCcM+TQ2BYb+u4PV9wZf36K8NzgC+d9W5AdPonUZAyvtjH8dWPlgklGWQ7Ayvivm0vc/mGykxi7wDx6/2g9W4lfI/nnpwdH6/8sD+Edj/9h8iROy/BPnR2ufOPHn9tH3H46t+tA587ndorHPE6r8Ifv/z/O9/X/mGnnyA8tch7rWYHOYe7fy/YeeMUv9Jh6fqyRdOO8TW+3YSu0/aPTb/z9LPPsAfJ4Q/AvfX3JXqyVHNDHqM4fyUe3JeVe0hYu/Q5vbt1lV23EcPofH+4/+c9eHhSx/3wD5/d/5m3u3sB7GW0XAGJ5WMbK8d0jz9Zos33Hky8z2FFfId2kO9ti0JWt4/O6W/AZ+f5b2FXt9f1bgf5Xm+4pzugMP+IXxrmmPjvceEfKOiu/xEcp8d4S8P4+Qd1WHJ2/8zWJxwO9Vq+3Irh2QtcB6c4yn3FRPwVt5lkdt91y+PXJHB5vfUMZGOAc//2cD2PNmbG2J4h3p+lmH2bxF5SHgG/Ad+bz/teMh/nvQg5TN4YdE5683Rcj7fcn7z5Jo+A/v9JcdPIkfeCs8PXxO+szWnVI+Ks/wePd48wat6ou8v+zqhwLv2k7C8vJDKbvet93t+PMG2V2d41X7MGqsUL+nRragOdAVMySXo9y0npzJydSK80uQXkT6B2liF+GQTNSPp3hBcoEv6Usyq2vl00qgF/KbwfvWLmnzEr348rmQJ3q5xnbbckWPtVsxsYqME9Yecqex+andeu8DTpaGs+bzQHd0e+Sd8L7R1K9QvWp69N7ZnCzVX6dz/BZKj779dDCO63HGuaenOHb7skh2q16g6sP7e3yfY87P1T7w7gvAU8rSX643LmbP4AKff49LWTNaIPRVx8YoH2WPM31nU/bdF6jPmXO57D1revKpa+XHybJRx/BfAVOV8+wV9bGP69HD7ytzxq9d6IRPvMAfOGQnx7VObjOy+6yFRKvQ8ftl+SN/0cLCfQB4ebo9sNDZD2ALyUdPPvDN6299J/j6P+sQtB6v0esflwqpv3tr8Jf+Jn2x8O9tLNLADLOtuj9EPD+sbwiLx47geDr6rX5oePrp4O3jgsfqCnjx2EptAMVX4AiZTpa8lPhGz2AuGaK/B9NpXvS+Q/3XYILWna8O1X+2s68seCzg3zQae5jed9tNvomrrmvvdpglW3T8jxf8g8e0ZKl/2dx5mOqj4b6vv5/4q37Pv2mlj6O8d9K1/Fc93AmXzl2fT4HNgCnoBO7Oh9McPb1XA7TAYPSy3I45PFg5gYd3GZEuxF99HgBtjt63LLLtj9nzCP2HW/ISJsor+u9njD2CMJVvtOvXJ9nPozoF2an/zL/TuMcRhdUz7/IDryP82x0P/tDDH+M+ieHxfTqUmf436qQ/ebYZ3xxhvuZtPwex2pHq88F2/A+nDVa/cbf3kcw+6h4k8mt1DTvYd+wt3FOPzNuPBFnDf0fEw946gbf/vqrjevz1+d7WJaKx8RpHqXoIubguwNDTR/IBvbs+ex8l9YmgzV50lGufgPz7wuXMv0spn1+i59seOIp/o7J4fv2ttB1kYO8+CdeG446ONh7POrqweKwzf3VSPgbKIHxfu79AO+m0K9+EaCvHectjihPD9jxG1vkIdDjxGP+25c+ScOrg3cfY9S8aXb48prDy1vGpmmOje3fYnsc69EmOdXu3APKPDQ/7ywHY7rjVx2V/VTxOv+txOZpjcX4H0qdIo46PxbZDWoB0HdIbSKUn4HOpSIcgXY0=
*/