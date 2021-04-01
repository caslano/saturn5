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
kuzgk8i+Ei62Ues0LNWgXEpVGQE55SJi3TABMZ959Bid3PSyzhCkTU/R/pmYf8rFBSET4V6lnyrg4MwqOa43aHoswDGS3mrar4RO6NeVqONoeSsDpxPZNXX/gREqbgRCfoChCtLnjOOM1pwf3sX+62RXTCOSeqWwxjXo2qgQVsM5zQmN61RY0aouvdt3V7+usKaj1kv/9SNlSTnHJEid61C4iavmtKljAxQtiRWexjdIzVpgMW29Comd7xMP7Pg33rJJzDNURaC5Epb1lL52YBXqSwwm5DI1sWNIJiEYYnSSfclMcyhXRFnjpos3DZ9bAWVmHPCx7EZCk1YE7LG11ue/Dl8NWtFWgkF+1x/lkJxoL4lKym9PmhiSr6HVMuWEtbwSWzMjGcuSYUw0hpz+F1eHvLOa1jrD2q42qWYu8qdE1BJwCrSEzF6RMugBm39GeOpy7+KbR7KIM9xaRRuCmpdjo0vp8kMW5Sgd4R7MKvbh+xw+KPjTbiL9PnRlxMz+PDZuXr2LfcvSqV/Cv6nvBPW58GHoBtI6Tp663GF2KKJDjSqkTQSREj9/qQ==
*/