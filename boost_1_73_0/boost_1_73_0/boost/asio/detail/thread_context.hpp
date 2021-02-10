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
s0ne4FgoDQsU2UnSh2Rl+BOnQGOUmrfei1iP5F+MW8PVmDAGadcxFVuKWS1bHTpqPdxfLm+4r6/VHxMf/JwI3OU55PkCrFl5LQXHn+wcuL+d5+/OzqCmsmVDnnCQC2znOgt0Cg6xDCI4W01vtbFpjqNxBr3lfse0ofHUoLcdEzox3/M0yloXfCJnu1P4J8sc+T/C0msXGvIxUXQJQw0YnBPaRi7ZQkJgpYuXnfa8cVSzLczKWBM7niI7hJL+0jO6tXHIFl+1bLGowoZaW4KjtD1suExYiSCvOHKZrJhIvHpjWHZ1uJz7IXchYj2a18MtdsVGtvrt+k9htzHFRpCkWuOxYrtyVzXGDZXixz5DbDAmTcLRy5Jqi8w5n5xDOyh8sAVvFdvHMq3HYQnOxV1Wy2qLcorHnxo+zz68319l/6/790mov0/iI8jEUZf9zqd3o+ZnouxfGdF44DaBwP7nwVTKE4/kSPYTEWb/Dh00d9pvQzwmnB6xgKyr5nfb1OIIqWA1u48c9gNmR0hgpn4DUEsDBAoAAAAIAC1nSlJAKeWMogEAAM8CAAAmAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvY2FwYXRoLmRVVAUAAbZIJGBtkkFr3DAQhe/6FcMeSgKx
*/