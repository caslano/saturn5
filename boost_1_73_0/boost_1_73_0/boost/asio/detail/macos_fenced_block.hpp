//
// detail/macos_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__MACH__) && defined(__APPLE__)

#include <libkern/OSAtomic.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class macos_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit macos_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit macos_fenced_block(full_t)
  {
    OSMemoryBarrier();
  }

  // Destructor.
  ~macos_fenced_block()
  {
    OSMemoryBarrier();
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__MACH__) && defined(__APPLE__)

#endif // BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP

/* macos_fenced_block.hpp
6MIgDsAcS5PhXNaSlqP5NCuaLHUb9tPF5c8Xt68//njtXxJm9XzI/UJv4/yLzAUd9XsyoyH2EL/78c3bS2k5m5UVZ/5zXqTlosa7QXwii5pPmvi3x1dXb45vjn8rc5eVoMNekTXVCM12ZQHVXMaZ5OMq+2c82pN2Tbf+PIrr+wQgw8P9+C5r4ipPAear45t3t++P/4QXB3GRNLns4dmbi3Aq02R0eY0Gh/G1PX13c3O1PeAE8HPzegsw+pJnnPBRfPLxw/nl1c3th9Pry/M/nrIhNpYfF/PpMKvQ8GV8kggWxkV2pyMXyTSLq6wuJ5+1q/5OnMybsptmDUCIQZZ83o+neZFP83/J4jSbCVJnxUiGjxd5cx+nS+koH8kGL+NJmaSyR9MynU+sz4HgTJpg595cXMuJqD4LSi3u84mMPS8Kg1N/Nx51Zf9qHBy/osur04vry5OfTm/efrw4uTm7vGDbvfhmOcvqZJzxWN4Kvi5v66wpZ83mFlvsx+/LIm8EEILFhSyGmGqo0z4SEJWKEQfxTbXEyZCRY1ldmWbxnQCpwAO2OIyP09TvFGB89uFMl3gUN/JxkX0xmMX5WLZSYFVmdfGi4Wkjbu3E1x/+yBV+/HBGeFTZqKxSxbwB13128fby9ur44/Xp7fXN
*/