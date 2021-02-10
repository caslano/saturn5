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
NfcIJfrQI56GWATN2rO0Hzxs0cDyk/TJjvNiOIG5w6Xj8FyaqrunoJfGyF1EM8kViuDZtUtfd+gP/123t0wYP/xZ0plkPePWNKoH4/d/7aq2h/fM/o45AB1vYt/iXryO82T0KrP9RZoZUswnji0o2wh47uXMbLyMXZ5yEwENlFEp9HYVDxvpZo3JlIEcqGT7/czkKmyejYvhkbFg0rmTJThyCqarVZ3VamCjX7YNt3cJzUUaHchry2WASMbWB30L4yvqM8KxLtZi3AhgMqctYrl3ct5J7FhiCG0uFQXAeGAb6Jn0Y667rBOhn/DM+Aw0VtPEqsz13gTq+WDlpXnqx4OG+OCQKuwP3yTTLc127h+cmW4v06fMC2qUZb43qyRnC+xDmtERLuBP1tLhEBgqRD8AmgMDFvmozA+MOQ86Ae1dMsvAZYqqNMLHGgIpIDgdMOBRkM6ODDTOUrrcZl4i5W/wd0sLIaZ+8SfDNP7SQtZaHuVx8tC6aWX1rYSdeDbDBaikbdC1ezmpCwW79Kv8xK9wCyuG64Dlu9rAs0Mz1a1CFb3zG4n9F05tAQ/cPoh3afMuuv4AF5ZnVyzOQTL/8W5UKVTp5ydJ8Q+wFriH6o2BnYe4/AJhR3suwsefLCRrDNZX4HDAPqCB4ZQE
*/