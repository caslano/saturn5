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
8M8mS564L1ATNJnswgDZb3GZ6mioqhVUNKGShdK1Zox2KhJoTmO4YU7hVHNbhuIDqLiZiBrp17BBizRNJ6Z4QI4e8TPKx2NGU6NK7jeBRV2YLcb3l18O8/qmZss8Ne4dx+/cWo4xfwbr5U2bk8vEptM79FlNBGOG3jMaKSPc0L21pKDluHZY2Z31PPIBLM+4Aw2zYEYFDqwD5vAzy7M50DWMbOtSMSqnRqLDO0bCpqZWya89/u6Np+fqVgQHxShXRRWKlipsm8JChelKuTstYEjRu2qo2Ew45YMj10IroEvE/oSYTZnLPLXcw0DLkwXJWgxEaL4EoOV0xY1hbEq/4hMbThySlxZNzBN9iGruKCjl/QQ9oRe8jmDBzrUENGs+vf8+7DHmwkbOCAZMkoLXpowNM/t0r5m5DMab2SQP9JZRdZ8z5c4fYL2ogA7J1UEzHggFXwhjM7Q6plzmuSileUhe0SES6hru+5YVsFBZ9F1YIGXxtakyOnfoAH/ASxzw99/9zW+b5GHj23/3t/8MlWqZbXsDiTltZfPpHWOrs/P5+fPg0VDIRm8lvG+ggiJ8QuVtB15h09hDS2e8VOmysMs11+aGZWRwWpg0XRrHDfdQmTOVY5AozxMUSEMHTvyBW5iPjAVcwh3nO5pp
*/