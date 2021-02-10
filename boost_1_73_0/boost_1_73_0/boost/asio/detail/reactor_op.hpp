//
// detail/reactor_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTOR_OP_HPP
#define BOOST_ASIO_DETAIL_REACTOR_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class reactor_op
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

  // The number of bytes transferred, to be passed to the completion handler.
  std::size_t bytes_transferred_;

  // Status returned by perform function. May be used to decide whether it is
  // worth performing more operations on the descriptor immediately.
  enum status { not_done, done, done_and_exhausted };

  // Perform the operation. Returns true if it is finished.
  status perform()
  {
    return perform_func_(this);
  }

protected:
  typedef status (*perform_func_type)(reactor_op*);

  reactor_op(perform_func_type perform_func, func_type complete_func)
    : operation(complete_func),
      bytes_transferred_(0),
      perform_func_(perform_func)
  {
  }

private:
  perform_func_type perform_func_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_REACTOR_OP_HPP

/* reactor_op.hpp
lTH5Ei7B4M/ZSLHgyafg8mGBWDe9GsWbuS6qB8Uf6Iwzywurh2D6KTGz8LFuS1TJzMma8KN0R5qHrYGYVBaz8Gc5uCFfDP7GrsaqaRau/d87G7YyfUxsXdfUR4HTC9XIX5KMI/LL0ZdkI2RwH+DauzFWRHzmmwCsH/mpcpJZoKGwmhheJrzU35FDPG4HZQ4n59Fey7sffqF7fm57Tdj+dXm9k3HfyWr+BGE+131cyAF1TLGEFKG1m+jCQ7xqAksAs/kZEeA9whCFMnGmoKcYUtuoTcxrUOgIYtVCNYA4BgiwZFxSnMkol6OYuGi8si/sV7cPxoZJKU2vaOZX5bDjoaz9YYosiGIOAeb4CicRKbsB0K8IGJxj5ddj3bkmOkbB+4j7s/yE5Q/KAHHWy7WrryNMGiEM4TCpR9WcBoBDEu8HLWwoRx4+c74HITsrCUNgobkKUcb/Op9WauVEBYRY1kAhMHvaxzDThKREOapNNd78eDXK3HrN2hqhx/04AfYSwMldcOJlkAA5dtdOlVnZJXxgiBQzMbDx0DDqq8T0VhtaOdQfykaZLiK6a1gpyxqaMxjWJEsQdS1adcNMNEeO0MDRsqM8jyVOtzpN3AP++JnIwGbX4MCoej7Cb1j3F3pwDr946PEQC7iF+Mk9
*/