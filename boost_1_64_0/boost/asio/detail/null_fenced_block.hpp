//
// detail/null_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_fenced_block
  : private noncopyable
{
public:
  enum half_or_full_t { half, full };

  // Constructor.
  explicit null_fenced_block(half_or_full_t)
  {
  }

  // Destructor.
  ~null_fenced_block()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP

/* null_fenced_block.hpp
G+sUGzUNNkrzRik9iZeoH8aO7ZwQVbDF+Vt1cjjBxkdG1Jc0g8djbhIz8HHpGg1wmZdMbJ3QoAkmPIzhq82MT6MEZA9jKjzE31H5488KCTsdgfc5wbddFB3idtdylCryZSpI9oEUb5VaZwMX8GMRkXhxAXxNfX6KGnyiBRcIbVHx2Mr7mSS1QUJsGAd/r1DXRku+TKTAxRSBnTKcuZ187lDNSJezDL8HsAZfg3T5iBOeiGBEYM+CTVik8IR5q+H8+xaTfR08IRp5mvsEGceNK4jrDm2Y1fZWDh8L7LmCgGPMvfoPX/gQ23TuI97xETalTcuyP5AQ80kt7NRj6DTkfINaGqNTsjyBMZS/5X+DxpH/8vCJHP7DQuyGmXoWTCVqXmxWb7W7Q9tO/lU8K08kNy9uXp2i7LCcDSsTzFkSOfRE5a/gDGw+03DsY4Y0C/j9f0uMFB+W3Nyz1SSAdFWWj/cDW7SxwLSOBO74a+6dc9+YotOmHpLr6TTPmvuTzfZmihTe6GKNK65iUAY06wg+Gtug6KDoDa2vnn7JhomA6fbODURwhpYqRWMBIw==
*/