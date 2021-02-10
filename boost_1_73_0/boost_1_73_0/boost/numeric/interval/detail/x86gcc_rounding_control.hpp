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
axxJ0J8MLWpIp+65343GH1BLAwQKAAAACAAtZ0pSaNRtxIECAADvBQAAIwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2xpYnRlc3QvbGliMTU2OS5jVVQFAAG2SCRgrVJfb9owEH/nU5zYC6CIrH1cu2kpZS0aggroKqRKlhMfxJNjR7bTFrX77juHUNZqG32oEbFz+f3z2XHv/UYLenBwsPrPaNBcM66s+YmZ/zuasSfY/oh1S/Mhkxj2lCfWhcOUJ+jUFNa4nIY1Y4eMbkO28IgD85aFJVWIFpgDU26sXOceOoMuHH88PorgnGuJCuYedYp2HcGpqCtfc/7w0Hf4JQL0wFW/0Vjk0oEzK3/PLQKtlcxQOxTAHQh0mZUpvUgNPkdYSYUwmF4tR5OLCO5zmeVBZGMqcLmplICc3yFYzFDebTVKbj2YFdFJXEjnSbDy0ug+eSN4tIULGsGeK2eA33GpeEpG3EPufek+xXFWWUXpY2EyF2e7ffdzXzzvZEkhCr4BU3rwBiqHEQRkBIURchVmaggVyypV0uXRPg1ZaREbCw6VClrEk+i2sRHmTXuiAIOSEksfJme0C1b3uSleAKmPQWVVWU1G1AcCCUNtjqDSAm0Nrne+s2h6Wjf4n0ezzyvAaAoD7WQOo3kbUu6k
*/