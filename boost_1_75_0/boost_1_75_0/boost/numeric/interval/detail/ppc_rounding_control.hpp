/* Boost interval/detail/ppc_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 * Copyright 2005 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_PPC_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_PPC_ROUNDING_CONTROL_HPP

#if !defined(powerpc) && !defined(__powerpc__) && !defined(__ppc__)
#error This header only works on PPC CPUs.
#endif

#if defined(__GNUC__ ) || (__IBMCPP__ >= 700)

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

typedef union {
   ::boost::long_long_type imode;
  double dmode;
} rounding_mode_struct;

static const rounding_mode_struct mode_upward      = { 0xFFF8000000000002LL };
static const rounding_mode_struct mode_downward    = { 0xFFF8000000000003LL };
static const rounding_mode_struct mode_to_nearest  = { 0xFFF8000000000000LL };
static const rounding_mode_struct mode_toward_zero = { 0xFFF8000000000001LL };

struct ppc_rounding_control
{
  typedef double rounding_mode;

  static void set_rounding_mode(const rounding_mode mode)
  { __asm__ __volatile__ ("mtfsf 255,%0" : : "f"(mode)); }

  static void get_rounding_mode(rounding_mode& mode)
  { __asm__ __volatile__ ("mffs %0" : "=f"(mode)); }

  static void downward()    { set_rounding_mode(mode_downward.dmode);    }
  static void upward()      { set_rounding_mode(mode_upward.dmode);      }
  static void to_nearest()  { set_rounding_mode(mode_to_nearest.dmode);  }
  static void toward_zero() { set_rounding_mode(mode_toward_zero.dmode); }
};

} // namespace detail

// Do not declare the following C99 symbols if <math.h> provides them.
// Otherwise, conflicts may occur, due to differences between prototypes.
#if !defined(_ISOC99_SOURCE) && !defined(__USE_ISOC99)
extern "C" {
  float rintf(float);
  double rint(double);
}
#endif

template<>
struct rounding_control<float>:
  detail::ppc_rounding_control
{
  static float force_rounding(const float r)
  {
    float tmp;
    __asm__ __volatile__ ("frsp %0, %1" : "=f" (tmp) : "f" (r));
    return tmp;
  }
  static float to_int(const float& x) { return rintf(x); }
};

template<>
struct rounding_control<double>:
  detail::ppc_rounding_control
{
  static const double & force_rounding(const double& r) { return r; }
  static double to_int(const double& r) { return rint(r); }
};

template<>
struct rounding_control<long double>:
  detail::ppc_rounding_control
{
  static const long double & force_rounding(const long double& r) { return r; }
  static long double to_int(const long double& r) { return rint(r); }
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE
#endif

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_PPC_ROUNDING_CONTROL_HPP */

/* ppc_rounding_control.hpp
MhsDukqDL6fRbVuXMAIMu3M8OZXBrnJocwLwx2AT2AnzuuCBjMinGClppq1VPIcc2SDlPXpesL8fM6HlVNjWWYfZ1vU25WwN0t4OaLmHy+rm4glWKo4hr3fw/1m8+QVWW+ntCSIxLNU95Et9Ay3QZl7bV5mbgY9m8CIQsHxnFVFWTFCqysC8gmEe6As/aIX/UqEPUJ0eTEd/qmxLBWX1qG0RlaKopvhQzI3x8Idtmg/NiEBWnlcZmW27/D3KVfirLU1Pr0iLjUdL6TNmXc5Hec946lufIOsYmiCeYhHXYE+wqwsxUW3s1CMJbjiJJEhMnOjvzZO8pJi+eG3x9Lk8Sn2vFfLVJQ4K6+lymp43/U/6uZ0+5Ult+Z0+YzgpHzEZpJOhbuVIjbJSdK/6Ki2fvZjekpp17sWwGU58dJissZA38p5B7xVFccNyZDTmggS1lhf3kNABI8qvgH17Yq2Jcj8iv5Rs2bOa4Z9H98dmf7wNrJ4d6mgnNIr5HK/XNHXaDRRi0/16+pMIfzZgGZFpYT5MYX46CR55fm6jr665gX99Bf5VH9rM727LR5uDf9kdD4DWqr1/bmdvGCWcMDz3wcuj4bky6v5HsEgaWB9YDpYCMKpovwNkHLvA67wNKBrDLGypw4Gy3FkuWIkj84C2aIlhWXJ0FXgLkW5ZT0o8j2nRWL2kjcljrfyoEU8D8PQonvC4GDn2dJ61LtWd
*/