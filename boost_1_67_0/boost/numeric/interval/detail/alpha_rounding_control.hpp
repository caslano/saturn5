/* Boost interval/detail/alpha_rounding_control.hpp file
 *
 * Copyright 2005 Felix Höfling, Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_ALPHA_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_ALPHA_ROUNDING_CONTROL_HPP

#if !defined(alpha) && !defined(__alpha__)
#error This header only works on Alpha CPUs.
#endif

#if defined(__GNUC__) || defined(__digital__) || defined(__DECCXX)

#include <float.h> // write_rnd() and read_rnd()

namespace boost {
namespace numeric {
namespace interval_lib {

namespace detail {
#if defined(__GNUC__ )
    typedef union {
    ::boost::long_long_type imode;
    double dmode;
    } rounding_mode_struct;

    // set bits 59-58 (DYN),
    // clear all exception bits and disable overflow (51) and inexact exceptions (62)
    static const rounding_mode_struct mode_upward      = { 0x4C08000000000000LL };
    static const rounding_mode_struct mode_downward    = { 0x4408000000000000LL };
    static const rounding_mode_struct mode_to_nearest  = { 0x4808000000000000LL };
    static const rounding_mode_struct mode_toward_zero = { 0x4008000000000000LL };

    struct alpha_rounding_control
    {
    typedef double rounding_mode;

    static void set_rounding_mode(const rounding_mode mode)
    { __asm__ __volatile__ ("mt_fpcr %0" : : "f"(mode)); }

    static void get_rounding_mode(rounding_mode& mode)
    { __asm__ __volatile__ ("mf_fpcr %0" : "=f"(mode)); }

    static void downward()    { set_rounding_mode(mode_downward.dmode);    }
    static void upward()      { set_rounding_mode(mode_upward.dmode);      }
    static void to_nearest()  { set_rounding_mode(mode_to_nearest.dmode);  }
    static void toward_zero() { set_rounding_mode(mode_toward_zero.dmode); }
    };
#elif defined(__digital__) || defined(__DECCXX)

#if defined(__DECCXX) && !(defined(__FLT_ROUNDS) && __FLT_ROUNDS == -1)
#error Dynamic rounding mode not enabled. See cxx man page for details.
#endif

    struct alpha_rounding_control
    {
    typedef unsigned int rounding_mode;

    static void set_rounding_mode(const rounding_mode& mode)  { write_rnd(mode); }
    static void get_rounding_mode(rounding_mode& mode)  { mode = read_rnd(); }

    static void downward()    { set_rounding_mode(FP_RND_RM); }
    static void upward()      { set_rounding_mode(FP_RND_RP); }
    static void to_nearest()  { set_rounding_mode(FP_RND_RN); }
    static void toward_zero() { set_rounding_mode(FP_RND_RZ); }
    };
#endif
} // namespace detail

extern "C" {
  float rintf(float);
  double rint(double);
  long double rintl(long double);
}

template<>
struct rounding_control<float>:
  detail::alpha_rounding_control
{
  static float force_rounding(const float r)
  { volatile float _r = r; return _r; }
  static float to_int(const float& x) { return rintf(x); }
};

template<>
struct rounding_control<double>:
  detail::alpha_rounding_control
{
  static const double & force_rounding(const double& r) { return r; }
  static double to_int(const double& r) { return rint(r); }
};

template<>
struct rounding_control<long double>:
  detail::alpha_rounding_control
{
  static const long double & force_rounding(const long double& r) { return r; }
  static long double to_int(const long double& r) { return rintl(r); }
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#undef BOOST_NUMERIC_INTERVAL_NO_HARDWARE
#endif

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_ALPHA_ROUNDING_CONTROL_HPP */

/* alpha_rounding_control.hpp
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
*/