//
// detail/gcc_x86_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/