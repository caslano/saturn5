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
OkpX10bb1ofS5VFfgGdTy3IoPhZd2fzlOeqGZlxBM6NWcWoNUYYYqhrkMeOhi6qhH11JbdTak1cdxYZXz4x1KhjNu4FPv20XnyNqNUaaWkmU5teDslBLS51U+QMobyIK+N7GX7S0rcAGGY6kls1HorwHa2NqlDsL+KuICTkiNKNc71KpGGo/LIrr4q++eNWxWRTCo3+Ako+pIl8+yNOKLkoW2ajQNpoBy1/Adgu6LUduEXJLkVtCiekjVROSRwWNLseXK8pHiauDcmkmPSgdb1BMXFTrd0oeDeiqpxkj7mMR98OotX5M0s5qsDxqbbaGooj7HunOBxSCKDH9hEKrqNBcJBymoCnorOM2/NW3An5ydKUh4qoFzWHSi64MgdRNUFOaJbRRy7WU+vTz6xRFEqcOkY6k9ArV0k0z6KLgV5TilUcKq05BhfW+F1JGSaT6/cGi+VTMV2rVD9W7qbJNuOqH8Tnly51iV9hQWZHUtjxhUd+pRTlK2XJoBhJBfCZMc4ULflQjlgkEbIrSmhWjC8lWsOBHqQ+S27Z6YYKcNv5aH6qPKRRvM1U0lQwJyIyKjqXW+bxiMcwDKHbZC45M5rtgr8d3PR113lMOyptKM6bIpRbpbJMp7ZMfIli6hEDaZqkUN4OFIzcmDnVP5E+K+2fG6fIC3ugyD2yovpZJM4ihMv29WufvP0F/zrxSeS9WufElRulYb5bUyc14
*/