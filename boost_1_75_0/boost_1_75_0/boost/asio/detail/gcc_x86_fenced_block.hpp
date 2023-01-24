//
// detail/gcc_x86_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_GCC_X86_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_GCC_X86_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class gcc_x86_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit gcc_x86_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit gcc_x86_fenced_block(full_t)
  {
    lbarrier();
  }

  // Destructor.
  ~gcc_x86_fenced_block()
  {
    sbarrier();
  }

private:
  static int barrier()
  {
    int r = 0, m = 1;
    __asm__ __volatile__ (
        "xchgl %0, %1" :
        "=r"(r), "=m"(m) :
        "0"(1), "m"(m) :
        "memory", "cc");
    return r;
  }

  static void lbarrier()
  {
#if defined(__SSE2__)
# if (__GNUC__ >= 4) && !defined(__INTEL_COMPILER) && !defined(__ICL)
    __builtin_ia32_lfence();
# else // (__GNUC__ >= 4) && !defined(__INTEL_COMPILER) && !defined(__ICL)
    __asm__ __volatile__ ("lfence" ::: "memory");
# endif // (__GNUC__ >= 4) && !defined(__INTEL_COMPILER) && !defined(__ICL)
#else // defined(__SSE2__)
    barrier();
#endif // defined(__SSE2__)
  }

  static void sbarrier()
  {
#if defined(__SSE2__)
# if (__GNUC__ >= 4) && !defined(__INTEL_COMPILER) && !defined(__ICL)
    __builtin_ia32_sfence();
# else // (__GNUC__ >= 4) && !defined(__INTEL_COMPILER) && !defined(__ICL)
    __asm__ __volatile__ ("sfence" ::: "memory");
# endif // (__GNUC__ >= 4) && !defined(__INTEL_COMPILER) && !defined(__ICL)
#else // defined(__SSE2__)
    barrier();
#endif // defined(__SSE2__)
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))

#endif // BOOST_ASIO_DETAIL_GCC_X86_FENCED_BLOCK_HPP

/* gcc_x86_fenced_block.hpp
zMrzvvTgUzQIhfptdcpzOlUTdBtQJRXymcXJ6yZABQUpXjMRxLnvxClntAqKZguJXebNE/RKlxjrhCJQxqruMQN3abmZcqVUbPcc5NwX4+htNu+zBM/FVcnq60BXqcvcV3/wiE35lXc1OY1wmBhkFe1h+fF3UTiC79NEBnY1DYRwhWbkknUTsPZd3QQ89CIzATi7Tp2WmYVr8cEUtB5EU4BoiH3P/l/h4sJkEiOhkBZb0ZquUlz2SbP8zpxRt9lL8dRuvEgqT+ZXW0Oo1UXRD+bJ7xqevOswKKSSC+Zl/Rx/cdsStdRCKvJPxiLH86OgdmsIKBIDlrxwgcNXYAf31gQJHZpQX1aU2kZEG1P8NjryLo72wWuqEwt6wt7chPRapy+3w5cbwnmLLrM/N8HJPAlUfSkLL2iSJ760CQflQmzqDdpZKAGRhj2v0hi7k7a96cEhCJNTPqltOJiibjgID2P8A5Tzo+mtWu0tVYmUkcbLLvOqbywWWnoPlDwXXVp5cDr0rwp7lJRCKGUVE8K0Px+E2mCSwCwp4ymOfeAdzSS9+CeKwm6ic8toB/PPQBKzGtZbpAbQQbQ4JXLLGYPF6WTiFSvnQyGSSZkyF4df0pvgHUeFb1hWaP0w+eJ3CGP8HRiYvF4gxOKzotta1j/UZrRSCgRZ/CHppOxuhjArDK9MBIEcKX/arAukCWgN/hmjneJD4t2gzKMxguVq
*/