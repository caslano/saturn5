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
t35iaCBk3tcnsf0ilJWQrpcW9WmaQ/7DJ1rTcBfQuVKDLxfnQV9ePczdxE9FseBqAhC8mEkBQBbK+IS5WXXrkqnB8fl5c+GFrLq1b8N/i9Tdt+HLWMtXxakC+8ArIebBh1T0VSX9mVX0DLtmVa/9JHKNKVPOAA9depbCNY1JMBRkwQtdL0cKKlUf+jJyjSnFe4YLlLHvN7xVZWJv7TQ8pPX0F3ee1qf16xdXPd/V/2K0TEyJhiATsXvBZ/gLWmTfR6Ewhj9gG4uKXGawk7IT+0mee8vpMKSD8B1SRYvNgmFybpu4f8rzVmEYxPj8cMQDOZdNiX/eLISet/BWl3VZVeUx6rFW6jGcGyHVod+t+kiPGXEVD4iWgypuj97L7BYbnbUZ1e9NbMpVsqdps00KUFpfnAhxfUlW87ok+fKPMLRAR19cQ2D/Nf55vVmNWyxSACcelrID2z++E1fk4CzSTj5BNsM7OHqsjJZyx6c3iVdP4x4N+OxSboq02AZxf+0KDTA8slvN9QrEzfNNpa8jnC8MK5WPfIKTsvPmY2CNZ6Ktn//yMpptswnqBaf5US5OtHYWFn40/rzSEjUNHK+mgfX6sMJMY0w7XipIg85JIbAxt9VXgLtSJck/OapFMvwuauDKIlqLzifUx+H8KZunCZ66RH9qEXtqjmsUrl/AsT3GYfmzjbju7mhYaC1xFpXSCINY1yvuvzjr5GaL
*/