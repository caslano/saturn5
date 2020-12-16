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
R07zybzX6+qj/vL52GT/mvrV9+6Pvnv3b6p/Q/2G9+k/hhF/jv4e+4+oX/I9e/ffb6/+aP8++6fUr2uv/nx+xca41b9b/Xr26T9u38/dP2D/vPoV9unfvs/2G+ofqF9pn/7j+Zh4/OpfUb+B9/xzzvveS3w/ysyYvNf3lj1yfKPc/5DwOGdqfY5OmZN0N40G2of1eTB02VyjqzJmJPSA2W8PPRiZ7UPmOj0M6/Mnx5eXs2xPmQO2d5kr3H7WnKH96PF00Zymy+Yct18zpzReGg0ab7T9sRyvuU57s+z4Ob4Oc1rjNTe5vW5zg+25qJ0umFuabxkzw/GakxpvtD+er6Y5y/GNmGvsn5xt54PbT8P6/ofji8z++ag/2wtRu8ZnztI1WD9fyfGZW5pPc4lumdN0+xw7H3SnOan5M1fonDm7P8dnznA8JXNd8wfr+yKOzxzQzWj7mr+onY/v6DVz/2lzk+3d5hadi9o1f+YGXTaXNL6oXeeXHrXg+wmOV+1L5RF5mtw+l54up+Tz5YxckbPy6bIvnyYX5ZJclQN5UF5n45PPgflFDL1Q7pBnyF3yTBuPvEguyBfIZbksD8iX2v7lLTY/cl5OzqdnyWn5ctu/fIWclz8kB/JsuSLPsfmKf3+N51ftc22+5PW2v1lPDH2WjV/t82z88hk2fz691sYvX2jbk8+1+ZMvk0vy+2388tk2n/IpckPut/HP5ng3yMNqL9r8LqCXyZ3yqXK3fKacky+y+ZX77PqNf9+d86n2jTYe+Twbj/wBGhuiN9t45Ivt+SBfYte/vMmud3m5XJdX2P7k+fb8W0ivsvMjr7bjlwuh479Hs9is9g+b53O+19j8LPzXvM94ZHl4l/v2Wbw0P0EGy+31iy6bs3TVnKMHYP17Az9Pmn22t8zpsB0XavR6x/et5hLdaa7QGXONzprrtG9u0EVzk66YWxpv6PgdesOco5vmLN0yZ+j2fns/QKfoUcv77HsttU+zz+HydNmXZ8iBPFMuy3l5QJ4VKv79ydn2eV7tc+QReaXcsVL3Uxuf3Gvjk+fKBXmeXJHn23jkwD63yL48LC+wzzmn6P4dKv75+eVySu199jlCXmjjkVfY/MiLbP/yYtu/vMT2f6rer9j+5IJ9TJGX2f7lU+380KMWW1dSe/nU/+774s3vTN06Y9d9973g0u8+58Jnc93icvw90PNSo74HiJdH/hbsI8v/2IKfS8HPpOA+8bKnhrmpGhk/mxLWYQ5Yh7mhGhk/pxLWYfZZh7muGhk/sxLWYc6xDnNNNTJ+fiWsw5xlHeYK6zC3WIf5mC+qD/IW1TXkR92ofSG/T7WP/AXVDeSn36TjQj5Ntb9fwrsGkfrwZK+O3DY24XWiTiG/F5FGHSDfgOhC3US+ZkLCG0GdPijhPXtiwhtCXXt8wss+IeFdhtrl3U9MeFtRu3wPYgfqUkfCuwWRQe3ydQcnvG7UyPizPAkvh9rlNz0l4RVQuzwNUXL7fWrC2w9/Y7yjOtlLIt96CPqgdvm7hya8zahdbntGwtuGOnNYwluLSKF2+apnYb+oXd6KmIa6cnjC+wZiEHULedKzcSyo08gnIxqos0ckvBmIJmof+RbEMGqXNz0n4e1B7fLliI6PTMZfnU94b3tewiujriEX0gnvCNQun4HIoHb5k4ge1C5fi/BRu9xArEGden7CuxCxG3Udue8FCfzsAMaMfMgLE96YKzE25F8hdrn+UxLey1+EY8D6ZBfGhTgadebFCe87iB63/iUJ76WIPGqXz0UUULv8LUTJ9XlpwvsYooq6iXzU0QmvjtrlWxF3oHb5F4h7UCPjOkp47VehP/IfEDW3nZcnvJsRU7A=
*/