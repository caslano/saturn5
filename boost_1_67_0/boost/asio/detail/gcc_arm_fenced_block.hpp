//
// detail/gcc_arm_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_GCC_ARM_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_GCC_ARM_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__GNUC__) && defined(__arm__)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class gcc_arm_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit gcc_arm_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit gcc_arm_fenced_block(full_t)
  {
    barrier();
  }

  // Destructor.
  ~gcc_arm_fenced_block()
  {
    barrier();
  }

private:
  static void barrier()
  {
#if defined(__ARM_ARCH_4__) \
    || defined(__ARM_ARCH_4T__) \
    || defined(__ARM_ARCH_5__) \
    || defined(__ARM_ARCH_5E__) \
    || defined(__ARM_ARCH_5T__) \
    || defined(__ARM_ARCH_5TE__) \
    || defined(__ARM_ARCH_5TEJ__) \
    || defined(__ARM_ARCH_6__) \
    || defined(__ARM_ARCH_6J__) \
    || defined(__ARM_ARCH_6K__) \
    || defined(__ARM_ARCH_6Z__) \
    || defined(__ARM_ARCH_6ZK__) \
    || defined(__ARM_ARCH_6T2__)
# if defined(__thumb__)
    // This is just a placeholder and almost certainly not sufficient.
    __asm__ __volatile__ ("" : : : "memory");
# else // defined(__thumb__)
    int a = 0, b = 0;
    __asm__ __volatile__ ("swp %0, %1, [%2]"
        : "=&r"(a) : "r"(1), "r"(&b) : "memory", "cc");
# endif // defined(__thumb__)
#else
    // ARMv7 and later.
    __asm__ __volatile__ ("dmb" : : : "memory");
#endif
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__GNUC__) && defined(__arm__)

#endif // BOOST_ASIO_DETAIL_GCC_ARM_FENCED_BLOCK_HPP

/* gcc_arm_fenced_block.hpp
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
*/