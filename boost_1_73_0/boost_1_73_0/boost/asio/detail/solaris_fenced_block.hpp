//
// detail/solaris_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__sun)

#include <atomic.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class solaris_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit solaris_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit solaris_fenced_block(full_t)
  {
    membar_consumer();
  }

  // Destructor.
  ~solaris_fenced_block()
  {
    membar_producer();
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__sun)

#endif // BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP

/* solaris_fenced_block.hpp
IWa7mL3B7B1mh5mdYPY5s3PMGpnprRQzWil2D7MZzBYyK2U2MU2xojTFpjGbyayG2RpmG5g9w+xjZieYnWH2d2Zaa8XcrRXrwKwzs77McpgFmYWYrWX2BLOX2yj2hzaK7WFWx+xdZkeZdW2rWM+2ivVjNohZMbMlzKqZhZmtZ/Y0s+3MdjHbx6yeWft0xa5IV6wns97MCtopNqGdYncxm8qsmlmY2b8zW8/sW2bfMXNmKObN4PQxu+L/WTsT8Kg=
*/