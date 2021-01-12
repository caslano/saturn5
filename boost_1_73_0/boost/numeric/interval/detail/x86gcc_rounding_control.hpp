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
WzWlzGNvSP0Z1vrQ5vb6cIzNc7/st4/GK/sDycnl9Nbicg92v4Zwtv8UF/6g5u1/wFsy/k3v92sV3g3R+Lf8H0NYpnvHB8VKIRgjgYxRTv+4Ur54MIzrhkg9amX+UUyp353CaGT2RV0YV5P9m6Lwiez+9J3DeJW9n1T4HFPaT8nfSZOU/I8K40Pdib9X9gdsvkcYe7Lz0cLvIOc3o9EwvsDiX4Uz+xajwziDvb9DuHW+YaNS
*/