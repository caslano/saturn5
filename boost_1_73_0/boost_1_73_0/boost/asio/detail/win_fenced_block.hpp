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
mpky+EIJ+49OHRMXHjjkFiaI11qyLZ6ax4fmXu1MoYnTt7BjVlpr1S80+NEL4er84LB/73Vl6e58Pva4EeQtMqWKL4w1U33SvwJb/p3yMRcyFjyKyMcJxREsjWYNvx3/TAkzDc5En+cGZxHJMMyrLPkibKmNUm+j+L3MWornCLkk2UoR8ZuA4mvmFhGMODkSrj6EiqjCRv0AUEsDBAoAAAAIAC1nSlKy1R7qfAEAAMwCAAArAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvZHVtcC1oZWFkZXIuZFVUBQABtkgkYG1RzWrjMBC+6ymmPdd5ALMslJbSwh4CMfQsS+NYrawR0jjBb78jKW1S6E2Mvt+ZfxSOPdh1id2M2mJSh5kS9/CsHpP8/Jmcx6AX/Kte0cce3pNjBJ4REhp0J7TQiBmYbuH7REyGfO7hdRj28DLs1QGx0z5TD7RyXFk9acYjpa2HmTnCxFF1Xad+MYkXuVu3AsgRjZucIIr1TqlhdhkosqMA8pp1sFsBrxnhPGOAjVY468BlmJlSM/qWnTWDDjWzyiVGxmCrnRB38ET06TDDlGj5QTS0elsmAcaSW1twAbTQDQWrzJq8DE5kdI02bpLIhWPV6DpTZS+572C4GXYfOt0U
*/