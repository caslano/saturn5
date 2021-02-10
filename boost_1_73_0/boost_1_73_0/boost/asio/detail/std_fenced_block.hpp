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
p62va98Mu/iAFjTiyEzrmTesc7BixLdijSlkSd/oCgTbLlPS1avJFFxIF5fGMgdKoSoUk+B6k4HdD55ZERdr0Vrp6csZ7WilfW2ahBFdiErKzmpcBl2APIVBB69YpwuwgTds+rTC4M3g2i+EZLK1YEajJeybu3v2+v4blgkn3Yr99vrhp7f/e2C/3b1/f/fm4QN7+1929+YD6vr59ZtXGG+JK1kGh9aCw5Utk02rJBRhwT/vgwve12h0wTLwewDNfhVbCDsTTfDgSwJ+wf24tT/4i4tX7+5+/OGe/esv9Pl4wZjIcK8i97zT8sCdybfg18WJqDx3u3xdfL36T/VDEvooOl8HDYOOtgVdoAryXd4TCM9FDhaXwh+tOEkEAsLceeE7F6kJqD+2MMPiR9mi1xMh04QIQMGdi5cY8YRZl7JKAY09jHvZgOl8LD4QTMrtpe6Ai8QmY7YS+CdhF2AMWBAeeCFT63uUwsmxrODrYeglVEkexS/Kgcngzu4gVl0IL7hwuZRzMJNa2OMcxX4AOg82xDiuFchW7CMCKKhEaDmRFlmB8wngqOtwaG3k2Ql1uwU6k1bK7Dl2HqtFA1xqMnLM3EI7hLDwS0yzSBPB7e5vXBSFXcB/PwOj/l2aVIWpx6UGpGtaXoPAfhOh
*/