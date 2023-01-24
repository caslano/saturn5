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
4fOk22uYP99DbnqDbfnBuqFZBpGlZeQB4H6Oo/wchlUPUfazFMiC5e/woA2kdLbgtoyjnh/v5VxQzKcsUWAYmZmqI+Xu+QynRxWQ5wqawkwuUACR6wK3sLWGXABj+48FFLcDWR5ydYJeTEI03fmW6+WT5OsB4fjtyfczmzR9Az0gyI+cjmIcnzCd4wwcH0demqBPbg0wArwDFxbUuUpmunE2eh5mIzxcC1INOYX8bwD2j7VSoSWlwi8WlQy/WFYi/po5Ph5/jRxvJ3P0slvfwNaxIWMnk/SGtCKJk5ZK1qVPqUOlUh8qZZvUYWLtbZjgpLHQTf5niT5pWLuNj74eN8F7AIE/BgP9yDu36EYDvZH0TRpJpy6haP+Vnpz8JYqR8ub+ukHL9eSet05RfNMD+fJnQIqMED3ytGcZH70dDwCOAsSBFGDZPvP2JGON7d1GAP3YZdZD+ayHZrMeunk6RSZ0G+BWcFUcrKiGImQrK21mv6SkSquhGlh2YFIvcY9YjYHPgWdjeGCAloDRfEVhalIFOvUF6V6IotvuBXUdnw49Xvk5GiUA58zAEOz809D5jhvCmJ44l5Gkd7zek2cRUUMqWE8eV3vy72FMD7uaYkTuEr8e7v86bHBOYYMTtwvQTMdue7aGHhlPUKsxjdcIKbDeTfYu6inkTgkJuW6yha2kocsHkkPj9D5szPkJ3GzyItr1L7K0RA5l/1ME
*/