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
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
*/