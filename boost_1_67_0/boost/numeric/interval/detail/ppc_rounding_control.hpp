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
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
*/