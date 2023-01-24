//
// detail/thread_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THREAD_CONTEXT_HPP
#define BOOST_ASIO_DETAIL_THREAD_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <climits>
#include <cstddef>
#include <boost/asio/detail/call_stack.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class thread_info_base;

// Base class for things that manage threads (scheduler, win_iocp_io_context).
class thread_context
{
public:
  // Per-thread call stack to track the state of each thread in the context.
  typedef call_stack<thread_context, thread_info_base> thread_call_stack;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_THREAD_CONTEXT_HPP

/* thread_context.hpp
8l0cQjTvksNfNiIXRMZR0EsMhmm0xRB0fIIG1lhywYYtdpO3MFtKEGL/RgswZ7nI34ZT3fNido87U4QPRNB1mDdGE/RT5UjdHEVmoV41lUw5A/1l3qN6AXfiKueptNq0QymHhtaCIOHXXHlDYEqtKiot6bZrgZod6pfZa5KqXgRJhpD5V/FCCBB8bdsyImBCMpF/QBBq/q3p00twV3hbMoSXNHZF231VuOFQkoGbVKdd0rOvYAn/ylCbbKuyQUJlsnWjNTyli9z4SFBL8W/gUyUt3Ytykc5KPcERM97JgwXDmDF7I5W4JCZG4GHaOJnG4Gk1Zs5MP6lbW5/vNXid75JoUPWz+1G1HGdleW8qaaNVYpISXLu7yKQQ1Pm0SoyD3HuwSdl3QmRNn3wxmLH+TjWK3AqBrBaxdbLJ7zUpk83YUt8bUBVQrJZ52NftjFhtVQpuA76+h+79hDW3b6i5/8QUky09MRao0FO8ZUJlutIDY4dCCX5nQhnoiTsQZEu+G2/FefQg+githKD87XMiFanqJQCh4tISfpDPrZgaKy5N4Ps6gmXR2Xdvj4Fg4ZuUBga8GBxte3Qq3naj9LeJt+BNOpMXpjS43O9htQwCPELyUBcb6raqBNoAs94AiL0lBFsX+uuhJZvqXXqCvqEE/zR2bz/EfrtVj30PYkvsetsh8ngo8gUdIm+MizyBDu7lj6AfWJiLPIIhvm0R
*/