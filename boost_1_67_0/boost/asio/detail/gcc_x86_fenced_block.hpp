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
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
*/