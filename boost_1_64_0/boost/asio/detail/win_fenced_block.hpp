//
// detail/win_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_WIN_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) && !defined(UNDER_CE)

#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit win_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit win_fenced_block(full_t)
  {
#if defined(__BORLANDC__)
    LONG barrier = 0;
    ::InterlockedExchange(&barrier, 1);
#elif defined(BOOST_ASIO_MSVC) \
  && ((BOOST_ASIO_MSVC < 1400) || !defined(MemoryBarrier))
# if defined(_M_IX86)
#  pragma warning(push)
#  pragma warning(disable:4793)
    LONG barrier;
    __asm { xchg barrier, eax }
#  pragma warning(pop)
# endif // defined(_M_IX86)
#else
    MemoryBarrier();
#endif
  }

  // Destructor.
  ~win_fenced_block()
  {
#if defined(__BORLANDC__)
    LONG barrier = 0;
    ::InterlockedExchange(&barrier, 1);
#elif defined(BOOST_ASIO_MSVC) \
  && ((BOOST_ASIO_MSVC < 1400) || !defined(MemoryBarrier))
# if defined(_M_IX86)
#  pragma warning(push)
#  pragma warning(disable:4793)
    LONG barrier;
    __asm { xchg barrier, eax }
#  pragma warning(pop)
# endif // defined(_M_IX86)
#else
    MemoryBarrier();
#endif
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS) && !defined(UNDER_CE)

#endif // BOOST_ASIO_DETAIL_WIN_FENCED_BLOCK_HPP

/* win_fenced_block.hpp
PaOCe0ri9aIFXTIetX2e08n6vb1zqrZttgNRx8UGqXQxKipBif2EHQ2pB0asjK+z/RpIZqRKdefLeujH4LgSY2EXCMNdP9conJdPNBPdc8q+GUE1seXNMUYyB2I/3VxhYK4SEmHpOUMmu4mI/hozg7DxM0Ov9jPlpmX3TaTjJzrVbROdqCMZEWO7k0o7vj4ET0utGw+THLQqu3yGOG3reFaJhbb1c6haDeLjeXI/eqCz4DJDlyjDNxUuJA+TPfZfdQ0tO/eYuqN2lZAMqlRVKgP8SLJFlLm9dSQCI+uv2cZhICGSdDQ2b8TMKQq1WnE1jRVU7w9acFHxsLPCdEhGO6cWfepxIwkJbimJH66zpEz/IY1xcemI8p93EvpFHu5YGfylGH37SzEiZCaK/y6aBF8cDzbp73L/Ebpbn+jrRyzmuwB3lWerHt2x0PUnaVz6r5Q2Kxxd+gSajFnk2bdG6C4uKpKXIi1o6IXMYNaesGms2tjhVFBjsX2wepRkQhY/+d5dYME5y9xyFuVS/rNxWL7u9lxOeBzqe7PACb7BjVnE4NZA62NQpQFY5A==
*/