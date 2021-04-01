//
// detail/std_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_STD_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_ATOMIC)

#include <atomic>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit std_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit std_fenced_block(full_t)
  {
    std::atomic_thread_fence(std::memory_order_acquire);
  }

  // Destructor.
  ~std_fenced_block()
  {
    std::atomic_thread_fence(std::memory_order_release);
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_ATOMIC)

#endif // BOOST_ASIO_DETAIL_STD_FENCED_BLOCK_HPP

/* std_fenced_block.hpp
OOKwnAkvG+M3KlN+8dE0h3vArUyAoYNyi3zFZQlIaUgHfGAO7eqdfeiG/I7ZeM76rAlvfVFCgg+iyg/REsj58wShVeRGw4rcwcs38WWBR1aZuGLEpNQEWTc/wZfmABqHu/1YQl9xbH98n+VRHRE1+3sGxF0C7KMYfQEdVfd4w/06EFCQknEPq0v482Mgb244KZkbrFAP1ckgIvbCPp6nOSSz8Ay7PEjF0P0A0JUpYxoHm3ntwjz+bnDnX1V46gjCO5ZMyHW3nOyIW+J+TKHrUYMGqAOoFCQroveblh4H82kJV+aSd2MKOhO9sgVkS2kwHGsB/66HaogHsK7rKxMF6k/PdZ1/lwYWZvEoSs0Xf8I53eEipj2lLUrLYcb9AEcPJtODXqJk5E243BVK5fxdKK2PkNJ59xeA/+t5H4K/ytx5nXSj0qo5M4SJ9/E13kfgVkyus7ODK5zgqC4oHluJThl2ZXFQ+ia1CBbIN5HY6AlXzK4W+8jLxswUC9MMjdqMq4JDk5QVcrp+9/JkYkyDL1LK7CCoch1Xpsa0MQL3xE3noQKX39LcXNX9LA==
*/