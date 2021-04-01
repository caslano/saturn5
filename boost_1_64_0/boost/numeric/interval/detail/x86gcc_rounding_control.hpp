/* Boost interval/detail/x86gcc_rounding_control.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_X86GCC_ROUNDING_CONTROL_HPP
#define BOOST_NUMERIC_INTERVAL_DETAIL_X86GCC_ROUNDING_CONTROL_HPP

#ifndef __GNUC__
#  error This header only works with GNU CC.
#endif

#if !defined(__i386__) && !defined(__x86_64__)
#  error This header only works on x86 CPUs.
#endif

namespace boost {
namespace numeric {
namespace interval_lib {
namespace detail {

struct x86_rounding
{
  typedef unsigned short rounding_mode;

  static void set_rounding_mode(const rounding_mode& mode)
  { __asm__ __volatile__ ("fldcw %0" : : "m"(mode)); }

  static void get_rounding_mode(rounding_mode& mode)
  { __asm__ __volatile__ ("fnstcw %0" : "=m"(mode)); }

  template<class T>
  static T to_int(T r)
  {
    T r_;
    __asm__ ("frndint" : "=&t"(r_) : "0"(r));
    return r_;
  }
};

} // namespace detail
} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif /* BOOST_NUMERIC_INTERVAL_DETAIL_X86GCC_ROUNDING_CONTROL_HPP */

/* x86gcc_rounding_control.hpp
TAOEQ8ypEhqldjVIqZxxAqLvvpYCiGoUvoWiNL5pSKjf0Po/5sDTO8aMRbnDqx3rpZNahnY9QVPORoxfSDEv7Lq0OnqZfSMrOGKQVe+TkLClX1FISc/u/gpkYEJmyccBNKXY7RVTubOtkkYWDiBGq8gYc0blZN69KwzYDkYAb4dxWE3mKtfdPwPxkCO+0k8i80PgjZ2DvV+5Ke3x6Rrl/EMRnUphVlCjnrwVAyYaididaSo4sBiHfpO24Ew/HqFsLue6wANd7hpWvvz3KRbME84d5loHrY379ewHTRxKMXOqdTikWqR1xR5K7/1t/6M3WhD9kjj7t+NLCppNNvefk1WMluzogIZaAlzSaImYzLPkdEhNi26YYA35ZTo4FquwBkanNsQ+fiLRZ0bcxN9jG+OHVq4HnvmhVebrRXeCzyfEDhQt2o7vJy+E/M31JA+xeYZDBvEqJihdLPZNd+I2sYtgslZIUfTNSetynrfDl1K9z1rIBQhru2x0yg7lg61IVSYO4ww0FaxDWDaXyxqRhzYWjc+t30KneB+hjMdkTXDp/hYJghcAmMC6dg==
*/